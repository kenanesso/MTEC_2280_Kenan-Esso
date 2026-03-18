/*
  Kenan Esso 
  Short Sketch #4 - Sensor to control a software sketch

  Simple Analog Sensor Sender
  Reads one analog sensor and sends the value to p5.js through Serial

  Music Style Aesthetic reference from 
  https://dev.to/devsatasurion/creative-coding-with-p5js-an-inclusive-javascript-library-4e55
*/


// Analog input pin
int sensorPin = A0;

// Variable to store the sensor value
int sensorValue = 0;

void setup() {
  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the analog sensor
  sensorValue = analogRead(sensorPin);

  // Send the sensor value to the computer
  Serial.println(sensorValue);

  // Small pause so data is easier to read
  delay(30);
}