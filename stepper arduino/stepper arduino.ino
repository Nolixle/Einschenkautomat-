#define DIR_HEFE  6
#define STEP_HEFE  7
#define STEPS_PER_REV_HEFE  2000 

#define DIR_GLAS  4    // Stepper 2 
#define STEP_GLAS  5
#define STEPS_PER_REV_GLAS  2000

// #define DEBUG

void BeerPouringRoutine(void);
void StartSwitchISR(void);
void EmergencyStopISR(void);
void Ranfuehren(void);  
void Einschenken(void);
void Hefeextrahieren(void);
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
  pinMode(STEP_GLAS, OUTPUT);
  pinMode(DIR_GLAS, OUTPUT);
  pinMode(STEP_HEFE, OUTPUT);   
  pinMode(DIR_HEFE, OUTPUT);

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
  digitalWrite(STEP_GLAS, LOW);
  digitalWrite(STEP_HEFE, LOW);
  EmergencySwitchStatus = true;
  Serial.println("EMStop ON");
}

void StartSwitchISR(void)
{
  //only if System is not Busy start new iteration of Beer
  digitalWrite(STEP_HEFE, HIGH);
  digitalWrite(STEP_GLAS, HIGH);
  StartSwitchStatus = true;
  Serial.println("Start ON");
}

void BeerPouringRoutine(void)
{  
  Serial.println("Ranfuehren\n");
  // digitalWrite(DIR_HEFE, HIGH);
  // digitalWrite(DIR_GLAS, HIGH);
  // Ranfuehren(); 

  Serial.println("Einschenken\n");
  // digitalWrite(DIR_HEFE, LOW);
  // digitalWrite(DIR_GLAS, HIGH); 
  // Einschenken();

  Serial.println("Hefeextrahieren\n");
  // digitalWrite(DIR_HEFE, LOW);
  // digitalWrite(DIR_GLAS, LOW); 
  // Hefeextrahieren();

  Serial.println("Hefeeinschenken\n");
  // digitalWrite(DIR_HEFE, LOW);
  // digitalWrite(DIR_GLAS, HIGH); 
  // Hefeeinschenken();

  Serial.println("Fertigstellen\n");
  // digitalWrite(DIR_HEFE, LOW);
  // digitalWrite(DIR_GLAS, LOW); 
  // Fertigstellen();
}

// void Ranfuehren(void)
// {
//   for(int i = 0; i<STEPS_PER_REV && !EmergencySwitchStatus; i++) 
//   { 
//     digitalWrite(STEP_HEFE, HIGH);
//     digitalWrite(STEP_GLAS, HIGH);  
//     delayMicroseconds(1000);
//     digitalWrite(STEP_HEFE, LOW);
//     digitalWrite(STEP_GLAS, LOW);
//     delayMicroseconds(1000);
//   } 
// }
void turnMotorGlas(bool GlasUp, float RevsGlas)
{
  if(GlasUp)
  {
    digitalWrite(DIR_GLAS, HIGH);
  }
  else
  {
    digitalWrite(DIR_GLAS, LOW);
  } 

  for(int i = 0; i<(STEPS_PER_REV_GLAS * RevsGlas) && !EmergencySwitchStatus; i++) 
  {
    digitalWrite(STEP_GLAS, HIGH);
    delayMicroseconds(1500);
    digitalWrite(STEP_GLAS, LOW); 
    delayMicroseconds(1500);
  }
}

void turnMotorHefe(bool HefeUp, float RrevsHefe)
{
  if(HefeUp)
  {
    digitalWrite(DIR_HEFE, HIGH);
  }
  else
  {
    digitalWrite(DIR_HEFE, LOW);
  } 

  for(int i = 0; i<(STEPS_PER_REV_HEFE * RrevsHefe) && !EmergencySwitchStatus; i++) 
  {
    digitalWrite(STEP_HEFE, HIGH);
    delayMicroseconds(1500);
    digitalWrite(STEP_HEFE, LOW); 
    delayMicroseconds(1500);
  }
}

void turnMotorHefeGlas(bool HefeUp, bool GlasUp, float Revs)
{
  if(HefeUp)
  {
    digitalWrite(DIR_HEFE, HIGH);
  }
  else
  {
    digitalWrite(DIR_HEFE, LOW);
  } 

  if(GlasUp)
  {
    digitalWrite(DIR_GLAS, HIGH);
  }
  else
  {
    digitalWrite(DIR_GLAS, LOW);
  }

  for(int i = 0; i<(STEPS_PER_REV_GLAS * Revs) && !EmergencySwitchStatus; i++) 
  {
    digitalWrite(STEP_HEFE, HIGH);
    delayMicroseconds(1500);
    digitalWrite(STEP_HEFE, LOW); 
    delayMicroseconds(1500);
    digitalWrite(STEP_GLAS, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP_GLAS, LOW);
    delayMicroseconds(1000);
  }
}

// void Einschenken(void)
// {
//   for(int i = 0; i<STEPS_PER_REV && !EmergencySwitchStatus; i++) 
//   {
//     digitalWrite(STEP_HEFE, HIGH);
//     delayMicroseconds(1500);
//     digitalWrite(STEP_HEFE, LOW); 
//     delayMicroseconds(1500);
//     digitalWrite(STEP_GLAS, HIGH);
//     delayMicroseconds(1000);
//     digitalWrite(STEP_GLAS, LOW);  
//     delayMicroseconds(1000);
//   }
// }

// void Hefeextrahieren(void)
// {
//   for(int i = 0; i<STEPS_PER_REV && !EmergencySwitchStatus; i++) 
//   {
//     digitalWrite(STEP_GLAS, HIGH);
//     delayMicroseconds(1000);
//     digitalWrite(STEP_GLAS, LOW);   
//     delayMicroseconds(1000);
//   }
// }

// void Hefeeinschenken(void)
// {
//   for(int i = 0; i<STEPS_PER_REV && !EmergencySwitchStatus; i++) 
//   {   
//     digitalWrite(STEP_GLAS, HIGH);
//     delayMicroseconds(1000);
//     digitalWrite(STEP_GLAS, LOW);
//     delayMicroseconds(1000);
//   }
// }

// void Fertigstellen(void)
// {
//   for(int i = 0; i<STEPS_PER_REV && !EmergencySwitchStatus; i++) 
//   {   
//     digitalWrite(STEP_HEFE, HIGH);
//     digitalWrite(STEP_GLAS, HIGH);    
//     delayMicroseconds(1000);
//     digitalWrite(STEP_HEFE, LOW);
//     digitalWrite(STEP_GLAS, LOW);
//     delayMicroseconds(1000);
//   }  
// }