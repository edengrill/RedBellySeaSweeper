#pragma once

#include <JuceHeader.h>

class WaveformDisplay : public juce::Component, public juce::Timer
{
public:
    WaveformDisplay()
    {
        startTimerHz(30); // 30 FPS refresh
        waveformPath.preallocateSpace(1024);
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
        
        // Draw status text
        g.setColour(juce::Colour(0xffd83427));
        g.setFont(13.0f);
        g.setFont(g.getCurrentFont().withStyle(juce::Font::plain));
        
        juce::String statusText = juce::String(static_cast<int>(currentFrequency)) + "Hz • " +
                                 juce::String(static_cast<int>(sweepProgress * 100)) + "% " +
                                 waveTypeName + " • " + modeName;
        
        g.drawText(statusText, bounds.reduced(20, 10), 
                  juce::Justification::bottomRight, false);
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
    
    void setWaveType(const juce::String& type) { waveTypeName = type.toUpperCase(); }
    void setMode(const juce::String& mode) { modeName = mode.toUpperCase(); }
    
private:
    SwoopDeviceAudioProcessor* processor = nullptr;
    juce::Path waveformPath;
    float currentFrequency = 20.0f;
    float sweepProgress = 0.0f;
    juce::String waveTypeName = "SINE";
    juce::String modeName = "SINGLE";
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};