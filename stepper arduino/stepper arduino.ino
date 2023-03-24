#define DIR  2
#define STEP  3
#define STEPS_PER_REV  2000 

#define DIR2  4    // Stepper 2 
#define STEP2  5
#define STEPS_PER_REV2  2000

void BeerPouringRoutine(void);
void StartSwitchISR(void);
void EmergencyStopISR(void);
void ErrorState(void);
void EmergencyStopPressed(void);
void funktion1(void);  
void funktion2(void);
void funktion3(void);
void funktion4(void);
void funktion5(void);

const int EmergencySwitch = 6; //real interrupt pin 
bool EmergencySwitchStatus = true;
const int StartSwitch = 7; //real interrupt pin 
bool StartSwitchStatus = false;

int rev = 5;

void funktion1()
{
  for(int i = 0; i<STEPS_PER_REV; i++) 
  { 
    digitalWrite(STEP, HIGH);
    digitalWrite(STEP2, HIGH);   // da wird ein Schritt gemacht 
    delayMicroseconds(1000);
    digitalWrite(STEP, LOW);
    digitalWrite(STEP2, LOW);
    delayMicroseconds(1000);

  } 
}
void funktion2()
{
  for(int i = 0; i<STEPS_PER_REV; i++) 
     {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP, LOW); 
    delayMicroseconds(1000);
    digitalWrite(STEP2, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP2, LOW);  
    delayMicroseconds(1000);
     }
}
void funktion3()
{
  for(int i = 0; i<STEPS_PER_REV; i++) 
     {
    digitalWrite(STEP2, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP2, LOW);   // da wird ein Schritt gemacht 
    delayMicroseconds(1000);
     }
}
void funktion4()
{
   for(int i = 0; i<STEPS_PER_REV; i++) 
  {   
    digitalWrite(STEP2, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP2, LOW);
    delayMicroseconds(1000);
  }
}
void funktion5()
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

void setup()
{
  Serial.begin(115200);
  Serial.println("Startet Biereinschenkautomat");
  
  pinMode(EmergencySwitch, INPUT);
  pinMode(EmergencySwitch, HIGH);
  pinMode(StartSwitch, INPUT);
  pinMode(StartSwitch, LOW);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(STEP2, OUTPUT);   
  pinMode(DIR2, OUTPUT);

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

  Serial.println("Initializing done");
  Serial.println("-------------------------------------------");
}


void loop()
{ 
  //run BeerPouringroutine when start button is pressed and Emergency Switch is not pressed 
  if(false != EmergencySwitch && true == StartSwitch)
  {
    BeerPouringRoutine();
  }
  else if(false == StartSwitch) //Status messages 
  {
    Serial.println("Start Switch not pressed");
  }
   else if(true == EmergencySwitch)
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
}

void StartSwitchISR(void)
{
  //only if System is not Busy start new iteration of Beer
  digitalWrite(STEP, LOW);
  digitalWrite(STEP2, LOW);
  StartSwitchStatus = true;
}

void BeerPouringRoutine(void)
{  
  Serial.println("Spinning Clockwise...");
  digitalWrite(DIR, HIGH);
  digitalWrite(DIR2, HIGH); // Neu Stepp
  funktion1(); 

  Serial.print("Spinning Clockwise...");
  digitalWrite(DIR, LOW);
  digitalWrite(DIR2, HIGH); 
  funktion2();

  Serial.print("Spinning Clockwise...");
  digitalWrite(DIR, LOW);
  digitalWrite(DIR2, LOW); 
  funktion3();

  Serial.print("Spinning Clockwise...");
  digitalWrite(DIR, LOW);
  digitalWrite(DIR2, HIGH); 
  funktion4();

  Serial.print("Spinning Clockwise...");
  digitalWrite(DIR, LOW);
  digitalWrite(DIR2, LOW); 
  funktion5();
}
