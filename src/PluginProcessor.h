/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveNet.h"
#include "WaveNetLoader.h"

#define GAIN_ID "drive"
#define GAIN_NAME "Drive"
#define MASTER_ID "level"
#define MASTER_NAME "Level"

//==============================================================================
/**
*/
class SmartPedalAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    SmartPedalAudioProcessor();
    ~SmartPedalAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // Files and configuration
    //void setupDataDirectories();
    //void addDirectory(const File& file);
    void loadConfig(File configFile);


    //File userAppDataDirectory_irs = File::getSpecialLocation(File::userDesktopDirectory);

    // Pedal/amp states
    int fw_state = 1;       // 0 = off, 1 = on

    File currentDirectory = File::getCurrentWorkingDirectory().getFullPathName();
    int current_model_index = 0;

    Array<File> fileArray;
    std::vector<File> jsonFiles;
    int num_models = 0;
    File folder = File::getSpecialLocation(File::userDesktopDirectory);
    //File folder;
    File saved_model;

    AudioProcessorValueTreeState treeState;
    

private:

    std::atomic<float>* driveParam = nullptr;
    std::atomic<float>* masterParam = nullptr;

    float previousDriveValue = 0.5;
    float previousMasterValue = 0.5;

    //chowdsp::ResampledProcess<chowdsp::ResamplingTypes::SRCResampler<>> resampler;

    WaveNet waveNet;

    //float preGain = 1.0;
    //float postGain = 1.0;
    // Overdrive pedal
    //float odLevel = 0.0;
    //float odDrive = 0.0;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SmartPedalAudioProcessor)
};
