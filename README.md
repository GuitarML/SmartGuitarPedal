# SmartGuitarPedal

Guitar plugin that uses neural network models to emulate real world hardware.

This plugin uses a WaveNet model to recreate the sound of real world hardware, such as
a TS9 Tubescreamer or Blues Jr amp. Drive, Gain, and Tone were added for simple but effective ways
to control the sound. The WaveNet model is effective at emulating distortion style effects or tube amplifiers.


You can create your own models and load them in SmartGuitarPedal using the following Github repository:

https://github.com/keyth72/pedalnet

Model training is done using PyTorch on pre recorded .wav samples. More info in the above repository.


## Initial Setup

1. Clone or download this repository.
2. Download and install [JUCE](https://juce.com/) This project uses the "Projucer" application from the JUCE website. 
3. Download [Eigen](http://eigen.tuxfamily.org)
   Extract Eigen to a convenient location on your system (will be linked with Projucer)
4. Open SmartGuitarPedal.jucer file with Projucer
5. Add the <full_path_to>/ Eigen folder to "Header Search Paths" in Exporters -> Debug/Release
6. Open and build project in Visual Studio (Windows), Xcode (Mac), or Code::Blocks/Makefile (Linux)

### Loading hardware models
When running the plugin, load the directory containing the .json model files using the "Set Model Directory" button,
and select a model from the combobox.


This project builds off the the work done here:
https://github.com/damskaggep/WaveNetVA

## License
This project is licensed under the Apache License, Version 2.0 - see the [LICENSE](LICENSE) file for details.
