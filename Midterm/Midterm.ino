/*
Kenan Esso
MTEC 2280 Physical Computing
Professor Ian Porkorny

MIDTERM UPDATED VERSION

Concept: Red Light/Green Light User Game Experience


Taking the ordinary Red Light/Green Light game and fitting it into a more matured version, physical computing style!
The user presses button during GREEN light.
If they press during RED light, they lose.

Red Light / Green Light Game
Features:
- Score system
- Random timing
- Potentiometer difficulty control
- PRESS & HOLD interaction
- Score only resets if player HOLDS during RED
*/

// ---------------------------
// PINS
// ---------------------------
int buttonPin = 2;
int redLED = 4;
int greenLED = 5;
int potPin = 1;

// ---------------------------
// VARIABLES
// ---------------------------
int buttonState = 0;
int potValue = 0;

unsigned long previousTime = 0;
int gameInterval = 2000;

bool greenState = true;

int score = 0;

// For hold detection
unsigned long holdStart = 0;
bool holding = false;

// LED array
int ledArray[2] = {4, 9};

// how long player must hold button
int holdTime = 300;


// ---------------------------
// SETUP
// ---------------------------
void setup()
{
  Serial.begin(115200);

  // set LEDs as outputs using array + for loop
  for (int i = 0; i < 2; i++)
  {
    pinMode(ledArray[i], OUTPUT);
  }

  // button input
  pinMode(buttonPin, INPUT_PULLUP);

  // start random timing
  randomSeed(analogRead(A1));

  // countdown before game starts
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, HIGH);
    delay(300);

    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    delay(300);
  }
}


// ---------------------------
// LOOP
// ---------------------------
void loop()
{
  // ---------------------------
  // READ INPUTS
  // ---------------------------
  potValue = analogRead(potPin);
  buttonState = digitalRead(buttonPin);

  // ---------------------------
  // POTENTIOMETER = DIFFICULTY
  // controls speed + randomness
  // ---------------------------
  int baseSpeed = map(potValue, 0, 1023, 800, 2500);
  int randomness = map(potValue, 0, 1023, 200, 1500);

  gameInterval = random(baseSpeed, baseSpeed + randomness);

  // ---------------------------
  // TIMER USING MILLIS
  // ---------------------------
  unsigned long currentTime = millis();

  if (currentTime - previousTime >= gameInterval)
  {
    previousTime = currentTime;
    greenState = !greenState;

    // print instruction when GREEN starts
    if (greenState == true)
    {
      Serial.println("GREEN! Press and HOLD!");
    }
    else
    {
      Serial.println("RED! Do not hold!");
    }
  }

  // ---------------------------
  // LIGHT OUTPUT
  // ---------------------------
  if (greenState == true)
  {
    digitalWrite(redLED, LOW);
    analogWrite(greenLED, 180);   // analog output / PWM
  }
  else
  {
    analogWrite(greenLED, 0);
    digitalWrite(redLED, HIGH);
  }

  // ---------------------------
  // HOLD LOGIC
  // ---------------------------

  // if button is currently pressed
  if (buttonState == LOW)
  {
    // start hold timing once
    if (holding == false)
    {
      holding = true;
      holdStart = millis();
    }

    // ---------------------------
    // CORRECT: holding during GREEN
    // ---------------------------
    if (greenState == true)
    {
      if (millis() - holdStart > holdTime)
      {
        score++;

        Serial.print("Correct! Score: ");
        Serial.println(score);

        // green success flash
        for (int i = 0; i < 2; i++)
        {
          analogWrite(greenLED, 255);
          delay(120);
          analogWrite(greenLED, 80);
          delay(120);
        }

        // reset hold so one hold = one score
        holding = false;
      }
    }

    // ---------------------------
    // WRONG: only fail if holding during RED long enough
    // ---------------------------
    else
    {
      if (millis() - holdStart > holdTime)
      {
        Serial.println("Wrong! Score Reset.");
        score = 0;

        // red error flash
        for (int i = 0; i < 3; i++)
        {
          digitalWrite(redLED, LOW);
          delay(120);
          digitalWrite(redLED, HIGH);
          delay(120);
        }

        // reset hold after fail
        holding = false;
      }
    }
  }

  // button released
  else
  {
    holding = false;
  }
}



/*
"This project recreates the Red Light Green Light game using a microcontroller.
The player must press the button only when the green LED is on.
If they press during red, the buzzer plays an error sound.
The potentiometer controls how fast the game changes speed.
The system measures button input and processes it using conditional logic."

This program demonstrates:

digitalRead()
digitalWrite()
analogRead()
analogWrite()
arrays
if / else
logical operators
millis() timer
for loop



INPUTS
Potentiometer
Button

PROCESS
Arduino Microcontroller

OUTPUTS
LED Signals
*/