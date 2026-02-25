/*
Kenan Esso 
Short Sketch #2 - Digital Input

  this is attempted template version (I do not have access to a ESP32-S3 Arduino board as of yet) 
  (Concept Demonstration purpose)
  This code represents LED behavior without needing hardware.

  SS2 - Digital Input (ESP32-S3)
  4 LEDs + 1 button cycles through 6 patterns
*/

const int ledPins[4] = {4, 5, 6, 7};   // LED pins (edit to match your wiring)
const int buttonPin = 2;               // Button pin (one side to GND)

int patternIndex = 0;                  // variable #1: this would indicate which pattern it is
int lastButton = HIGH;                 // variable #2: this woukd indicate the last button reading
int buttonNow = HIGH;                  // variable #3: this would indicate the current reading

// This is where the 6 unique patterns gets mapped out to 4 LEDs
const byte patterns[6] = {
  0b0000,  // all off
  0b1111,  // all on
  0b1000,  // one on (LED1)
  0b0100,  // one on (LED2)
  0b0010,  // one on (LED3)
  0b0001   // one on (LED4)
};

void showPattern(byte mask)
{
  for (int i = 0; i < 4; i++)
  {
    bool on = (mask >> (3 - i)) & 1;
    digitalWrite(ledPins[i], on ? HIGH : LOW);
  }
}


void setup() {
  // put your setup code here, to run once:
  // This is where the hardware is prepared.

  // Set each LED pin as an OUTPUT
  // This tells the ESP32 that these pins will send voltage out
  for (int i = 0; i < 4; i++)
  {
    pinMode(ledPins[i], OUTPUT);

    // Start with LEDs turned OFF
    digitalWrite(ledPins[i], LOW);
  }

  // Set button pin as INPUT_PULLUP
  // This activates an internal resistor
  
  // !important reminder!:
  // Not pressed = HIGH
  // Pressed = LOW
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  // This code keeps running over and over.

  // This reads the button's current state
  buttonNow = digitalRead(buttonPin);

  // If Statenment  #1 
  // Detect a NEW button press (Rising/Falling Edge logic)
  // We check if the button WAS HIGH
  // AND is NOW LOW
  // This means the button was just pressed, revising the condition
  if (lastButton == HIGH && buttonNow == LOW)
  {
    // Move to the next pattern
    patternIndex++;

    // // If Statenment  #2
    // If we reach past pattern 5, reset back to pattern 0
    if (patternIndex >= 6)
    {
      patternIndex = 0;
    }
  }

  // Show the current pattern on LEDs
  showPattern(patterns[patternIndex]);

  // Save current button state
  // This becomes the "previous state" next loop
  lastButton = buttonNow;

  // Should create a small delay to prevent accidental double presses
  delay(50);
}
