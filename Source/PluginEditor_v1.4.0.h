#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LookAndFeel.h"
#include "WaveformDisplay.h"

class SwoopDeviceAudioProcessorEditor : public juce::AudioProcessorEditor,
                                        public juce::Slider::Listener,
                                        public juce::Button::Listener,
                                        public juce::Timer,
                                        public juce::KeyListener
{
public:
    SwoopDeviceAudioProcessorEditor (SwoopDeviceAudioProcessor&);
    ~SwoopDeviceAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(juce::Slider* slider) override;
    void buttonClicked(juce::Button* button) override;
    void timerCallback() override;
    
    // Keyboard handling
    bool keyPressed(const juce::KeyPress& key, juce::Component* originatingComponent) override;
    
    // Mouse handling for tooltip
    void mouseMove(const juce::MouseEvent& event) override;
    void mouseExit(const juce::MouseEvent& event) override;

private:
    SwoopDeviceAudioProcessor& audioProcessor;
    SwoopLookAndFeel lookAndFeel;
    
    // GUI Components
    WaveformDisplay waveformDisplay;
    
    juce::ToggleButton powerButton;
    juce::Label powerLabel;
    
    juce::Slider startFreqKnob;
    juce::Slider endFreqKnob;
    juce::Slider sweepTimeKnob;
    
    juce::Label startFreqLabel;
    juce::Label endFreqLabel;
    juce::Label sweepTimeLabel;
    
    juce::Label startFreqValue;
    juce::Label endFreqValue;
    juce::Label sweepTimeValue;
    
    // Branding labels
    juce::Label pluginNameLabel;
    juce::Label authorLabel;
    
    // Tooltip for keyboard shortcut
    juce::Label keyboardTooltip;
    bool showingTooltip = false;
    
    // Parameter attachments
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> startFreqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> endFreqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sweepTimeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> powerAttachment;
    
    void updateFrequencyLabel(juce::Label& label, float freq);
    void togglePower();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SwoopDeviceAudioProcessorEditor)
};