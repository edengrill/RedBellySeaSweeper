#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "LookAndFeel.h"
#include "WaveformDisplay_v1.3.0.h"

class SwoopDeviceAudioProcessorEditor : public juce::AudioProcessorEditor,
                                        public juce::Slider::Listener,
                                        public juce::Button::Listener,
                                        public juce::Timer
{
public:
    SwoopDeviceAudioProcessorEditor (SwoopDeviceAudioProcessor&);
    ~SwoopDeviceAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(juce::Slider* slider) override;
    void buttonClicked(juce::Button* button) override;
    void timerCallback() override;

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
    
    // Parameter attachments
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> startFreqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> endFreqAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sweepTimeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> powerAttachment;
    
    void updateFrequencyLabel(juce::Label& label, float freq);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SwoopDeviceAudioProcessorEditor)
};