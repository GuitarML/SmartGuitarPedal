/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SmartPedalAudioProcessor::SmartPedalAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
    ),
    waveNet(1, 1, 1, 1, "linear", { 1 }),
    treeState(*this, nullptr, "PARAMETER", { std::make_unique<AudioParameterFloat>(GAIN_ID, GAIN_NAME, NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5f),
                        std::make_unique<AudioParameterFloat>(MASTER_ID, MASTER_NAME, NormalisableRange<float>(0.0f, 1.0f, 0.01f), 0.5) })

    
#endif
{
    driveParam = treeState.getRawParameterValue (GAIN_ID);
    masterParam = treeState.getRawParameterValue (MASTER_ID);
}

SmartPedalAudioProcessor::~SmartPedalAudioProcessor()
{
}

//==============================================================================
const String SmartPedalAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SmartPedalAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SmartPedalAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SmartPedalAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SmartPedalAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SmartPedalAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SmartPedalAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SmartPedalAudioProcessor::setCurrentProgram (int index)
{
}

const String SmartPedalAudioProcessor::getProgramName (int index)
{
    return {};
}

void SmartPedalAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SmartPedalAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    waveNet.prepareToPlay(samplesPerBlock);

}

void SmartPedalAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SmartPedalAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif


void SmartPedalAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;

    auto driveValue = static_cast<float> (driveParam->load());
    auto masterValue = static_cast<float> (masterParam->load());

    // Setup Audio Data
    const int numSamples = buffer.getNumSamples();
    const int numInputChannels = getTotalNumInputChannels();

    // Overdrive Pedal ================================================================== 
    if (fw_state == 1) {
        
        if (conditioned == false) {
            // Apply ramped changes for gain smoothing
            if (driveValue == previousDriveValue)
            {
                buffer.applyGain(driveValue*20.0);
            }
             else {
                buffer.applyGainRamp(0, (int) buffer.getNumSamples(), previousDriveValue * 20.0, driveValue * 20.0);
                previousDriveValue = driveValue;
            }
        } else {
            buffer.applyGain(10.0); // Apply default boost to help sound
            float* chanBuffer1 = buffer.getWritePointer(1);
            for (int i = 0; i < buffer.getNumSamples(); i++)
            {
                chanBuffer1[i] = driveValue; 
            }
        }

        waveNet.process(buffer.getArrayOfReadPointers(), buffer.getArrayOfWritePointers(),
            buffer.getNumSamples());
        
        // Master Volume 
        // Apply ramped changes for gain smoothing
        if (masterValue == previousMasterValue)
        {
            buffer.applyGain(masterValue);
        }
        else {
            buffer.applyGainRamp(0, (int) buffer.getNumSamples(), previousMasterValue, masterValue);
            previousMasterValue = masterValue;
        }
    }

    for (int ch = 1; ch < buffer.getNumChannels(); ++ch)
        buffer.copyFrom(ch, 0, buffer, 0, 0, buffer.getNumSamples());
}

//==============================================================================
bool SmartPedalAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SmartPedalAudioProcessor::createEditor()
{
    return new SmartPedalAudioProcessorEditor (*this);
}

//==============================================================================
void SmartPedalAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    auto state = treeState.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml());
    xml->setAttribute ("fw_state", fw_state);
    xml->setAttribute("folder", folder.getFullPathName().toStdString());
    xml->setAttribute("saved_model", saved_model.getFullPathName().toStdString());
    xml->setAttribute("current_model_index", current_model_index);
    copyXmlToBinary (*xml, destData);

}

void SmartPedalAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
    {
        if (xmlState->hasTagName (treeState.state.getType()))
        {
            treeState.replaceState (juce::ValueTree::fromXml (*xmlState));
            fw_state = xmlState->getBoolAttribute ("fw_state");
            saved_model = xmlState->getStringAttribute("saved_model");
            current_model_index = xmlState->getIntAttribute("current_model_index");
            File temp = xmlState->getStringAttribute("folder");
            folder = temp;
            if (auto* editor = dynamic_cast<SmartPedalAudioProcessorEditor*> (getActiveEditor()))
                editor->resetImages();
            if (auto* editor = dynamic_cast<SmartPedalAudioProcessorEditor*> (getActiveEditor()))
                editor->loadFromFolder();

        }
    }
}


void SmartPedalAudioProcessor::loadConfig(File configFile)
{
    this->suspendProcessing(true);
    WaveNetLoader loader(configFile);
    int numChannels = loader.numChannels;
    int inputChannels = loader.inputChannels;
    if (inputChannels > 1) {
        conditioned = true;
    } else {
        conditioned = false;
    }
    int outputChannels = loader.outputChannels;
    int filterWidth = loader.filterWidth;
    std::vector<int> dilations = loader.dilations;
    std::string activation = loader.activation;
    waveNet.setParams(inputChannels, outputChannels, numChannels, filterWidth, activation,
        dilations);
    loader.loadVariables(waveNet);
    this->suspendProcessing(false);
}



//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SmartPedalAudioProcessor();
}
