# ChromaJamBCA
## Table of contents
1. About the Installaton
2. Circuit & Components
3. Making Your Own Audio Reactive Lights

## About the Installation
This code was developed for an upcoming 3 month installation at Burlington City Arts collaborating with light designer Clay Mohrman and musician Britt Mae. An Arduino Nano handles audio processing to modulate 3 LED channels based on 3 audio signals. The Nano also controls a [DFPlayer Mini](https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299) to programatically synchronize the audio in the installation space.

*Cool Pictures To Come*

## Circuit & Components
### Minimal Components List
* 1x Arduino Nano (or Suitable Replacement)
* 3x DFRobot DFPlayer Mini
* 3x Texas Instruments TL072 op amp
* 3x RFP30N06LE NPN MOSFET Transistors
* Assorted Resistors
* Assorted Capacitors

*Circuit Diagram to Come*

## Making Your Own Audio Reactive Lights
To begin, clone this repository. It was developed using VSCode + Platform.io so you may find that helpful for implementation. [AudioReactor](lib/AudioReactor) is the primary library to check out if you just want to implement audio reactivity and don't need to play MP3s from your Arduino. See how it is used in [main](src/main.cpp).
