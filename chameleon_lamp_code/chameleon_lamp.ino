#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

#define PIN 3
#define NUMPIXELS 24
//#define CLOCK_PIN 13

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

CRGB leds[NUMPIXELS];

const int ldrPin = A0;

// Calibration Values

int redMin = 34;
int redMax = 87;
int greenMin = 39;
int greenMax = 100;
int blueMin = 35;
int blueMax = 88;



int redPW = 0;
int greenPW = 0;
int bluePW = 0;

int redValue;
int greenValue;
int blueValue;

void setup() {

  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  // Set Sensor output as input
  pinMode(sensorOut, INPUT);

  // Set Frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);


  //ring led
  pixels.begin();
  pixels.setBrightness(25);
  pixels.show();

  Serial.begin(57600);
  Serial.println("resetting");
  FastLED.addLeds<WS2812, PIN, RGB>(leds, NUMPIXELS);
  FastLED.setBrightness(84);

  //photoresistor
  pinMode(ldrPin, INPUT);
}

void fadeall() {
  for (int i = 0; i < NUMPIXELS; i++) { leds[i].nscale8(250); }
}

void loop() {
  //read photoresistor value
  int ldrStatus = analogRead(ldrPin);
  Serial.print(ldrStatus);
  if (ldrStatus >= 100) {

    // Read Red value
    redPW = getRedPW();
    redValue = map(redPW, redMin, redMax, 255, 0);
    Serial.print("red: ");
    Serial.print(redValue);

    // Read Green value
    greenPW = getGreenPW();
    greenValue = map(greenPW, greenMin, greenMax, 255, 0);
    Serial.print("green: ");
    Serial.print(greenValue);

    // Read Blue value
    bluePW = getBluePW();
    blueValue = map(bluePW, blueMin, blueMax, 255, 0);
    Serial.print("blue: ");
    Serial.print(blueValue);
    Serial.println();

    delay(1000);

    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(greenValue, redValue, blueValue));
    }
    pixels.show();
  } else {
    static uint8_t hue = 0;
    //Serial.print("x");
    for (int i = 0; i < NUMPIXELS; i++) {
      leds[i] = CHSV(hue++, 255, 255);
      // Show the leds
      FastLED.show();
      fadeall();
      // Wait a little bit before we loop around and do it again
      delay(30);
    }
    Serial.println("else");
  }
}


// Function to read Red Pulse Widths
int getRedPW() {

  // Set sensor to read Red only
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  int PW;
  PW = pulseIn(sensorOut, LOW);
  return PW;
}

// Function to read Green Pulse Widths
int getGreenPW() {

  // Set sensor to read Green only
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  int PW;
  PW = pulseIn(sensorOut, LOW);
  return PW;
}

// Function to read Blue Pulse Widths
int getBluePW() {

  // Set sensor to read Blue only
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  int PW;
  PW = pulseIn(sensorOut, LOW);
  return PW;
}