/*
  Kenan Esso
  Assignment 5 - LED Beat Speed Controller

  Arduino receives beat speed from p5.js
  and blinks the LED using that speed.
*/

const int ledPin = 4;

int beatSpeed = 800;   // start slow
unsigned long lastBlinkTime = 0;
bool ledState = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  readSpeedFromP5();
  blinkLED();
}

void readSpeedFromP5() {
  if (Serial.available() > 0) {
    int incomingSpeed = Serial.parseInt();

    if (incomingSpeed >= 100 && incomingSpeed <= 1000) {
      beatSpeed = incomingSpeed;
    }
  }
}

void blinkLED() {
  unsigned long currentTime = millis();

  if (currentTime - lastBlinkTime >= beatSpeed) {
    lastBlinkTime = currentTime;
    ledState = !ledState;

    digitalWrite(ledPin, ledState);
  }
}