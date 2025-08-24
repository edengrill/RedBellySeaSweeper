#include "PluginProcessor.h"
#include "PluginEditor.h"

SwoopDeviceAudioProcessor::SwoopDeviceAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    // Initialize parameters
    addParameter(powerParam = new juce::AudioParameterBool("power", "Power", false));
    addParameter(startFreqParam = new juce::AudioParameterFloat("startFreq", "Start Frequency", 
        juce::NormalisableRange<float>(20.0f, 20000.0f, 1.0f, 0.5f), 6700.0f));
    addParameter(endFreqParam = new juce::AudioParameterFloat("endFreq", "End Frequency", 
        juce::NormalisableRange<float>(20.0f, 20000.0f, 1.0f, 0.5f), 699.0f));
    addParameter(sweepTimeParam = new juce::AudioParameterFloat("sweepTime", "Sweep Time", 
        juce::NormalisableRange<float>(0.1f, 60.0f, 0.1f), 13.5f));
    addParameter(waveTypeParam = new juce::AudioParameterChoice("waveType", "Wave Type", 
        juce::StringArray{"Sine", "Sawtooth", "Square", "Triangle"}, 0));
    addParameter(sweepModeParam = new juce::AudioParameterChoice("sweepMode", "Sweep Mode", 
        juce::StringArray{"Single", "Loop", "Sweep"}, 2));
    
    waveformBuffer.fill(0.0f);
}

SwoopDeviceAudioProcessor::~SwoopDeviceAudioProcessor()
{
}

const juce::String SwoopDeviceAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SwoopDeviceAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SwoopDeviceAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SwoopDeviceAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SwoopDeviceAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SwoopDeviceAudioProcessor::getNumPrograms()
{
    return 1;
}

int SwoopDeviceAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SwoopDeviceAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SwoopDeviceAudioProcessor::getProgramName (int index)
{
    return {};
}

void SwoopDeviceAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

void SwoopDeviceAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    currentSampleRate = sampleRate;
    phase = 0.0;
    sweepPhase = 0.0;
}

void SwoopDeviceAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SwoopDeviceAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

float SwoopDeviceAudioProcessor::generateSample(float phase, int waveType)
{
    switch (waveType)
    {
        case 0: // Sine
            return std::sin(phase);
            
        case 1: // Sawtooth
            return 2.0f * (phase / (2.0f * juce::MathConstants<float>::pi)) - 1.0f;
            
        case 2: // Square
            return phase < juce::MathConstants<float>::pi ? 1.0f : -1.0f;
            
        case 3: // Triangle
        {
            float p = phase / (2.0f * juce::MathConstants<float>::pi);
            return 4.0f * std::abs(p - 0.5f) - 1.0f;
        }
            
        default:
            return 0.0f;
    }
}

void SwoopDeviceAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    if (!powerParam->get())
    {
        buffer.clear();
        // Reset sweep when powered off
        sweepPhase = 0.0;
        sweepDirection = 1;
        return;
    }

    // Get parameters - these can change in real-time
    const float startFreq = startFreqParam->get();
    const float endFreq = endFreqParam->get();
    const float sweepTime = sweepTimeParam->get();
    const int waveType = waveTypeParam->getIndex();
    const int sweepMode = sweepModeParam->getIndex();
    
    const double sweepIncrement = 1.0 / (sweepTime * currentSampleRate);
    
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        // Update sweep progress
        if (sweepMode == 0) // Single
        {
            sweepPhase += sweepIncrement;
            if (sweepPhase >= 1.0)
            {
                sweepPhase = 1.0;
                powerParam->setValueNotifyingHost(0.0f); // Turn off after single sweep
            }
        }
        else if (sweepMode == 1) // Loop
        {
            sweepPhase += sweepIncrement;
            if (sweepPhase >= 1.0)
                sweepPhase -= 1.0;
        }
        else if (sweepMode == 2) // Sweep (back and forth)
        {
            sweepPhase += sweepIncrement * sweepDirection;
            if (sweepPhase >= 1.0)
            {
                sweepPhase = 1.0;
                sweepDirection = -1;
            }
            else if (sweepPhase <= 0.0)
            {
                sweepPhase = 0.0;
                sweepDirection = 1;
            }
        }
        
        sweepProgress = static_cast<float>(sweepPhase);
        
        // Calculate current frequency (logarithmic sweep)
        const float logStart = std::log(startFreq);
        const float logEnd = std::log(endFreq);
        currentFrequency = std::exp(logStart + sweepProgress * (logEnd - logStart));
        
        // Generate oscillator sample
        const double phaseIncrement = (currentFrequency * 2.0 * juce::MathConstants<double>::pi) / currentSampleRate;
        phase += phaseIncrement;
        
        if (phase >= 2.0 * juce::MathConstants<double>::pi)
            phase -= 2.0 * juce::MathConstants<double>::pi;
        
        float outputSample = generateSample(static_cast<float>(phase), waveType) * 0.1f; // Scale down for safety
        
        // Write to all channels
        for (int channel = 0; channel < totalNumOutputChannels; ++channel)
        {
            buffer.getWritePointer(channel)[sample] = outputSample;
        }
        
        // Store in waveform buffer for visualization
        if (sample % 4 == 0) // Downsample for visualization
        {
            std::lock_guard<std::mutex> lock(waveformMutex);
            waveformBuffer[waveformWritePos] = outputSample;
            waveformWritePos = (waveformWritePos + 1) % waveformBuffer.size();
        }
    }
}

bool SwoopDeviceAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* SwoopDeviceAudioProcessor::createEditor()
{
    return new SwoopDeviceAudioProcessorEditor (*this);
}

void SwoopDeviceAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = getParameters();
    std::unique_ptr<juce::XmlElement> xml(new juce::XmlElement("SwoopDeviceState"));
    
    for (auto* param : getParameters())
    {
        if (auto* p = dynamic_cast<juce::AudioParameterFloat*>(param))
            xml->setAttribute(p->paramID, p->get());
        else if (auto* p = dynamic_cast<juce::AudioParameterBool*>(param))
            xml->setAttribute(p->paramID, p->get());
        else if (auto* p = dynamic_cast<juce::AudioParameterChoice*>(param))
            xml->setAttribute(p->paramID, p->getIndex());
    }
    
    copyXmlToBinary(*xml, destData);
}

void SwoopDeviceAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    
    if (xmlState.get() != nullptr && xmlState->hasTagName("SwoopDeviceState"))
    {
        for (auto* param : getParameters())
        {
            if (auto* p = dynamic_cast<juce::AudioParameterFloat*>(param))
                p->setValueNotifyingHost(xmlState->getDoubleAttribute(p->paramID, p->get()));
            else if (auto* p = dynamic_cast<juce::AudioParameterBool*>(param))
                p->setValueNotifyingHost(xmlState->getBoolAttribute(p->paramID, p->get()));
            else if (auto* p = dynamic_cast<juce::AudioParameterChoice*>(param))
                p->setValueNotifyingHost(xmlState->getIntAttribute(p->paramID, p->getIndex()) / (float)(p->choices.size() - 1));
        }
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SwoopDeviceAudioProcessor();
}