/*
  Kenan Esso
  Assignment 6 - Serial Handshaking (Call & Response)

  Sensors:
  - Potentiometer 1 on 1
  - Potentiometer 2 on 2

  Actuators:
  - LED on pin 4
  - Piezo buzzer on pin 5

  Handshaking:
  p5.js sends:  R,mode
  Arduino sends: pot1,pot2
*/

const int pot1Pin = 1;
const int pot2Pin = 2;

const int ledPin = 4;
const int buzzerPin = 5;

int mode = 0; // 0 = calm, 1 = active

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // only do something if p5 sent a request
  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');
    message.trim();

    // expected format: R,0  or  R,1
    int commaIndex = message.indexOf(',');

    if (commaIndex > 0) {
      String requestPart = message.substring(0, commaIndex);
      String modePart = message.substring(commaIndex + 1);

      // update mode sent from p5.js
      mode = modePart.toInt();

      // control actuators based on mode
      updateActuators();

      // if the first part is R, send sensor data back
      if (requestPart == "R") {
        int pot1 = analogRead(pot1Pin);
        int pot2 = analogRead(pot2Pin);

        Serial.print(pot1);
        Serial.print(",");
        Serial.println(pot2);
      }
    }
  }
}

void updateActuators() {
  if (mode == 0) {
    // calm mode
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
  } else {
    // active mode
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 440); // A note
  }
}