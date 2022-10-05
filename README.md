# SmartGuitarPedal

[![Downloads](https://img.shields.io/github/downloads/GuitarML/SmartGuitarPedal/total)](https://somsubhra.github.io/github-release-stats/?username=GuitarML&repository=SmartGuitarPedal&page=1&per_page=30) [![CI](https://github.com/GuitarML/SmartGuitarPedal/actions/workflows/cmake.yml/badge.svg)](https://github.com/GuitarML/SmartGuitarPedal/actions/workflows/cmake.yml)

Guitar plugin made with JUCE that uses neural network models to emulate real world hardware.

- Checkout the tutorial on [YouTube](https://youtu.be/HrNf6DNRUdU) for creating your own models for the SmartPedal.
- Visit the GuitarML [ToneLibrary Website](https://guitarml.com/tonelibrary/tonelib-sa.html) to download SmartPedal compatible models.

![app](https://github.com/GuitarML/SmartGuitarPedal/blob/master/resources/app_pic.png)

This plugin uses a WaveNet model to recreate the sound of real world hardware, such as
a TS9 Tubescreamer or Blues Jr amp. Drive and Level adjust the signal gain before and after the 
WaveNet model processing. As of version 1.5, the SmartPedal can run models conditioned on a single parameter, 
such as a gain control. When conditioned models are loaded, the LED graphic will change colors 
from red to blue, and the Drive knob will control the conditioned parameter.

The WaveNet model is effective at emulating distortion style effects or tube amplifiers, but cannot capture
time based effects such as reverb or delay. You can capture the sound of an amplifier either by recording with 
a microphone, or direct out from a load box. When running "Direct Out" models, you will need to use an
Impulse Response plugin to accurately model the amp speaker/cabinet. 

You can create your own models and load them in SmartGuitarPedal using the [PedalNetRT](https://github.com/GuitarML/PedalNetRT) repository directly, or
by using the Capture Utility files (available for download at [GuitarML.com](https://guitarml.com/)) with Google Colab and following the [Video Tutorial](https://youtu.be/HrNf6DNRUdU).

Model training is done using PyTorch on pre recorded .wav samples. More info in the above repository. 
To share your best models, email the json files to smartguitarml@gmail.com and they may be included 
in the latest [ToneLibrary](https://guitarml.com/tonelibrary/tonelib-sa.html) release.

Also see companion plugin, the [SmartGuitarAmp](https://github.com/GuitarML/SmartGuitarAmp)

## Installing the plugin

1. Download the appropriate plugin installer (Windows, Mac, Linux) from the [Releases](https://github.com/GuitarML/SmartGuitarPedal/releases) page.
2. Run the installer and follow the instructions. May need to reboot to allow your DAW to recognize the new plugin.

## Build Instructions

### Build with Cmake

```bash
# Clone the repository
$ git clone https://github.com/GuitarML/SmartGuitarPedal.git
$ cd SmartGuitarPedal

# initialize and set up submodules
$ git submodule update --init --recursive

# build with CMake
$ cmake -Bbuild
$ cmake --build build --config Release
```
The binaries will be located in `SmartPedal/build/SmartPedal_artefacts/`

### Loading hardware models
Use the Load Model button to select a folder containing SmartPedal json models. Note that models for NeuralPi and SmartAmpPro use
a different model architecture and will not be compatible. Only WaveNet models trained using PedalNetRT are compatible with SmartPedal and SmartAmp.

## License
This project is licensed under the Apache License, Version 2.0 - see the [LICENSE](LICENSE) file for details.

This project builds off the work done in the [WaveNetVA](https://github.com/damskaggep/WaveNetVA) repository.

### Special Thanks
Special thanks to Stefan Schmidt for the graphics in SmartPedal version 1.5. These were created from a Blender model and rendered using the Cycles render engine.
