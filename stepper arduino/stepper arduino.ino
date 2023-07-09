/*
* Project: Biereinschenkautomat 
* Date: 08.05.2023
* Hardware: Arduino Uno
*/

// preprocessor 
#define DIR  6
#define STEP  7
#define STEPS_PER_REV  2000 

#define DIR2  4    // Stepper 2 
#define STEP2  5
#define STEPS_PER_REV2  2000
//Debug macro, Enabled for checking the functionality of Switches 
#define DEBUG

// datatypes
typedef enum{
  UNINITIALIZED = 0,
  INITIALIZING,
  IDLE,
  ACTIVE,
  ERROR
}SMState_Type;

//Function declaration
void BeerPouringRoutine(void);
void StartSwitchON(void);
void StartSwitchOFF(void);
void EmergencyStopON(void);
void EmergencyStopOFF(void);
void Ranfuehren(void);  
void Einschenken(void);
void Hefeextrahieren(void);
void Hefeeinschenken(void);
void Fertigstellen(void);
void movetoStart(void);

//Pin declaration
const int EmergencySwitch = 2; // interrupt pin 
const int StartSwitch = 3; // interrupt pin 
const int EndSwitchStep1Start = 10;
const int EndSwitchStep1End = 11;
const int EndSwitchStep2Start = 12;
const int EndSwitchStep2End = 13;

//variable declaration
SMState_Type SMState = UNINITIALIZED;
volatile bool EmergencySwitchStatus = true;
volatile bool StartSwitchStatus = false;
volatile bool isReferencedStep1 = false;
volatile bool isReferencedStep2 = false;
int rev = 5;

int i = 0;
int d = 0;
int b = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("Startet Biereinschenkautomat");
  
  pinMode(EmergencySwitch, INPUT);
  pinMode(EmergencySwitch, HIGH);
  pinMode(StartSwitch, INPUT);
  pinMode(StartSwitch, HIGH);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(STEP2, OUTPUT);
  pinMode(DIR2, OUTPUT);

  // attachInterrupt(digitalPinToInterrupt(EmergencySwitch), EmergencyStopON, RISING);
  attachInterrupt(digitalPinToInterrupt(EmergencySwitch), EmergencyStopOFF, FALLING);
  attachInterrupt(digitalPinToInterrupt(StartSwitch), StartSwitchON, RISING);
  attachInterrupt(digitalPinToInterrupt(StartSwitch), StartSwitchOFF, FALLING);
  
  Serial.println("Pins configured");

  if(digitalRead(EmergencySwitch) != HIGH)
  {
    EmergencySwitchStatus = true;
    Serial.println("Emergency Stop is PRESSED");
  }
  else
  {
    EmergencySwitchStatus = false;
    Serial.println("Emergency Stop is NOT pressed");
  }

  if(digitalRead(StartSwitch) != HIGH)
  {
    StartSwitchStatus = false;
    Serial.println("Start is PRESSED");
  }
  else
  {
    StartSwitchStatus = true;
    Serial.println("Start is NOT pressed");
  }

  Serial.println("Setup done");
  Serial.println("-------------------------------------------");
}

void loop()
{ 
#ifdef DEBUG
  // run BeerPouringroutine when start button is pressed and Emergency Switch is not pressed 
  // Serial.print("start: ");
  // Serial.print(digitalRead(StartSwitch));
  // Serial.print(", start Status: ");
  // // Serial.print(",");
  // Serial.print(StartSwitchStatus);
  // // Serial.print(",");
  // Serial.print(", EM Stop: ");
  // Serial.print(digitalRead(EmergencySwitch));
  // // Serial.print(",");
  // Serial.print(", EM Status: ");
  // Serial.println(EmergencySwitchStatus);
#endif
  Statemachine();
}

void Statemachine(void)
{
  switch (SMState)
  {
  case UNINITIALIZED:
    SM_Uninitialized();
    break;
  case INITIALIZING:
    SM_Initializing();
    break;
  case IDLE:
    SM_Idle();
    break;
  case ACTIVE:
    SM_Active();
    break;
  case ERROR:
    SM_Error();
    break;
  default:
    SMState = ERROR;
    break;
  }
}

void EmergencyStopOFF(void)
{
  //Switch off Stepper
  digitalWrite(STEP, HIGH);
  digitalWrite(STEP2, HIGH);
  EmergencySwitchStatus = false;
  // delay(500);
  Serial.println("EM Stop OFF");
  i++;
  Serial.print("i:");
  Serial.println(i);
}

void StartSwitchON(void)
{
  digitalWrite(STEP, HIGH);
  digitalWrite(STEP2, HIGH);
  StartSwitchStatus = true;
  // delay(500);
  Serial.println("Start ON");
  b++;
  Serial.print("b:");
  Serial.println(b);
}

void StartSwitchOFF(void)
{
  digitalWrite(STEP, LOW);
  digitalWrite(STEP2, LOW);
  StartSwitchStatus = false;
  // delay(500);
  Serial.println("Start OFF");
  d++;
  Serial.print("d:");
  Serial.println(d);
}

void BeerPouringRoutine(void)
{  
  // Serial.println("Spinning Clockwise...");
  digitalWrite(DIR, HIGH);
  digitalWrite(DIR2, HIGH);
  Ranfuehren(); 

  // Serial.print("Spinning Clockwise...");
  digitalWrite(DIR, LOW);
  digitalWrite(DIR2, HIGH); 
  Einschenken();

  // Serial.print("Spinning Clockwise...");
  digitalWrite(DIR, LOW);
  digitalWrite(DIR2, LOW); 
  Hefeextrahieren();

  // Serial.print("Spinning Clockwise...");
  digitalWrite(DIR, LOW);
  digitalWrite(DIR2, HIGH); 
  Hefeeinschenken();

  // Serial.print("Spinning Clockwise...");
  digitalWrite(DIR, LOW);
  digitalWrite(DIR2, LOW); 
  Fertigstellen();
}

void Ranfuehren(void)
{
  for(int i = 0; i<STEPS_PER_REV && !EmergencySwitchStatus; i++) 
  { 
    digitalWrite(STEP, HIGH);
    digitalWrite(STEP2, HIGH);  
    delayMicroseconds(1000);
    digitalWrite(STEP, LOW);
    digitalWrite(STEP2, LOW);
    delayMicroseconds(1000);
  } 
}

void Einschenken(void)
{
  for(int i = 0; i<STEPS_PER_REV && !EmergencySwitchStatus; i++) 
  {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(1500);
    digitalWrite(STEP, LOW); 
    delayMicroseconds(1500);
    digitalWrite(STEP2, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP2, LOW);  
    delayMicroseconds(1000);
  }
}

void Hefeextrahieren(void)
{
  for(int i = 0; i<STEPS_PER_REV && !EmergencySwitchStatus; i++) 
  {
    digitalWrite(STEP2, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP2, LOW);   
    delayMicroseconds(1000);
  }
}

void Hefeeinschenken(void)
{
  for(int i = 0; i<STEPS_PER_REV && !EmergencySwitchStatus; i++) 
  {   
    digitalWrite(STEP2, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP2, LOW);
    delayMicroseconds(1000);
  }
}

void Fertigstellen(void)
{
  for(int i = 0; i<STEPS_PER_REV && !EmergencySwitchStatus; i++) 
  {   
    digitalWrite(STEP, HIGH);
    digitalWrite(STEP2, HIGH);    
    delayMicroseconds(1000);
    digitalWrite(STEP, LOW);
    digitalWrite(STEP2, LOW);
    delayMicroseconds(1000);
  }  
}

void movetoStart(void)
{
  if(!isReferencedStep1 || !isReferencedStep2)
  {
    digitalWrite(DIR, HIGH);
    digitalWrite(DIR2, HIGH);

    if(LOW != digitalRead(EndSwitchStep1Start))
    {
      digitalWrite(STEP, HIGH);
      delayMicroseconds(100);
      digitalWrite(STEP, LOW);
      delayMicroseconds(100);
    }
    else
    {
      isReferencedStep1 = true;
    }
    if(LOW != digitalRead(EndSwitchStep2Start))
    {
      digitalWrite(STEP2, HIGH);
      delayMicroseconds(100);
      digitalWrite(STEP2, LOW);
      delayMicroseconds(100);
    }
    else
    {
      isReferencedStep2 = true;
    }
  }
}

void SM_Uninitialized(void)
{
  // Serial.println("SM: Uninitialized");
  SMState = INITIALIZING;
}

void SM_Initializing(void)
{
  // Serial.println("SM: Initializing");
  if(!isReferencedStep1 || !isReferencedStep2)
  {
    movetoStart();
  }
  else
  {
    SMState = IDLE;
  }
}

void SM_Idle(void)
{
  // Serial.println("SM: Idle");
  if(StartSwitchStatus)
  {
    SMState = ACTIVE;
  } 
}

void SM_Active(void)
{
  // Serial.println("SM: Active");
  BeerPouringRoutine();
}

void SM_Error(void)
{
  Serial.println("SM: Error");
}