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
#include "ResonantLowpassFilter.h"


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

    void addDirectory(File file);

    void loadConfig(File configFile);
    
    void setPreGain(float dbValue);
    void setPostGain(float dbValue);

    // Overdrive Pedal
    void set_odDrive(float odDriveKnobLevel);
    float convertLogScale(float in_value, float x_min, float x_max, float y_min, float y_max);
    void set_odTone(float toneKnobValue);
    void set_odLevel(float db_odLevel);


    float decibelToLinear(float dbValue);

    // Pedal/amp states
    int od_state = 1;       // 0 = off, 1 = on

    File currentDirectory = File::getCurrentWorkingDirectory().getFullPathName();

    Array<File> fileArray;
    std::vector<File> jsonFiles;

private:
    WaveNet waveNet;  // OverDrive Pedal
    ResonantLowpassFilter reslowpass; // Overdrive tone control
    float preGain = 1.0;
    float postGain = 1.0;
    // Overdrive pedal
    float odLevel = 0.0;
    float odDrive = 0.0;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SmartPedalAudioProcessor)
};
