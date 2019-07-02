/*This is the code for my first Arduino Shield puzzle
   It will include 2 RGB LEDs
   3 Single-color LEDs
   7 buttons (6 color buttons and 1 set button) ***EDIT*** Now only 4 buttons (3 color and 1 set)
   8 dip Switches ***EDIT***Dip Switch 8 removed
   1 Beeper Buzzer ***EDIT***AND_3 with the single-color LEDs
   1  4-digit 7-segment Display ***EDIT*** Removed
 * ***EDIT*** Pull_up Pins: 12,8, 0-7, External Pull_up 13
*/
//************************************************************************************************
//Button Pins:
#define SETBUTTON 2 //interrup vector 0

#define COLORBUTTON1 13
#define COLORBUTTON2 12
#define COLORBUTTON3 8

//DipSwitch Pins:
#define DIPSWITCH1 7
#define DIPSWITCH2 6
#define DIPSWITCH3 5
#define DIPSWITCH4 4
#define DIPSWITCH5 3
#define DIPSWITCH6 1 //swapped with setbutton pin due to needed interrupt pin from pin2.
#define DIPSWITCH7 0

//Single-color LED Pins:
#define LED3 11
#define LED2 10
#define LED1 9

// RBG LED Pins:
#define SIMONRED A0
#define SIMONGREEN A1
#define SIMONBLUE A2

#define PLAYERRED A3
#define PLAYERGREEN A4
#define PLAYERBLUE A5 // connected via a dipswitch.


volatile int setButtonState;         // variable for reading the pushbutton status

uint8_t Simon1; //Upper bound is exclusive
uint8_t Simon2;
uint8_t Simon3;
uint8_t Simon4;
uint8_t Simon5;
uint8_t Simon6;
uint8_t Simon7;

uint8_t Player1; //Upper bound is exclusive
uint8_t Player2;
uint8_t Player3;
uint8_t Player4;
uint8_t Player5;
uint8_t Player6;
uint8_t Player7;

boolean b1;// These boolean values will invert the logic to be able to use active LOW as a trigger for the LEDs without confusion.
boolean b2;
boolean b3;

boolean playerRedState;// Thes booleans will show which color the player LED is on regardless of that buttons were pressed.
boolean playerGreenState;
boolean playerBlueState;

boolean simonRedState1;// Thes booleans will show which color the player LED is on regardless of that buttons were pressed.
boolean simonGreenState1;
boolean simonBlueState1;

boolean simonRedState2;// Thes booleans will show which color the Simon LED is for each level regardless of what Level is currently being displayed
boolean simonGreenState2;
boolean simonBlueState2;

boolean simonRedState3;
boolean simonGreenState3;
boolean simonBlueState3;

boolean simonRedState4;
boolean simonGreenState4;
boolean simonBlueState4;

boolean simonRedState5;
boolean simonGreenState5;
boolean simonBlueState5;

boolean simonRedState6;
boolean simonGreenState6;
boolean simonBlueState6;

boolean simonRedState7;
boolean simonGreenState7;
boolean simonBlueState7;

boolean simonRedState8;
boolean simonGreenState8;
boolean simonBlueState8;

boolean unlock1 = false; // the completion states of the 7 levels.
boolean unlock2 = false;
boolean unlock3 = false;
boolean unlock4 = false;
boolean unlock5 = false;
boolean unlock6 = false;
boolean unlock7 = false;
//************************************************************************************************

void setup() {
  Serial.begin(9600);

  volatile int setButtonState = 0;         // variable for reading the pushbutton status

  Simon1 = random(1, 8); //Upper bound is exclusive
  Simon2 = random(1, 8);
  Simon3 = random(1, 8);
  Simon4 = random(1, 8);
  Simon5 = random(1, 8);
  Simon6 = random(1, 8);
  Simon7 = random(1, 8);

  Player1 = random(1, 7); //Upper bound is exclusive
  Player2 = random(1, 7);
  Player3 = random(1, 7);
  Player4 = random(1, 7);
  Player5 = random(1, 7);
  Player6 = random(1, 7);
  Player7 = random(1, 7);

  //Simon LED Randomized Colors:
  pinMode(PLAYERBLUE, INPUT);//temporary assignment as INPUT to read the floating value.
  randomSeed(analogRead(A5));//We are using DIPSWITCH 8 to disconnect the blue A5 input for the RGB LED and reading it as FLOAT
  pinMode(SETBUTTON, INPUT_PULLUP);

  attachInterrupt(0, pin_ISR, CHANGE);// Attach an interrupt to the ISR vector

  pinMode(COLORBUTTON1, INPUT);// cant be pulled up on Arduino, must use external pull-up.
  pinMode(COLORBUTTON2, INPUT_PULLUP);
  pinMode(COLORBUTTON3, INPUT_PULLUP);

  pinMode(DIPSWITCH7, INPUT_PULLUP);
  pinMode(DIPSWITCH6, INPUT_PULLUP);
  pinMode(DIPSWITCH5, INPUT_PULLUP);
  pinMode(DIPSWITCH4, INPUT_PULLUP);
  pinMode(DIPSWITCH3, INPUT_PULLUP);
  pinMode(DIPSWITCH2, INPUT_PULLUP);
  pinMode(DIPSWITCH1, INPUT_PULLUP);

  pinMode(LED3, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED1, OUTPUT);

  pinMode(SIMONRED, OUTPUT);
  pinMode(SIMONGREEN, OUTPUT);
  pinMode(SIMONBLUE, OUTPUT);

  pinMode(PLAYERRED, OUTPUT);
  pinMode(PLAYERGREEN, OUTPUT);
  pinMode(PLAYERBLUE, OUTPUT);
}
//************************************************************************************************

void pin_ISR() { //this function runs when the setButton is pressed
  //check the dipswitches to see what level to pass and check for.
  Serial.println("BUTTON PRESS DETECTED");
  if (digitalRead(DIPSWITCH7) == LOW) { //active low level7
    playerSelect(Player7);//turn on player LED using whatever button pattern is for level 7.
    //Check the player Red/Green/Blue states and compare to the Simon Red/Green/Blue states for each level.
    if (playerRedState == simonRedState7 && playerGreenState == simonGreenState7 && playerBlueState == simonBlueState7) {
      //for testing purposes we will activate the beeper whenever a comnination is succesful.
      digitalWrite(LED3, HIGH); //111
      digitalWrite(LED2, HIGH);
      digitalWrite(LED1, HIGH);
      unlock7 = true;
    }

  }
  else if (digitalRead(DIPSWITCH6) == LOW) {
    playerSelect(Player6);
    if (playerRedState == simonRedState6 && playerGreenState == simonGreenState6 && playerBlueState == simonBlueState6) {
      //for testing purposes we will activate the beeper whenever a comnination is succesful.
      digitalWrite(LED3, HIGH); //111
      digitalWrite(LED2, HIGH);
      digitalWrite(LED1, HIGH);
      unlock6 = true;
    }
  }
  else if (digitalRead(DIPSWITCH5) == LOW) {
    playerSelect(Player5);
    if (playerRedState == simonRedState5 && playerGreenState == simonGreenState5 && playerBlueState == simonBlueState5) {
      //for testing purposes we will activate the beeper whenever a comnination is succesful.
      digitalWrite(LED3, HIGH); //111
      digitalWrite(LED2, HIGH);
      digitalWrite(LED1, HIGH);
      unlock5 = true;
    }
  }
  else if (digitalRead(DIPSWITCH4) == LOW) {
    playerSelect(Player4);
    if (playerRedState == simonRedState4 && playerGreenState == simonGreenState4 && playerBlueState == simonBlueState4) {
      //for testing purposes we will activate the beeper whenever a comnination is succesful.
      digitalWrite(LED3, HIGH); //111
      digitalWrite(LED2, HIGH);
      digitalWrite(LED1, HIGH);
      unlock4 = true;
    }
  }
  else if (digitalRead(DIPSWITCH3) == LOW) {
    playerSelect(Player3);
    if (playerRedState == simonRedState3 && playerGreenState == simonGreenState3 && playerBlueState == simonBlueState3) {
      //for testing purposes we will activate the beeper whenever a comnination is succesful.
      digitalWrite(LED3, HIGH); //111
      digitalWrite(LED2, HIGH);
      digitalWrite(LED1, HIGH);
      unlock3 = true;
    }
  }
  else if (digitalRead(DIPSWITCH2) == LOW) {
    playerSelect(Player2);
    if (playerRedState == simonRedState2 && playerGreenState == simonGreenState2 && playerBlueState == simonBlueState2) {
      //for testing purposes we will activate the beeper whenever a comnination is succesful.
      digitalWrite(LED3, HIGH); //111
      digitalWrite(LED2, HIGH);
      digitalWrite(LED1, HIGH);
      unlock2 = true;
    }
  }
  else if (digitalRead(DIPSWITCH1) == LOW) {
    playerSelect(Player1);
    if (playerRedState == simonRedState1 && playerGreenState == simonGreenState1 && playerBlueState == simonBlueState1) {
      //for testing purposes we will activate the beeper whenever a comnination is succesful.
      digitalWrite(LED3, HIGH); //111
      digitalWrite(LED2, HIGH);
      digitalWrite(LED1, HIGH);
      unlock1 = true;
    }
  }
  Serial.println("DipSwitch1: " + (digitalRead(DIPSWITCH1) == LOW));
  Serial.println("DipSwitch2: " + (digitalRead(DIPSWITCH2) == LOW));
  Serial.println("DipSwitch3: " + (digitalRead(DIPSWITCH3) == LOW));
  Serial.println("DipSwitch4: " + (digitalRead(DIPSWITCH4) == LOW));
  Serial.println("DipSwitch5: " + (digitalRead(DIPSWITCH5) == LOW));
  Serial.println("DipSwitch6: " + (digitalRead(DIPSWITCH6) == LOW));
  Serial.println("DipSwitch7: " + (digitalRead(DIPSWITCH7) == LOW));
}
//************************************************************************************************
void loop() {
  if (unlock1 && unlock2 && unlock3 && unlock4 && unlock5 && unlock6 && unlock7) {
    while (true) { // if all of the levels are completed it will beep forever (This is just for testing).
      digitalWrite(LED3, HIGH); //111 All on should activate beep.
      digitalWrite(LED2, HIGH);
      digitalWrite(LED1, HIGH);
      Serial.println("ALL LEVELS COMEPLETED");
    }
  }
  //Level: 1
  digitalWrite(LED3, LOW); //001
  digitalWrite(LED2, LOW);
  digitalWrite(LED1, HIGH);
  simonSelect(Simon1);
  Serial.println("Simon1 Sent: " + Simon1);
  delay(1500);//Wait for 1.5 seconds

  //Level: 2
  digitalWrite(LED3, LOW); //010
  digitalWrite(LED2, HIGH);
  digitalWrite(LED1, LOW);
  simonSelect(Simon2);
  Serial.println("Simon2 Sent: " + Simon2);
  delay(1500);//Wait for 1.5 seconds

  //Level: 3
  digitalWrite(LED3, LOW); //011
  digitalWrite(LED2, HIGH);
  digitalWrite(LED1, HIGH);
  simonSelect(Simon3);
  Serial.println("Simon3 Sent: " + Simon3);
  delay(1500);//Wait for 1.5 seconds

  //Level: 4
  digitalWrite(LED3, HIGH); //100
  digitalWrite(LED2, LOW);
  digitalWrite(LED1, LOW);
  simonSelect(Simon4);
  Serial.println("Simon4 Sent: " + Simon4);
  delay(1500);//Wait for 1.5 seconds

  //Level: 5
  digitalWrite(LED3, HIGH); //101
  digitalWrite(LED2, LOW);
  digitalWrite(LED1, HIGH);
  simonSelect(Simon5);
  Serial.println("Simon5 Sent: " + Simon5);
  delay(1500);//Wait for 1.5 seconds

  //Level: 6
  digitalWrite(LED3, HIGH); //110
  digitalWrite(LED2, HIGH);
  digitalWrite(LED1, LOW);
  simonSelect(Simon6);
  Serial.println("Simon6 Sent: " + Simon6);
  delay(1500);//Wait for 1.5 seconds

  //Level: 7
  digitalWrite(LED3, HIGH); //111
  digitalWrite(LED2, HIGH);
  digitalWrite(LED1, HIGH);
  simonSelect(Simon7);
  Serial.println("Simon7 Sent: " + Simon7);
  delay(1500);//Wait for 1.5 seconds

}
//************************************************************************************************
//Displays a color combination on the Simon LED based on the value Int passed 1-7.
void simonSelect(int selectedColor) { // must be 1-7
  Serial.println("Simon Received: " + selectedColor);
  switch (selectedColor) {
    case 1: //BLUE
      digitalWrite(SIMONRED, LOW);
      digitalWrite(SIMONGREEN, LOW);
      digitalWrite(SIMONBLUE, HIGH);
      simonRedState1 = false;
      simonGreenState1 = false;
      simonBlueState1 = true;
      break;
    case 2: //GREEN
      digitalWrite(SIMONRED, LOW);
      digitalWrite(SIMONGREEN, HIGH);
      digitalWrite(SIMONBLUE, LOW);
      simonRedState2 = false;
      simonGreenState2 = true;
      simonBlueState2 = false;
      break;
    case 3: //CYAN
      digitalWrite(SIMONRED, LOW);
      digitalWrite(SIMONGREEN, HIGH);
      digitalWrite(SIMONBLUE, HIGH);
      simonRedState3 = false;
      simonGreenState3 = true;
      simonBlueState3 = true;
      break;
    case 4: //RED
      digitalWrite(SIMONRED, HIGH);
      digitalWrite(SIMONGREEN, LOW);
      digitalWrite(SIMONBLUE, LOW);
      simonRedState4 = true;
      simonGreenState4 = false;
      simonBlueState4 = false;
      break;
    case 5: //MAGENTA
      digitalWrite(SIMONRED, HIGH);
      digitalWrite(SIMONGREEN, LOW);
      digitalWrite(SIMONBLUE, HIGH);
      simonRedState5 = true;
      simonGreenState5 = false;
      simonBlueState5 = true;
      break;
    case 6: //YELLOW
      digitalWrite(SIMONRED, HIGH);
      digitalWrite(SIMONGREEN, HIGH);
      digitalWrite(SIMONBLUE, LOW);
      simonRedState6 = true;
      simonGreenState6 = true;
      simonBlueState6 = false;
      break;
    case 7: //WHITE
      digitalWrite(SIMONRED, HIGH);
      digitalWrite(SIMONGREEN, HIGH);
      digitalWrite(SIMONBLUE, HIGH);
      simonRedState7 = true;
      simonGreenState7 = true;
      simonBlueState7 = true;
      break;
    default: //turn all OFF as default
      digitalWrite(SIMONRED, LOW);
      digitalWrite(SIMONGREEN, LOW);
      digitalWrite(SIMONBLUE, LOW);
      Serial.println("Simon Sent IS INVALID : " + selectedColor );
  }
}

// this method takes a case, and activates the color of player LED based on which buttons are pressed at the time of call.
//************************************************************************************************
void playerSelect(int buttonPatternSelector) { // must be 1-6
  Serial.println("player Signal received: " + buttonPatternSelector);
  if (digitalRead(COLORBUTTON1) == LOW)// we invert the button boolean value because we are using a pulled up acctive low input.
    b1 = HIGH;
  else
    b1 = LOW;
  if (digitalRead(COLORBUTTON2) == LOW)
    b2 = HIGH;
  else
    b2 = LOW;
  if (digitalRead(COLORBUTTON3) == LOW)
    b3 = HIGH;
  else
    b3 = LOW;

  Serial.println("b1 state: " + b1);
  Serial.println("b2 state: " + b2);
  Serial.println("b3 state: " + b3);

  switch (buttonPatternSelector) {
    case 1: //R G B
      digitalWrite(PLAYERRED, b1);
      digitalWrite(PLAYERGREEN, b2);
      digitalWrite(PLAYERBLUE, b3);
      playerRedState = b1;
      playerGreenState = b2;
      playerBlueState = b3;
      break;
    case 2: //R B G
      digitalWrite(PLAYERRED, b1);
      digitalWrite(PLAYERBLUE, b2);
      digitalWrite(PLAYERGREEN, b3);
      playerRedState = b1;
      playerBlueState = b2;
      playerGreenState = b3;
      break;
    case 3: //G R B
      digitalWrite(PLAYERGREEN, b1);
      digitalWrite(PLAYERRED, b2);
      digitalWrite(PLAYERBLUE, b3);
      playerGreenState = b1;
      playerRedState = b2;
      playerBlueState = b3;
      break;
    case 4: //G B R
      digitalWrite(PLAYERGREEN, b1);
      digitalWrite(PLAYERBLUE, b2);
      digitalWrite(PLAYERRED, b3);
      playerGreenState = b1;
      playerBlueState = b2;
      playerRedState = b3;
      break;
    case 5: //B G R
      digitalWrite(PLAYERBLUE, b1);
      digitalWrite(PLAYERGREEN, b2);
      digitalWrite(PLAYERRED, b3);
      playerBlueState = b1;
      playerGreenState = b2;
      playerRedState = b3;
      break;
    case 6: //B R G
      digitalWrite(PLAYERBLUE, b1);
      digitalWrite(PLAYERRED, b2);
      digitalWrite(PLAYERGREEN, b3);
      playerBlueState = b1;
      playerRedState = b2;
      playerGreenState = b3;
      break;
    default: // If anything else is passed we must communicate error. For now it's just RGB with no player state booleans.
      digitalWrite(PLAYERRED, b1);
      digitalWrite(PLAYERGREEN, b2);
      digitalWrite(PLAYERBLUE, b3);
      Serial.println("Player State INVALID" + buttonPatternSelector );
  }
}
//************************************************************************************************
