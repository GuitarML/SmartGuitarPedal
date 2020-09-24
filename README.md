# SmartGuitarPedal

Guitar plugin made with JUCE that uses neural network models to emulate real world hardware.

This plugin uses a WaveNet model to recreate the sound of real world hardware, such as
a TS9 Tubescreamer or Blues Jr amp. Drive, Level, and Tone were added for simple ways to
control the sound. The WaveNet model is effective at emulating distortion style effects or tube amplifiers.

![app](https://github.com/keyth72/SmartGuitarPedal/blob/master/resources/app_pic.png)

You can create your own models and load them in SmartGuitarPedal using the following Github repository:

https://github.com/keyth72/pedalnet

Model training is done using PyTorch on pre recorded .wav samples. More info in the above repository.
Feel free to create a pull request to add your own trained models to this repository.


Also see companion plugin, the SmartGuitarAmp:
https://github.com/keyth72/SmartGuitarAmp


## Initial Setup

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


This project builds off the work done here:
https://github.com/damskaggep/WaveNetVA

## License
This project is licensed under the Apache License, Version 2.0 - see the [LICENSE](LICENSE) file for details.
