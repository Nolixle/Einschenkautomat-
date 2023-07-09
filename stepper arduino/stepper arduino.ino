#define DIR  6
#define STEP  7
#define STEPS_PER_REV  2000
int enPIN = 8;

#define DIR2  4    // Stepper 2 
#define STEP2  5
#define STEPS_PER_REV2  5000
int enPIN2 = 12; 

int stps16=102400;// Steps to move
int stps5=32000;

// #define DEBUG

void BeerPouringRoutine(void);
void StartSwitchISR(void);
void EmergencyStopISR(void);
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
  pinMode(enPIN, OUTPUT);
  pinMode(enPIN2, OUTPUT);
  digitalWrite(enPIN, LOW);
  digitalWrite(enPIN2, LOW);

  attachInterrupt(digitalPinToInterrupt(EmergencySwitch), EmergencyStopISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(StartSwitch), StartSwitchISR, RISING);
  
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

  Serial.println("Initializing done");
  Serial.println("-------------------------------------------");
}


void loop()
{ 
#ifdef DEBUG
  // run BeerPouringroutine when start button is pressed and Emergency Switch is not pressed 
  Serial.print("start: ");
  Serial.println(digitalRead(StartSwitch));
  Serial.print("stop: ");
  Serial.println(digitalRead(EmergencySwitch));
#endif

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

void EmergencyStopISR(void)
{
  //Switch off Stepper
  digitalWrite(STEP, LOW);
  digitalWrite(STEP2, LOW);
  EmergencySwitchStatus = true;
  Serial.println("EMStop ON");
}

void StartSwitchISR(void)
{
  //only if System is not Busy start new iteration of Beer
  digitalWrite(STEP, LOW);
  digitalWrite(STEP2, LOW);
  StartSwitchStatus = true;
  Serial.println("Start ON");
}

void BeerPouringRoutine(void)
{  
  Serial.println("Spinning Clockwise...");
  digitalWrite(DIR, LOW);
  digitalWrite(DIR2, LOW);
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
  for(int i = 0; i<STEPS_PER_REV*19 && !EmergencySwitchStatus; i++) 
  { 
    digitalWrite(STEP, HIGH);
    digitalWrite(STEP2, HIGH);  
    delayMicroseconds(200);
    digitalWrite(STEP, LOW);
    digitalWrite(STEP2, LOW);
    delayMicroseconds(200);
  } 
}

void Einschenken(void)
{
  for(int i = 0; i<STEPS_PER_REV*5 && !EmergencySwitchStatus; i++) 
  {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(200);
    digitalWrite(STEP, LOW); 
    delayMicroseconds(200);
    digitalWrite(STEP2, HIGH);
    delayMicroseconds(200);
    digitalWrite(STEP2, LOW);  
    delayMicroseconds(200);
  }
}

void Hefeextrahieren(void)
{
  for(int i = 0; i<STEPS_PER_REV*5 && !EmergencySwitchStatus; i++) 
  {
    digitalWrite(STEP2, HIGH);
    delayMicroseconds(200);
    digitalWrite(STEP2, LOW);   
    delayMicroseconds(200);
  }
}
void Hefeextrahieren2(void)
{
  for(int i = 0; i<STEPS_PER_REV*5; i++) 
  {
  digitalWrite(STEP2, HIGH);
  delayMicroseconds(200);
  digitalWrite(STEP2, LOW);
  delayMicroseconds(200);
  }
}

void Hefeextrahieren3(void)
{
  for(int i = 0; i<STEPS_PER_REV*5; i++) 
  {
  digitalWrite(STEP2, HIGH);
  delayMicroseconds(200);
  digitalWrite(STEP2, LOW);
  delayMicroseconds(200);
  }
}

void Hefeeinschenken(void)
{
  for(int i = 0; i<STEPS_PER_REV*30 && !EmergencySwitchStatus; i++) 
  {   
    digitalWrite(STEP2, HIGH);
    delayMicroseconds(200);
    digitalWrite(STEP2, LOW);
    delayMicroseconds(200);
  }
}

void Fertigstellen(void)
{
  for(int i = 0; i<STEPS_PER_REV*5 && !EmergencySwitchStatus; i++) 
  {   
    digitalWrite(STEP, HIGH);
    digitalWrite(STEP2, HIGH);    
    delayMicroseconds(200);
    digitalWrite(STEP, LOW);
    digitalWrite(STEP2, LOW);
    delayMicroseconds(200);
  }  
}