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
                                       //private ComboBox::Listener
                                
{
public:
    SmartPedalAudioProcessorEditor (SmartPedalAudioProcessor&);
    ~SmartPedalAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;



private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SmartPedalAudioProcessor& processor;

    virtual void buttonClicked(Button* button) override;
    void loadButtonClicked();

    // Global Widgets
    Label modelLabel;

    ComboBox modelSelect;

    // Overdrive Widgets
    Slider odDriveKnob;
    Slider odLevelKnob;
    Slider odToneKnob;
    ImageButton odFootSw;
    ImageButton odLED;

    
    // LookandFeels 
    myLookAndFeel ampSilverKnobLAF;
    myLookAndFeel blackSilverKnobLAF;
    myLookAndFeel blackHexKnobLAF;


    Image background;

    virtual void sliderValueChanged(Slider* slider) override;
 
    void odFootSwClicked();
    void modelSelectChanged();
 
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SmartPedalAudioProcessorEditor)
};
