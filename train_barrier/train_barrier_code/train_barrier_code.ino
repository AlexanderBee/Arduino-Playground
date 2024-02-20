#include <Servo.h>

const int ledPinP1 = 9; //rosu stanga
const int ledPinP2 = 6; //rosu dreapta
const int ledPinF = 3;  //alb
const int redTrain = 2;
const int greenTrain = 5;
const int irSensorPin = 10; // Senzorul IR conectat la pinul 10
const int servoPin = 11;    // Servomotorul conectat la pinul 11
const int buzzerPin = 8;    // Buzzer conectat la pinul 8

Servo barieraServo; // Creăm un obiect Servo
//int switchState = 0;
int irSensorState = 0; // Variabila pentru starea senzorului IR
unsigned long time = 0;
bool buzzerState = false;
unsigned long previousMillis = 0; // timpul la care s-a schimbat ultima data starea LED-urilor

void setup() {
    Serial.begin(57600);
    pinMode(ledPinP1, OUTPUT);
    pinMode(ledPinP2, OUTPUT);
    pinMode(ledPinF, OUTPUT);
    pinMode(greenTrain, OUTPUT);
    pinMode(redTrain, OUTPUT);
    pinMode(irSensorPin, INPUT); // Setăm pinul senzorului IR ca input

    barieraServo.attach(servoPin); // Atașăm servomotorul la pinul corespunzător
    barieraServo.write(90); // Inițializăm bariera deschisă (90 de grade)
    pinMode(buzzerPin, OUTPUT); // Setăm pinul buzzer ca output
}

void loop() {
    irSensorState = digitalRead(irSensorPin); // Citim starea senzorului IR
    Serial.print("Time: ");
    unsigned long currentMillis = millis();

    Serial.println(time); // prints time since program started
    delay(1000);

    if (irSensorState == 0) // Dacă trenul este detectat
    { 
        barieraServo.write(0); // Închidem bariera
        //digitalWrite(ledPinF, HIGH); // Aprindem semnalul de stop
        digitalWrite(ledPinF, LOW); //stingem ledul alb
        delay(1000); // Așteptăm 1 secundă

        if (currentMillis - previousMillis >= 2000)
        { // Dacă au trecut 2 secunde
          previousMillis = currentMillis; // Resetăm cronometrul
        
          // Comutăm LED-urile roșii
          bool ledState = digitalRead(ledPinP1);
          digitalWrite(ledPinP1, !ledState);
          digitalWrite(ledPinP2, ledState);
        
          // Bipăm buzzerul
          digitalWrite(buzzerPin, HIGH);
          delay(100); // Un sunet scurt de 100ms
          digitalWrite(buzzerPin, LOW);
        }

    }
    else
    {
        barieraServo.write(90); // Deschidem bariera
        //digitalWrite(ledPinF, LOW); // Stingem semnalul de stop

        digitalWrite(ledPinP1, LOW);
        digitalWrite(ledPinP2, LOW);
        
        digitalWrite(redTrain, LOW);
        digitalWrite(greenTrain, HIGH);

        delay(1000);
        digitalWrite(ledPinF, HIGH); //aprindem ledul alb
        delay(1000);
        digitalWrite(ledPinF, LOW);
        digitalWrite(buzzerPin, HIGH); // Oprim buzzerul
    }
}