/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SmartPedalAudioProcessorEditor::SmartPedalAudioProcessorEditor (SmartPedalAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to

    // Overall Widgets
    addAndMakeVisible(loadButton);
    loadButton.setButtonText("LOAD MODEL");
    loadButton.addListener(this);

    addAndMakeVisible(modelLabel);
    modelLabel.setText("Model", juce::NotificationType::dontSendNotification);
    modelLabel.setJustificationType(juce::Justification::centred);
    modelLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    addAndMakeVisible(modelSelect);
    modelSelect.setColour(juce::Label::textColourId, juce::Colours::black);
    modelSelect.setScrollWheelEnabled(true);
    int c = 1;
    for (const auto& jsonFile : processor.jsonFiles) {
        modelSelect.addItem(jsonFile.getFileName(), c);
        c += 1;
    }
    modelSelect.onChange = [this] {modelSelectChanged();};

    auto font = modelLabel.getFont();
    float height = font.getHeight();
    font.setHeight(height);
    modelLabel.setFont(font);

    // Set Widget Graphics
    blackHexKnobLAF.setLookAndFeel(ImageCache::getFromMemory(BinaryData::knob_hex_png, BinaryData::knob_hex_pngSize));

    // Pre Amp Pedal Widgets
 
    // Overdrive
    odFootSw.setImages(true, true, true,
        ImageCache::getFromMemory(BinaryData::footswitch_up_png, BinaryData::footswitch_up_pngSize), 1.0, Colours::transparentWhite,
        Image(), 1.0, Colours::transparentWhite,
        ImageCache::getFromMemory(BinaryData::footswitch_down_png, BinaryData::footswitch_down_pngSize), 1.0, Colours::transparentWhite,
        0.0);
    addAndMakeVisible(odFootSw);
    odFootSw.addListener(this);

    odLED.setImages(true, true, true,
        ImageCache::getFromMemory(BinaryData::led_red_on_png, BinaryData::led_red_on_pngSize), 1.0, Colours::transparentWhite,
        Image(), 1.0, Colours::transparentWhite,
        ImageCache::getFromMemory(BinaryData::led_red_on_png, BinaryData::led_red_on_pngSize), 1.0, Colours::transparentWhite,
        0.0);
    addAndMakeVisible(odLED);

    driveSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, GAIN_ID, odDriveKnob);
    addAndMakeVisible(odDriveKnob);
    odDriveKnob.setLookAndFeel(&blackHexKnobLAF);
    odDriveKnob.addListener(this);
    odDriveKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    odDriveKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    odDriveKnob.setDoubleClickReturnValue(true, 0.5);

    masterSliderAttach = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, MASTER_ID, odLevelKnob);
    addAndMakeVisible(odLevelKnob);
    odLevelKnob.setLookAndFeel(&blackHexKnobLAF);
    odLevelKnob.addListener(this);
    odLevelKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    odLevelKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
    odLevelKnob.setDoubleClickReturnValue(true, 0.5);

    addAndMakeVisible(versionLabel);
    versionLabel.setText("v1.4", juce::NotificationType::dontSendNotification);
    versionLabel.setJustificationType(juce::Justification::left);
    versionLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    //auto font = versionLabel.getFont();
    //float height = font.getHeight();
    //font.setHeight(height); // 0.75
    versionLabel.setFont(font);

    // Size of plugin GUI
    setSize (500, 650);

    resetImages();

    loadFromFolder();
}

SmartPedalAudioProcessorEditor::~SmartPedalAudioProcessorEditor()
{
}

//==============================================================================
void SmartPedalAudioProcessorEditor::paint (Graphics& g)
{
    // Workaround for graphics on Windows builds (clipping code doesn't work correctly on Windows)
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    g.drawImageAt(background, 0, 0);  // Debug Line: Redraw entire background image
    #else
    // Redraw only the clipped part of the background image
    juce::Rectangle<int> ClipRect = g.getClipBounds(); 
    g.drawImage(background, ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight(), ClipRect.getX(), ClipRect.getY(), ClipRect.getWidth(), ClipRect.getHeight());
    #endif
}

void SmartPedalAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    //Overall Widgets
    loadButton.setBounds(184, 68, 120, 20);
    modelSelect.setBounds(50, 36, 400, 25);
    modelLabel.setBounds(193, 12, 90, 25);
    versionLabel.setBounds(465, 635, 60, 10);

    // Overdrive Widgets
    odDriveKnob.setBounds(112, 115, 125, 145);
    odLevelKnob.setBounds(283, 115, 125, 145);
    odFootSw.setBounds(220, 459, 75, 105);
    odLED.setBounds(239, 398, 75, 105);
}


void SmartPedalAudioProcessorEditor::loadButtonClicked()
{
    myChooser = std::make_unique<FileChooser> ("Select a folder to load models from",
                                               processor.folder,
                                               "*.json");
 
    auto folderChooserFlags = FileBrowserComponent::openMode | FileBrowserComponent::canSelectDirectories | FileBrowserComponent::canSelectFiles;
 
    myChooser->launchAsync (folderChooserFlags, [this] (const FileChooser& chooser)                
    {
        if (!chooser.getResult().exists()) {
                return;
        }
        Array<File> files;
        if (chooser.getResult().existsAsFile()) { // If a file is selected
            processor.saved_model = chooser.getResult();
            files = chooser.getResult().getParentDirectory().findChildFiles(2, false, "*.json");
            processor.folder = chooser.getResult().getParentDirectory();
        } else if (chooser.getResult().isDirectory()){ // Else folder is selected
            files = chooser.getResult().findChildFiles(2, false, "*.json");
            processor.folder = chooser.getResult();
        }
        
        processor.jsonFiles.clear();

        modelSelect.clear();

        if (files.size() > 0) {
            for (auto file : files) {
                modelSelect.addItem(file.getFileNameWithoutExtension(), processor.jsonFiles.size() + 1);
                processor.jsonFiles.push_back(file);
                processor.num_models += 1;
            }
            if (chooser.getResult().existsAsFile()) {
                modelSelect.setText(processor.saved_model.getFileNameWithoutExtension());
                processor.loadConfig(processor.saved_model);
            }
            else {
                modelSelect.setSelectedItemIndex(0, juce::NotificationType::dontSendNotification);
                modelSelectChanged();
            }
        }
    });
    
}

void SmartPedalAudioProcessorEditor::loadFromFolder()
{

    Array<File> files;
    files = processor.folder.findChildFiles(2, false, "*.json");

    processor.jsonFiles.clear();
    modelSelect.clear();

    if (files.size() > 0) {
        for (auto file : files) {
            modelSelect.addItem(file.getFileNameWithoutExtension(), processor.jsonFiles.size() + 1);
            processor.jsonFiles.push_back(file);
            processor.num_models += 1;
        }
        processor.loadConfig(processor.jsonFiles[processor.current_model_index]);
        modelSelect.setText(processor.jsonFiles[processor.current_model_index].getFileNameWithoutExtension(), juce::NotificationType::dontSendNotification);
    }
}


void SmartPedalAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if (button == &odFootSw) {
        odFootSwClicked();
    } else if (button == &loadButton) {
        loadButtonClicked();
    }
}

void SmartPedalAudioProcessorEditor::odFootSwClicked() {
    if (processor.fw_state == 0)
        processor.fw_state = 1;
    else
        processor.fw_state = 0;
    resetImages();
}

void SmartPedalAudioProcessorEditor::sliderValueChanged(Slider* slider)
{

}

void SmartPedalAudioProcessorEditor::modelSelectChanged()
{
    const int selectedFileIndex = modelSelect.getSelectedItemIndex();
    if (selectedFileIndex >= 0 && selectedFileIndex < processor.jsonFiles.size()) {
        processor.loadConfig(processor.jsonFiles[selectedFileIndex]);
    }
}


void SmartPedalAudioProcessorEditor::resetImages()
{
    if (processor.fw_state == 0) {
        odFootSw.setImages(true, true, true,
            ImageCache::getFromMemory(BinaryData::footswitch_up_png, BinaryData::footswitch_up_pngSize), 1.0, Colours::transparentWhite,
            Image(), 1.0, Colours::transparentWhite,
            ImageCache::getFromMemory(BinaryData::footswitch_up_png, BinaryData::footswitch_up_pngSize), 1.0, Colours::transparentWhite,
            0.0);
        odLED.setImages(true, true, true,
            ImageCache::getFromMemory(BinaryData::led_red_off_png, BinaryData::led_red_off_pngSize), 1.0, Colours::transparentWhite,
            Image(), 1.0, Colours::transparentWhite,
            ImageCache::getFromMemory(BinaryData::led_red_off_png, BinaryData::led_red_off_pngSize), 1.0, Colours::transparentWhite,
            0.0);
    }
    else {
        odFootSw.setImages(true, true, true,
            ImageCache::getFromMemory(BinaryData::footswitch_down_png, BinaryData::footswitch_down_pngSize), 1.0, Colours::transparentWhite,
            Image(), 1.0, Colours::transparentWhite,
            ImageCache::getFromMemory(BinaryData::footswitch_down_png, BinaryData::footswitch_down_pngSize), 1.0, Colours::transparentWhite,
            0.0);
       odLED.setImages(true, true, true,
            ImageCache::getFromMemory(BinaryData::led_red_on_png, BinaryData::led_red_on_pngSize), 1.0, Colours::transparentWhite,
            Image(), 1.0, Colours::transparentWhite,
            ImageCache::getFromMemory(BinaryData::led_red_on_png, BinaryData::led_red_on_pngSize), 1.0, Colours::transparentWhite,
            0.0);
    }
}