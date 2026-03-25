/*
  Kenan Esso
  Assignment 4 - 4 Sensor UART Control for P5.js

  Sensors used:
  1. Potentiometer 1 -  to change circle size
  2. Potentiometer 2 -  to change size of bars
  3. Button 1   - to change circle color
  4. Button 2   - to change the background color      gray/blue

  This Arduino code reads the sensors
  and sends values to P5.js using Serial UART.
*/

// --------------------
// PIN SETUP
// --------------------
int pot1 = 1;
int pot2 = 2;
int button1 = 4;
int button2 = 5;

void setup() {
  Serial.begin(9600);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
}

void loop() {

  int p1 = analogRead(pot1);
  int p2 = analogRead(pot2);
  int b1 = digitalRead(button1);
  int b2 = digitalRead(button2);

  Serial.print(p1);
  Serial.print(",");
  Serial.print(p2);
  Serial.print(",");
  Serial.print(b1);
  Serial.print(",");
  Serial.println(b2);

  delay(30);
}