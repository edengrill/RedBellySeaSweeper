#pragma once

#include <JuceHeader.h>

class WaveformDisplay : public juce::Component, 
                        public juce::Timer,
                        public juce::Button::Listener
{
public:
    WaveformDisplay()
    {
        startTimerHz(30); // 30 FPS refresh
        waveformPath.preallocateSpace(1024);
        
        // Setup wave type clickable text
        waveTypes = { "SINE", "SAWTOOTH", "SQUARE", "TRIANGLE" };
        currentWaveIndex = 0;
        
        // Setup mode clickable text
        modes = { "SINGLE", "LOOP", "SWEEP" };
        currentModeIndex = 0;
    }
    
    ~WaveformDisplay() override
    {
        stopTimer();
    }
    
    void paint(juce::Graphics& g) override
    {
        auto bounds = getLocalBounds().toFloat();
        
        // Draw background
        g.setColour(juce::Colour(0xff0c0d13));
        g.fillRoundedRectangle(bounds, 12.0f);
        
        // Draw border
        g.setColour(juce::Colour(0xffd83427));
        g.drawRoundedRectangle(bounds.reduced(1.5f), 12.0f, 3.0f);
        
        // Draw grid
        g.setColour(juce::Colour(0xffd83427).withAlpha(0.15f));
        for (int i = 1; i < 8; ++i)
        {
            float x = bounds.getX() + (bounds.getWidth() / 8.0f) * i;
            g.drawVerticalLine(x, bounds.getY() + 10, bounds.getBottom() - 10);
        }
        for (int i = 1; i < 4; ++i)
        {
            float y = bounds.getY() + (bounds.getHeight() / 4.0f) * i;
            g.drawHorizontalLine(y, bounds.getX() + 10, bounds.getRight() - 10);
        }
        
        // Draw waveform
        if (!waveformPath.isEmpty())
        {
            g.setColour(juce::Colour(0xffd83427));
            g.strokePath(waveformPath, juce::PathStrokeType(2.0f));
        }
        
        // Draw sweep progress indicator
        if (sweepProgress > 0.0f && sweepProgress < 1.0f)
        {
            float progressX = bounds.getX() + 20 + (bounds.getWidth() - 40) * sweepProgress;
            g.setColour(juce::Colour(0xffd83427).withAlpha(0.5f));
            
            float dashLengths[] = { 5.0f, 5.0f };
            g.drawDashedLine(juce::Line<float>(progressX, bounds.getY() + 20, 
                                              progressX, bounds.getBottom() - 20), 
                            dashLengths, 2);
        }
        
        // Draw Mode and Wave selectors on BOTTOM LEFT
        g.setFont(13.0f);
        
        // Mode selector on LEFT (aligned with right-side text height)
        auto modeArea = juce::Rectangle<float>(bounds.getX() + 15, bounds.getBottom() - 25, 100, 15);
        juce::String modeText = "MODE: " + modes[currentModeIndex];
        
        // Change text color to white on hover (no box)
        if (modeHover)
            g.setColour(juce::Colours::white);
        else
            g.setColour(juce::Colour(0xffd83427));
        
        g.drawText(modeText, modeArea, juce::Justification::left, false);
        
        // Wave selector to the RIGHT of Mode
        auto waveArea = juce::Rectangle<float>(bounds.getX() + 130, bounds.getBottom() - 25, 120, 15);
        juce::String waveText = "WAVE: " + waveTypes[currentWaveIndex];
        
        // Change text color to white on hover (no box)
        if (waveHover)
            g.setColour(juce::Colours::white);
        else
            g.setColour(juce::Colour(0xffd83427));
        
        g.drawText(waveText, waveArea, juce::Justification::left, false);
        
        // Draw status text on RIGHT side
        g.setColour(juce::Colour(0xffd83427));
        juce::String statusText = juce::String(static_cast<int>(currentFrequency)) + "Hz • " +
                                 juce::String(static_cast<int>(sweepProgress * 100)) + "% " +
                                 waveTypes[currentWaveIndex] + " • " + modes[currentModeIndex];
        
        g.drawText(statusText, bounds.reduced(20, 10), 
                  juce::Justification::bottomRight, false);
    }
    
    void mouseMove(const juce::MouseEvent& event) override
    {
        auto bounds = getLocalBounds().toFloat();
        auto modeArea = juce::Rectangle<float>(bounds.getX() + 15, bounds.getBottom() - 25, 100, 15);
        auto waveArea = juce::Rectangle<float>(bounds.getX() + 130, bounds.getBottom() - 25, 120, 15);
        
        bool oldWaveHover = waveHover;
        bool oldModeHover = modeHover;
        
        waveHover = waveArea.contains(event.position);
        modeHover = modeArea.contains(event.position);
        
        if (waveHover || modeHover)
            setMouseCursor(juce::MouseCursor::PointingHandCursor);
        else
            setMouseCursor(juce::MouseCursor::NormalCursor);
        
        if (oldWaveHover != waveHover || oldModeHover != modeHover)
            repaint();
    }
    
    void mouseDown(const juce::MouseEvent& event) override
    {
        auto bounds = getLocalBounds().toFloat();
        auto modeArea = juce::Rectangle<float>(bounds.getX() + 15, bounds.getBottom() - 25, 100, 15);
        auto waveArea = juce::Rectangle<float>(bounds.getX() + 130, bounds.getBottom() - 25, 120, 15);
        
        if (waveArea.contains(event.position))
        {
            // Cycle through wave types
            currentWaveIndex = (currentWaveIndex + 1) % waveTypes.size();
            waveTypeName = waveTypes[currentWaveIndex];
            
            // Update both the display AND notify the processor
            setWaveType(waveTypes[currentWaveIndex]);
            
            if (onWaveTypeChanged)
                onWaveTypeChanged(currentWaveIndex);
                
            repaint();
        }
        else if (modeArea.contains(event.position))
        {
            // Cycle through modes
            currentModeIndex = (currentModeIndex + 1) % modes.size();
            modeName = modes[currentModeIndex];
            
            // Update both the display AND notify the processor
            setMode(modes[currentModeIndex]);
            
            if (onModeChanged)
                onModeChanged(currentModeIndex);
                
            repaint();
        }
    }
    
    void mouseExit(const juce::MouseEvent&) override
    {
        waveHover = false;
        modeHover = false;
        setMouseCursor(juce::MouseCursor::NormalCursor);
        repaint();
    }
    
    void timerCallback() override
    {
        if (processor != nullptr && processor->isPlaying())
        {
            updateWaveform();
            currentFrequency = processor->getCurrentFrequency();
            sweepProgress = processor->getSweepProgress();
            repaint();
        }
        else if (sweepProgress != 0.0f)
        {
            sweepProgress = 0.0f;
            currentFrequency = 20.0f;
            waveformPath.clear();
            repaint();
        }
    }
    
    void setProcessor(SwoopDeviceAudioProcessor* p) 
    { 
        processor = p; 
    }
    
    void updateWaveform()
    {
        if (processor == nullptr) return;
        
        auto data = processor->getWaveformData();
        auto bounds = getLocalBounds().toFloat().reduced(20, 30);
        
        waveformPath.clear();
        
        const float xScale = bounds.getWidth() / static_cast<float>(data.size());
        const float yScale = bounds.getHeight() * 0.4f;
        const float yCentre = bounds.getCentreY();
        
        waveformPath.startNewSubPath(bounds.getX(), yCentre);
        
        for (size_t i = 0; i < data.size(); ++i)
        {
            float x = bounds.getX() + i * xScale;
            float y = yCentre - data[i] * yScale;
            
            if (i == 0)
                waveformPath.startNewSubPath(x, y);
            else
                waveformPath.lineTo(x, y);
        }
    }
    
    void setWaveType(const juce::String& type) 
    { 
        waveTypeName = type.toUpperCase();
        for (int i = 0; i < waveTypes.size(); ++i)
        {
            if (waveTypes[i] == waveTypeName)
            {
                currentWaveIndex = i;
                break;
            }
        }
    }
    
    void setMode(const juce::String& mode) 
    { 
        modeName = mode.toUpperCase();
        for (int i = 0; i < modes.size(); ++i)
        {
            if (modes[i] == modeName)
            {
                currentModeIndex = i;
                break;
            }
        }
    }
    
    void setWaveTypeIndex(int index) 
    { 
        if (index >= 0 && index < waveTypes.size())
        {
            currentWaveIndex = index;
            waveTypeName = waveTypes[index];
        }
    }
    
    void setModeIndex(int index) 
    { 
        if (index >= 0 && index < modes.size())
        {
            currentModeIndex = index;
            modeName = modes[index];
        }
    }
    
    void buttonClicked(juce::Button*) override {}
    
    // Callbacks
    std::function<void(int)> onWaveTypeChanged;
    std::function<void(int)> onModeChanged;
    
private:
    SwoopDeviceAudioProcessor* processor = nullptr;
    juce::Path waveformPath;
    float currentFrequency = 20.0f;
    float sweepProgress = 0.0f;
    
    juce::StringArray waveTypes;
    juce::StringArray modes;
    int currentWaveIndex = 0;
    int currentModeIndex = 0;
    
    juce::String waveTypeName = "SINE";
    juce::String modeName = "SINGLE";
    
    bool waveHover = false;
    bool modeHover = false;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};