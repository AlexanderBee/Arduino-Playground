# Chameleon Lamp

## Description
The Chameleon Lamp is an innovative Arduino project that changes light color based on the detected ambient light intensity. Using a combination of Neopixel LEDs and a color sensor, this project can mimic surrounding colors, offering a unique and customizable ambient lighting experience.

## Required Components
- Arduino UNO (or compatible)
- Neopixel LED strip with 24 LEDs
- TCS3200 color sensor
- Photoresistor
- Resistors, wires, and a power source

## Circuit Diagram
A detailed circuit diagram is included in the folder entitled 'images'

## Installation and Setup
To run the Chameleon Lamp project, follow the steps below:
1. Assemble the hardware components according to the circuit diagram.
2. Upload the source code to the Arduino board using the Arduino IDE.
3. Adjust the calibration values (`redMin`, `redMax`, `greenMin`, `greenMax`, `blueMin`, `blueMax`) in the code, if necessary, to optimize color detection.

## Usage
Upon starting, the Chameleon Lamp will read the ambient light intensity and adjust the Neopixel LEDs' color accordingly. In low light conditions, the LEDs will display a dynamic range of colors, creating attractive visual effects.

## Source Code
A brief explanation of the main sections of the code:
- **Initialization**: Sets up the pins and initializes the LED strip and color sensor.
- **Color Reading**: Uses the TCS3200 sensor to detect colors and adjusts the LEDs accordingly.
- **Light Effects**: Activates a color transition effect for the LEDs in the absence of sufficient light.

## Video Demonstration
To see the Chameleon Lamp in action, watch the demonstration video [here](https://youtube.com/shorts/xmWnPU3yy4c?feature=share).

## Contributions
Contributions to this project are always welcome. If you have suggestions for improvement or want to contribute your own tweaks, I encourage you to initiate a pull request or open an issue.