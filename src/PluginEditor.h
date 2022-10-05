/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "myLookAndFeel.h"

//==============================================================================
/**
*/
class SmartPedalAudioProcessorEditor  : public AudioProcessorEditor,
                                       private Button::Listener,
                                       private Slider::Listener                  
{
public:
    SmartPedalAudioProcessorEditor (SmartPedalAudioProcessor&);
    ~SmartPedalAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    std::unique_ptr<FileChooser> myChooser;

    void loadFromFolder();
    void resetImages();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SmartPedalAudioProcessor& processor;


    TextButton loadButton;
    virtual void buttonClicked(Button* button) override;
    void loadButtonClicked();

    //Image background = ImageCache::getFromMemory(BinaryData::smart_pedal_jpg, BinaryData::smart_pedal_jpgSize);
    // LookandFeels and Graphics
    Image background_on = ImageCache::getFromMemory(BinaryData::background_on_jpg, BinaryData::background_on_jpgSize);
    Image background_on_blue = ImageCache::getFromMemory(BinaryData::background_on_blue_jpg, BinaryData::background_on_blue_jpgSize);
    Image background_off = ImageCache::getFromMemory(BinaryData::background_off_jpg, BinaryData::background_off_jpgSize);

    // Global Widgets
    Label modelLabel;
    Label versionLabel;

    ComboBox modelSelect;

    // Overdrive Widgets
    Slider odDriveKnob;
    Slider odLevelKnob;
    ImageButton odFootSw;
    //ImageButton odLED;

    
    // LookandFeels 
    myLookAndFeel blackHexKnobLAF;

    virtual void sliderValueChanged(Slider* slider) override;

    AudioProcessorParameter* getParameter(const String& paramId);
 
    void odFootSwClicked();
    void modelSelectChanged();



public:
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> driveSliderAttach;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> masterSliderAttach;
 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SmartPedalAudioProcessorEditor)
};
