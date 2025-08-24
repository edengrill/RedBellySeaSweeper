#include "PluginProcessor.h"
#include "PluginEditor.h"

SwoopDeviceAudioProcessorEditor::SwoopDeviceAudioProcessorEditor (SwoopDeviceAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setLookAndFeel(&lookAndFeel);
    setSize(700, 480); // Reduced height from 644
    
    // Setup waveform display with Wave/Mode selectors
    waveformDisplay.setProcessor(&audioProcessor);
    waveformDisplay.onWaveTypeChanged = [this](int index) {
        audioProcessor.waveTypeParam->setValueNotifyingHost(index / 3.0f);
    };
    waveformDisplay.onModeChanged = [this](int index) {
        audioProcessor.sweepModeParam->setValueNotifyingHost(index / 2.0f);
    };
    waveformDisplay.setWaveTypeIndex(audioProcessor.waveTypeParam->getIndex());
    waveformDisplay.setModeIndex(audioProcessor.sweepModeParam->getIndex());
    addAndMakeVisible(waveformDisplay);
    
    // Setup power button
    powerButton.setButtonText("");
    powerButton.setToggleState(audioProcessor.powerParam->get(), juce::dontSendNotification);
    powerButton.addListener(this);
    addAndMakeVisible(powerButton);
    
    powerLabel.setText("OFF", juce::dontSendNotification);
    powerLabel.setJustificationType(juce::Justification::centred);
    powerLabel.setColour(juce::Label::textColourId, juce::Colour(0xff666666));
    powerLabel.setFont(juce::Font(12.0f, juce::Font::bold));
    addAndMakeVisible(powerLabel);
    
    // Setup knobs
    startFreqKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    startFreqKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    startFreqKnob.setRange(20.0, 20000.0, 1.0);
    startFreqKnob.setSkewFactorFromMidPoint(1000.0);
    startFreqKnob.setValue(audioProcessor.startFreqParam->get());
    startFreqKnob.addListener(this);
    addAndMakeVisible(startFreqKnob);
    
    endFreqKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    endFreqKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    endFreqKnob.setRange(20.0, 20000.0, 1.0);
    endFreqKnob.setSkewFactorFromMidPoint(1000.0);
    endFreqKnob.setValue(audioProcessor.endFreqParam->get());
    endFreqKnob.addListener(this);
    addAndMakeVisible(endFreqKnob);
    
    sweepTimeKnob.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    sweepTimeKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    sweepTimeKnob.setRange(0.1, 60.0, 0.1);
    sweepTimeKnob.setValue(audioProcessor.sweepTimeParam->get());
    sweepTimeKnob.addListener(this);
    addAndMakeVisible(sweepTimeKnob);
    
    // Setup labels
    startFreqLabel.setText("START", juce::dontSendNotification);
    startFreqLabel.setJustificationType(juce::Justification::centred);
    startFreqLabel.setColour(juce::Label::textColourId, juce::Colour(0xffd83427));
    startFreqLabel.setFont(juce::Font(13.0f, juce::Font::bold));
    addAndMakeVisible(startFreqLabel);
    
    endFreqLabel.setText("END", juce::dontSendNotification);
    endFreqLabel.setJustificationType(juce::Justification::centred);
    endFreqLabel.setColour(juce::Label::textColourId, juce::Colour(0xffd83427));
    endFreqLabel.setFont(juce::Font(13.0f, juce::Font::bold));
    addAndMakeVisible(endFreqLabel);
    
    sweepTimeLabel.setText("TIME", juce::dontSendNotification);
    sweepTimeLabel.setJustificationType(juce::Justification::centred);
    sweepTimeLabel.setColour(juce::Label::textColourId, juce::Colour(0xffd83427));
    sweepTimeLabel.setFont(juce::Font(13.0f, juce::Font::bold));
    addAndMakeVisible(sweepTimeLabel);
    
    // Setup value labels
    startFreqValue.setJustificationType(juce::Justification::centred);
    startFreqValue.setColour(juce::Label::textColourId, juce::Colour(0xffd83427));
    startFreqValue.setFont(juce::Font("Monaco", 16.0f, juce::Font::bold));
    updateFrequencyLabel(startFreqValue, audioProcessor.startFreqParam->get());
    addAndMakeVisible(startFreqValue);
    
    endFreqValue.setJustificationType(juce::Justification::centred);
    endFreqValue.setColour(juce::Label::textColourId, juce::Colour(0xffd83427));
    endFreqValue.setFont(juce::Font("Monaco", 16.0f, juce::Font::bold));
    updateFrequencyLabel(endFreqValue, audioProcessor.endFreqParam->get());
    addAndMakeVisible(endFreqValue);
    
    sweepTimeValue.setJustificationType(juce::Justification::centred);
    sweepTimeValue.setColour(juce::Label::textColourId, juce::Colour(0xffd83427));
    sweepTimeValue.setFont(juce::Font("Monaco", 16.0f, juce::Font::bold));
    sweepTimeValue.setText(juce::String(audioProcessor.sweepTimeParam->get(), 1) + "s", juce::dontSendNotification);
    addAndMakeVisible(sweepTimeValue);
    
    // Setup branding labels
    pluginNameLabel.setText("Red Belly Sea Sweeper", juce::dontSendNotification);
    pluginNameLabel.setJustificationType(juce::Justification::left);
    pluginNameLabel.setColour(juce::Label::textColourId, juce::Colour(0xffd83427));
    pluginNameLabel.setFont(juce::Font(20.0f));
    addAndMakeVisible(pluginNameLabel);
    
    authorLabel.setText("by Garden of Ed", juce::dontSendNotification);
    authorLabel.setJustificationType(juce::Justification::left);
    authorLabel.setColour(juce::Label::textColourId, juce::Colour(0xffd83427));
    authorLabel.setFont(juce::Font(18.0f));
    addAndMakeVisible(authorLabel);
    
    // Start timer for UI updates
    startTimerHz(30);
}

SwoopDeviceAudioProcessorEditor::~SwoopDeviceAudioProcessorEditor()
{
    stopTimer();
    setLookAndFeel(nullptr);
}

void SwoopDeviceAudioProcessorEditor::paint(juce::Graphics& g)
{
    // Draw main background (black rounded container)
    g.fillAll(juce::Colours::black);
    
    // Draw inner container
    auto innerBounds = getLocalBounds().reduced(18);
    g.setColour(juce::Colour(0xfff8f8f8));
    g.fillRoundedRectangle(innerBounds.toFloat(), 20.0f);
    
    // Draw control panel background (same height as waveform)
    auto controlPanel = juce::Rectangle<int>(40, 220, 620, 160);
    g.setColour(juce::Colour(0xff0c0d13));
    g.fillRoundedRectangle(controlPanel.toFloat(), 15.0f);
}

void SwoopDeviceAudioProcessorEditor::resized()
{
    // Position waveform display
    waveformDisplay.setBounds(40, 40, 620, 160);
    
    // Position control panel elements (vertically centered in 160px high panel)
    int controlPanelY = 220;
    int controlPanelHeight = 160;
    int knobY = controlPanelY + (controlPanelHeight - 75) / 2 - 10; // Center knobs vertically
    
    // Position power button
    powerButton.setBounds(80, knobY + 10, 40, 65);
    powerLabel.setBounds(70, knobY + 80, 60, 20);
    
    // Position knobs and labels
    int knobSize = 75;
    int knobSpacing = 150;
    int startX = 250;
    
    startFreqLabel.setBounds(startX - 30, knobY - 25, 60, 20);
    startFreqKnob.setBounds(startX - knobSize/2, knobY, knobSize, knobSize);
    startFreqValue.setBounds(startX - 35, knobY + knobSize + 5, 70, 20);
    
    endFreqLabel.setBounds(startX + knobSpacing - 30, knobY - 25, 60, 20);
    endFreqKnob.setBounds(startX + knobSpacing - knobSize/2, knobY, knobSize, knobSize);
    endFreqValue.setBounds(startX + knobSpacing - 35, knobY + knobSize + 5, 70, 20);
    
    sweepTimeLabel.setBounds(startX + knobSpacing*2 - 30, knobY - 25, 60, 20);
    sweepTimeKnob.setBounds(startX + knobSpacing*2 - knobSize/2, knobY, knobSize, knobSize);
    sweepTimeValue.setBounds(startX + knobSpacing*2 - 35, knobY + knobSize + 5, 70, 20);
    
    // Position branding text at bottom center
    pluginNameLabel.setBounds(250, 400, 300, 25);
    authorLabel.setBounds(250, 425, 200, 22);
}

void SwoopDeviceAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &startFreqKnob)
    {
        audioProcessor.startFreqParam->setValueNotifyingHost(
            audioProcessor.startFreqParam->convertTo0to1(slider->getValue()));
        updateFrequencyLabel(startFreqValue, slider->getValue());
    }
    else if (slider == &endFreqKnob)
    {
        audioProcessor.endFreqParam->setValueNotifyingHost(
            audioProcessor.endFreqParam->convertTo0to1(slider->getValue()));
        updateFrequencyLabel(endFreqValue, slider->getValue());
    }
    else if (slider == &sweepTimeKnob)
    {
        audioProcessor.sweepTimeParam->setValueNotifyingHost(
            audioProcessor.sweepTimeParam->convertTo0to1(slider->getValue()));
        sweepTimeValue.setText(juce::String(slider->getValue(), 1) + "s", juce::dontSendNotification);
    }
}

void SwoopDeviceAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if (button == &powerButton)
    {
        bool isOn = powerButton.getToggleState();
        audioProcessor.powerParam->setValueNotifyingHost(isOn ? 1.0f : 0.0f);
        powerLabel.setText(isOn ? "ON" : "OFF", juce::dontSendNotification);
        powerLabel.setColour(juce::Label::textColourId, 
                            isOn ? juce::Colour(0xffd83427) : juce::Colour(0xff666666));
        
        // Force repaint to update visual state
        powerButton.repaint();
    }
}

void SwoopDeviceAudioProcessorEditor::timerCallback()
{
    // Update power button state to match parameter
    bool isOn = audioProcessor.powerParam->get();
    if (powerButton.getToggleState() != isOn)
    {
        powerButton.setToggleState(isOn, juce::dontSendNotification);
        powerLabel.setText(isOn ? "ON" : "OFF", juce::dontSendNotification);
        powerLabel.setColour(juce::Label::textColourId, 
                            isOn ? juce::Colour(0xffd83427) : juce::Colour(0xff666666));
    }
}

void SwoopDeviceAudioProcessorEditor::updateFrequencyLabel(juce::Label& label, float freq)
{
    if (freq < 1000.0f)
        label.setText(juce::String(static_cast<int>(freq)) + "Hz", juce::dontSendNotification);
    else
        label.setText(juce::String(freq / 1000.0f, 1) + "kHz", juce::dontSendNotification);
}