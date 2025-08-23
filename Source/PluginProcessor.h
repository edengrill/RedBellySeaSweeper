#pragma once

#include <JuceHeader.h>

class SwoopDeviceAudioProcessor : public juce::AudioProcessor
{
public:
    SwoopDeviceAudioProcessor();
    ~SwoopDeviceAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // Custom parameters
    juce::AudioParameterFloat* startFreqParam;
    juce::AudioParameterFloat* endFreqParam;
    juce::AudioParameterFloat* sweepTimeParam;
    juce::AudioParameterChoice* waveTypeParam;
    juce::AudioParameterChoice* sweepModeParam;
    juce::AudioParameterBool* powerParam;
    
    // Get current frequency for display
    float getCurrentFrequency() const { return currentFrequency; }
    float getSweepProgress() const { return sweepProgress; }
    bool isPlaying() const { return powerParam->get(); }
    
    // Waveform data for visualization
    std::array<float, 512> getWaveformData() const 
    { 
        std::lock_guard<std::mutex> lock(waveformMutex);
        return waveformBuffer; 
    }

private:
    // Oscillator state
    double currentSampleRate = 44100.0;
    double phase = 0.0;
    float currentFrequency = 20.0f;
    float sweepProgress = 0.0f;
    double sweepPhase = 0.0;
    int sweepDirection = 1;
    
    // Waveform buffer for visualization
    mutable std::mutex waveformMutex;
    std::array<float, 512> waveformBuffer;
    int waveformWritePos = 0;
    
    // Generate sample based on wave type
    float generateSample(float phase, int waveType);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SwoopDeviceAudioProcessor)
};