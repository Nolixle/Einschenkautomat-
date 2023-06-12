#define DIR  6
#define STEP  7
#define STEPS_PER_REV  2000 

#define DIR2  4    // Stepper 2 
#define STEP2  5
#define STEPS_PER_REV2  2000

void BeerPouringRoutine(void);
// void StartSwitchISR(void);
void StartSwitchON(void);
void StartSwitchOFF(void);
// void EmergencyStopISR(void);
void EmergencyStopON(void);
void EmergencyStopOFF(void);
void ErrorState(void);
void EmergencyStopPressed(void);
void Ranfuehren(void);  
void Einschenken(void);
void Hefeextrahieren(void);
void Hefeextrahieren2(void);
void Hefeextrahieren3(void);
void Hefeeinschenken(void);
void Fertigstellen(void);

const int EmergencySwitch = 2; //real interrupt pin 
bool EmergencySwitchStatus = true;
const int StartSwitch = 3; //real interrupt pin 
bool StartSwitchStatus = false;

int rev = 5;


void setup()
{
  Serial.begin(115200);
  Serial.println("Startet Biereinschenkautomat");
  
  pinMode(EmergencySwitch, INPUT);
  pinMode(EmergencySwitch, LOW);
  pinMode(StartSwitch, INPUT);
  pinMode(StartSwitch, LOW);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(STEP2, OUTPUT);   
  pinMode(DIR2, OUTPUT);

  //attachInterrupt(digitalPinToInterrupt(EmergencySwitch), EmergencyStopISR, FALLING);
  //attachInterrupt(digitalPinToInterrupt(StartSwitch), StartSwitchISR, RISING);
  
  Serial.println("Pins configured");

  if(digitalRead(EmergencySwitch) != HIGH)
  {
    EmergencySwitchStatus = true;
    Serial.println("Emergency Stop is PRESSED");
  }
  else{
    EmergencySwitchStatus = false;
    Serial.println("Emergency Stop is NOT pressed");
  }

  if(digitalRead(StartSwitch) != HIGH)
  {
    StartSwitchStatus = false;
    Serial.println("Start is PRESSED");
  }
  else{
    StartSwitchStatus = true;
    Serial.println("Start is NOT pressed");
  }

  Serial.println("Initializing done");
  Serial.println("-------------------------------------------");
}


void loop()
{ 

  //run BeerPouringroutine when start button is pressed and Emergency Switch is not pressed 
  // Serial.print("start: ");
  // Serial.println(digitalRead(2));
  // Serial.print("stop: ");
  // Serial.println(digitalRead(3));

  if(HIGH == digitalRead(StartSwitch))
  {
    StartSwitchON();
  }
  else
  {
    StartSwitchOFF();
  }
  if(HIGH == digitalRead(EmergencySwitch))
  {
    EmergencyStopON();
  }
  else
  {
    EmergencyStopOFF();
  }

  if(true != EmergencySwitchStatus && true == StartSwitchStatus)
  {
    BeerPouringRoutine();
  }
  else if(false == StartSwitchStatus) //Status messages 
  {
    Serial.println("Start Switch not pressed");
  }
   else if(true == EmergencySwitchStatus)
  {
    Serial.println("Emergency Switch pressed");
  }
}

void EmergencyStopON(void)
{
  //Switch off Stepper
  digitalWrite(STEP, LOW);
  digitalWrite(STEP2, LOW);
  EmergencySwitchStatus = true;
  // Serial.println("Stop ON");
}

void EmergencyStopOFF(void)
{
  //Switch off Stepper
  digitalWrite(STEP, HIGH);
  digitalWrite(STEP2, HIGH);
  EmergencySwitchStatus = false;
  // Serial.println("Stop OFF");
}


void StartSwitchON(void)
{
  //only if System is not Busy start new iteration of Beer
  digitalWrite(STEP, HIGH);
  digitalWrite(STEP2, HIGH);
  StartSwitchStatus = true;
  // Serial.println("Start ON");
}

void StartSwitchOFF(void)
{
  //only if System is not Busy start new iteration of Beer
  digitalWrite(STEP, LOW);
  digitalWrite(STEP2, LOW);
  StartSwitchStatus = false;
  // Serial.println("Start OFF");
}

void BeerPouringRoutine(void)
{  
  Serial.println("Spinning Clockwise...");
  digitalWrite(DIR, HIGH);
  digitalWrite(DIR2, HIGH);
  Ranfuehren(); 

  Serial.print("Spinning Clockwise...");
  digitalWrite(DIR, LOW);
  digitalWrite(DIR2, HIGH); 
  Einschenken();

  Serial.print("Spinning Clockwise...");
  digitalWrite(DIR, LOW);
  digitalWrite(DIR2, LOW); 
  Hefeextrahieren();

  Serial.print("Spinning Clockwise...");
  digitalWrite(DIR, HIGH);
  digitalWrite(DIR2, HIGH); 
  Hefeextrahieren2();

  Serial.print("Spinning Clockwise...");
  digitalWrite(DIR, LOW);
  digitalWrite(DIR2, LOW); 
  Hefeextrahieren3();

  Serial.print("Spinning Clockwise...");
  digitalWrite(DIR, LOW);
  digitalWrite(DIR2, HIGH); 
  Hefeeinschenken();

  Serial.print("Spinning Clockwise...");
  digitalWrite(DIR, LOW);
  digitalWrite(DIR2, LOW); 
  Fertigstellen();
}

void Ranfuehren(void)
{
  for(int i = 0; i<STEPS_PER_REV; i++) 
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
  for(int i = 0; i<STEPS_PER_REV; i++) 
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
  for(int i = 0; i<STEPS_PER_REV; i++) 
  {
    digitalWrite(STEP2, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP2, LOW);   
    delayMicroseconds(1000);
  }
}
void Hefeextrahieren2(void)
{
  for(int i = 0; i<STEPS_PER_REV; i++) 
  {
  digitalWrite(STEP2, HIGH);
  delayMicroseconds(1000);
  digitalWrite(STEP2, LOW);
  delayMicroseconds(1000);
  }
}

void Hefeextrahieren3(void)
{
  for(int i = 0; i<STEPS_PER_REV; i++) 
  {
  digitalWrite(STEP2, HIGH);
  delayMicroseconds(1000);
  digitalWrite(STEP2, LOW);
  delayMicroseconds(1000);
  }
}

void Hefeeinschenken(void)
{
  for(int i = 0; i<STEPS_PER_REV; i++) 
  {   
    digitalWrite(STEP2, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP2, LOW);
    delayMicroseconds(1000);
  }
}

void Fertigstellen(void)
{
  for(int i = 0; i<STEPS_PER_REV; i++) 
  {   
    digitalWrite(STEP, HIGH);
    digitalWrite(STEP2, HIGH);    
    delayMicroseconds(1000);
    digitalWrite(STEP, LOW);
    digitalWrite(STEP2, LOW);
    delayMicroseconds(1000);
  }  
}
