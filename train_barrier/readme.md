# Train Barrier

## Description
The "Train Barrier" project is an Arduino simulation of an automatic railway barrier. It uses a servo motor to control the barrier position, an IR sensor for near train detection, LEDs for signaling, and a buzzer for audible alerts. When the IR sensor detects a train's presence, the barrier closes, the red LEDs start flashing alternately, and the buzzer sounds to warn of the approaching train. After the train has passed, the barrier lifts, and the signaling stops.

## Required Components
- Arduino UNO
- Servo motor
- IR sensor
- LEDs (2 red, 1 white)
- Buzzer
- Resistors for LEDs
- Connection wires

## Circuit Diagram
The wiring diagram of the components will be included in the folder entitled 'images'

## Installation and Setup
Assemble the circuit according to the diagram and upload the source code to the Arduino board. Adjust the initial position of the servo motor if necessary, so the barrier is in the open position upon initialization.

## Operation
Upon the train's detection by the IR sensor:
- The barrier automatically closes.
- The white LED turns off, and the red LEDs start flashing alternately.
- The buzzer emits warning sounds.

After the train has passed and the IR sensor no longer detects obstructions, the barrier lifts, the red LED signaling stops, the white LED briefly lights up as a clear signal, and the buzzer stops.

## Source Code
The "Train Barrier" project utilizes an Arduino to simulate the operation of an automatic railway barrier, using an IR sensor to detect trains, a servo motor to control the barrier, LEDs for signaling, and a buzzer for emitting warning sounds.

### Reading the IR Sensor

```cpp
irSensorState = digitalRead(irSensorPin); // Read the IR sensor state
```

- The IR sensor state is read through the digital pin connected to `irSensorPin`.
- If the sensor detects an object (such as a train), `irSensorState` will be `LOW`, indicating the presence of the train.

### Controlling the Servo Motor

```cpp
if (irSensorState == 0) {
    barieraServo.write(0); // Close the barrier
} else {
    barieraServo.write(90); // Open the barrier
}
```

- The servo motor is controlled via the `barieraServo` object.
- If a train is detected (`irSensorState == 0`), the barrier is closed by rotating the servo motor to `0` degrees.
- If no train is detected, the barrier is lifted (returning to the initial position of `90` degrees), thus allowing passage.

### Signaling Mode with LEDs and Buzzer

```cpp
if (irSensorState == 0) {
    // If the train is detected
    digitalWrite(ledPinF, LOW); // Turn off the white LED
    bool ledState = digitalRead(ledPinP1);
    digitalWrite(ledPinP1, !ledState);
    digitalWrite(ledPinP2, ledState);
    digitalWrite(buzzerPin, HIGH);
    delay(100); // A short sound of 100ms
    digitalWrite(buzzerPin, LOW);
} else {
    // If the train is not detected
    digitalWrite(ledPinP1, LOW);
    digitalWrite(ledPinP2, LOW);
    digitalWrite(redTrain, LOW);
    digitalWrite(greenTrain, HIGH);
    digitalWrite(ledPinF, HIGH); // Turn on the white LED
    delay(1000);
    digitalWrite(ledPinF, LOW); // Turn off the white LED
    digitalWrite(buzzerPin, HIGH); // Stop the buzzer
}
```

- When the train is detected, the white LED is turned off, the red LEDs start flashing alternately to signal the barrier closing, and the buzzer emits short sounds to warn of the train's approach.
- Once the train has passed, the signaling stops: the red LEDs are turned off, the white LED briefly lights up as a clear signal, and the buzzer stops.
- The changing of the red LEDs' states and the buzzer sounds are controlled over time, using `millis()` to create a flashing effect and periodic beeps without blocking the code's execution.

## Video Demonstration
Watch the train barrier operation in action [here](https://youtu.be/E3cCFlINDoE).

## Contributions and Suggestions
Any feedback, improvement suggestions, or contributions to this project are welcome. I encourage you to open a pull request or initiate a discussion for any ideas or improvements.
