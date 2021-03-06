# SmartGuitarPedal

Guitar plugin made with JUCE that uses neural network models to emulate real world hardware.

See video demo on [YouTube](https://www.youtube.com/watch?v=8GAr6qQAlxY), along with a sound comparison [video](https://youtu.be/xEOFz3UcDyA) between
the TS9 Tubescreamer and a deep learning model using the SmartGuitarPedal.

This plugin uses a WaveNet model to recreate the sound of real world hardware, such as
a TS9 Tubescreamer or Blues Jr amp. Drive and Level are used for simple ways to
control the sound. The WaveNet model is effective at emulating distortion style effects or tube amplifiers.

![app](https://github.com/keyth72/SmartGuitarPedal/blob/master/resources/app_pic.png)

You can create your own models and load them in SmartGuitarPedal using the [PedalNetRT](https://github.com/GuitarML/PedalNetRT) repository.

Model training is done using PyTorch on pre recorded .wav samples. More info in the above repository. 
To share your best models, email the json files to smartguitarml@gmail.com and they may be included 
in the latest release as a downloadable zip.


Also see companion plugin, the [SmartGuitarAmp](https://github.com/GuitarML/SmartGuitarAmp)

## Installing the plugin

1. Download plugin (Windows 10, Ubuntu Linux) [here](https://github.com/keyth72/SmartGuitarPedal/releases)
2. Copy to your DAW's VST directory
3. Copy .json models from the models/ directory of this repository to the DAW's executable directory when using VST,
   (for example: "C:\Program Files\REAPER (x64)\\*.json") or to the same directory as the SmartPedal.exe when using standalone. You can also add the files to your user application data directory (see [Loading hardware models](#loading-hardware-models) below).
4. As an alternative to the drop down menu, as of release v1.2 there is a "LOAD MODEL" button to select one model 
   at a time from a file select dialog. Note that the model name won't appear in the drop down, but will be loaded by the plugin.
 
## Build Instructions

1. Clone or download this repository.
2. Download and install [JUCE](https://juce.com/) This project uses the "Projucer" application from the JUCE website. 
3. Download [Eigen](http://eigen.tuxfamily.org)
   Extract Eigen to a convenient location on your system (will be linked with Projucer)
4. Open SmartGuitarPedal.jucer file with Projucer
5. Add the <full_path_to>/ Eigen folder to "Header Search Paths" in Exporters -> Debug/Release
6. Open and build project in Visual Studio (Windows), Xcode (Mac), or Code::Blocks/Makefile (Linux)

Note: Make sure to build in Release mode unless actually debugging. Debug mode will not keep up with real time playing.

### Loading hardware models
Models are auto loaded from the working directory of the executable. When using the plugin, add the .json files to your DAW
.exe path (for example: "C:\Program Files\REAPER (x64)"). When running the stand alone exe, put in the same directory as
SmartPedal.exe. 

Alternatively, you can add the files to your user application data directory under "GuitarML\SmartPedal", and the plugin should load them. This corresponds to:
- Mac: `~/Library/GuitarML/SmartPedal`
- Linux: `~/.config/GuitarML/SmartPedal`
- Windows: `C:\Users\<username>\AppData\Roaming\GuitarML\SmartPedal`


## License
This project is licensed under the Apache License, Version 2.0 - see the [LICENSE](LICENSE) file for details.

This project builds off the work done in the [WaveNetVA](https://github.com/damskaggep/WaveNetVA) repository.
