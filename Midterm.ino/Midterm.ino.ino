/*
Kenan Esso
MTEC 2280 Physical Computing
Professor Ian Porkorny

MIDTERM

Concept: Red Light/Green Light User Game Experience


Taking the ordinary Red Light/Green Light game and fitting it into a more matured version, physical computing style!
The light flashes 3 times to indicate the starting of the game.
The user presses button during GREEN light.
If they press during RED light, they lose.

Situation	                    Result
Button + Green	              Correct
Button + Red	                 Wrong
No press	                    Nothing


*/

//Pins
int buttonPin = 2;
int redLED = 4;
int greenLED = 9;
int buzzer = 10;
int potPin = A0;



//Variables
int buttonState = 0;                  // this stores data of button presses
int potValue = 0;                     // this is the potentiometer value (Reads the knob position. This changes how fast the game switches between red and green.)
unsigned long previousTime = 0;       // used for millis timer
int gameInterval = 2000;              // default time between changes




// Array to store LED pins
int ledArray[2] = {8, 9};


bool greenState = true;     // tracks whether game is green or red



void setup() 
{
  Serial.begin(115200);   // used for debugging

  // set LED pins as OUTPUT
  for (int i = 0; i < 2; i++)
  {
    pinMode(ledArray[i], OUTPUT);
  }

  // button input
  pinMode(buttonPin, INPUT_PULLUP);

  // buzzer output
  pinMode(buzzer, OUTPUT);  

  // Game starting countdown (three flashes to start)
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

void loop() 

{
  // Read the potentiometer
  potValue = analogRead(potPin);

  // map pot value to game speed
  gameInterval = map(potValue, 0, 1023, 500, 3000);

  // Read button input
  buttonState = digitalRead(buttonPin); // "digitalRead" Reads whether the player pressed the button.

  // Timer using millis instead of delay, I think it would be more effective for the scenario
  unsigned long currentTime = millis();

  if (currentTime - previousTime >= gameInterval)
  {

    previousTime = currentTime;

    // change game state
    greenState = !greenState; // GREEN → RED → GREEN → RED are the alternating colors the game will flip between

  }

  //LED Output Logic
   if (greenState == true)
  {

    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);

  }

  else
  {

    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);

  }

  //This is where the button Logic gets assessed.

    // button pressed AND green light
  if (buttonState == LOW && greenState == true)
  {

    Serial.println("Correct press!");

//    analogWrite(buzzer, 150);

  }

  // button pressed AND red light
  else if (buttonState == LOW && greenState == false)
  {

    Serial.println("Wrong press!");

    // beep pattern
    for (int i = 0; i < 3; i++)
    {

//      digitalWrite(buzzer, HIGH);
      delay(100);

      digitalWrite(buzzer, LOW);
      delay(100);

    }

  }


  // if nothing happens
  else
  {

    analogWrite(buzzer, 0);

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
Buzzer Feedback
*/