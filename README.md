# SmartGuitarPedal

[![Downloads](https://img.shields.io/github/downloads/GuitarML/SmartGuitarPedal/total)](https://somsubhra.github.io/github-release-stats/?username=GuitarML&repository=SmartGuitarPedal&page=1&per_page=30) [![CI](https://github.com/GuitarML/SmartGuitarPedal/actions/workflows/cmake.yml/badge.svg)](https://github.com/GuitarML/SmartGuitarPedal/actions/workflows/cmake.yml)

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
