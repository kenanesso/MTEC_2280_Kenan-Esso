/*
Kenan Esso 
Short Sketch #1 - Digital Output

  this is attempted template version (I do not have access to a ESP32-S3 Arduino board as of yet) 
  (Concept Demonstration purpose)
  This code represents LED behavior without needing hardware.
*/

// ----- the "Virtual" LED pins -----
int LED1 = 4;
int LED2 = 5;
int LED3 = 6;
int LED4 = 7;

// ----- Variables -----
int pattern = 0;        // this tracks current LED pattern
int delayTime = 500;    // this is a classic timing variable
bool fastSpeed = false; // a speed mode variable


void setup()
{
  // Symbolic setup (this would normally be where the pinMode would go)
  // pinMode(LED1, OUTPUT);
  // pinMode(LED2, OUTPUT);
  // pinMode(LED3, OUTPUT);
  // pinMode(LED4, OUTPUT);
}

void loop()
{
  // ---------- IF / ELSE #1 ----------
  // Check if pattern number is greater than 2
  if (pattern > 2)
  {
    fastSpeed = true;
  }
  else
  {
    fastSpeed = false;
  }

  // ---------- IF / ELSE #2 ----------
  if (fastSpeed == true)
  {
    delayTime = 250;
  }
  else
  {
    delayTime = 500;
  }

  // ---------- 6 UNIQUE PATTERNS ----------
  // In this part, this is pretty much just mixing and matching different patterns
  if (pattern == 0)
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  }
  else if (pattern == 1)
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
  }
  else if (pattern == 2)
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, LOW);
  }
  else if (pattern == 3)
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, HIGH);
  }
  else if (pattern == 4)
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  }
  else if (pattern == 5)
  {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
  }

  delay(delayTime);

  pattern++;

  if (pattern >= 6)
  {
    pattern = 0;
  }
}

/*
Overall, This project shows how to use digitalWrite() to control four LEDs and make six different patterns of on and off that repeat over time. Three variables—current pattern, timing delay, and speed mode—along with if/else lines and a logical comparator are used to change behavior on the fly. The delay() method sets the time between patterns, and the sequence starts over after six states so it can loop forever.
*/
