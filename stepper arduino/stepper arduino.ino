#define STEPS_PER_REVOLUTION 2000
#define DELAY_STEPPER 2000;

void BeerPouringRoutine(void);
void StartSwitchISR(void);
void EmergencyStopISR(void);
void ErrorState(void);
void EmergencyStopPressed(void);

//TODO Not aus as interrup, switch off stepper

const int DIR = 4;
const int STEP = 5;

const int DIR2 = 6;    // Stepper 2 
const int STEP2 = 7;


const int EmergencySwitch = 2; //real interrupt pin 
bool EmergencySwitchStatus = TRUE;
const int StartSwitch = 3; //real interrupt pin 
bool StartSwitchStatus = FALSE;

int rev = 5;

void setup()
{
  Serial.begin(115200);
  Serial.println("Startet Biereinschenkautomat");
  
  pinMode(EmergencySwitch, INPUT);
  pinMode(EmergencySwitch, HIGH);
  pinMode(StartSwitch, INPUT);
  pinMode(StartSwitch, LOW);
  //Interrupt  for Emergency switch and StartSwitch 
  attachInterrupt(digitalPintInterrupt(EmergencySwitch), EmergencyStopISR, FALLING);
  attachInterrupt(digitalPintInterrupt(StartSwitchStatus), StartSwitchISR, RISING);
  Serial.println("Interrupt initialized");

  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);

  pinMode(STEP2, OUTPUT);   
  Serial.println("Pins configured");

  if(digitalRead(EmergencySwitch) != HIGH)
  {
    EmergencySwitchStatus = TRUE;
  }
  else{
    EmergencySwitchStatus = FALSE;
  }
  Serial.println("Emergency Stop is pressed %c, [1 pressed, 0 not pressed]", EmergencySwitchStatus);
  Serial.println("Initializing done");
  Serial.println("-------------------------------------------");
}

void loop()
{ 
  //run BeerPouringroutine when start button is pressed and Emergency Switch is not pressed 
  if(FALSE != EmergencySwitch && TRUE == StartSwitch)
  {
    BeerPouringRoutine();
  }
  else if(FALSE == StartSwitch) //Status messages 
  {
    Serial.println("Start Switch not pressed");
  }
   else if(TRUE == EmergencySwitch)
  {
    Serial.println("Emergency Switch pressed");
  }
}

void EmergencyStopISR(void)
{
  //Switch off Stepper
  digitalWrite(STEP, LOW);
  digitalWrite(STEP2, LOW);
  EmergencySwitchStatus = TRUE;
}

void StartSwitchISR(void)
{
  //only if System is not Busy start new iteration of Beer
  digitalWrite(STEP, LOW);
  digitalWrite(STEP2, LOW);
  StartSwitchStatus = TRUE;
}

void BeerPouringRoutine(void)
{
  //define spinning direction of stepper
  digitalWrite(DIR, HIGH);
  digitalWrite(DIR2, HIGH); // Neu Stepper 2 
      
  //define stepper motor revolutions
  rev = 1;

  //turn both motor simustanosly until target revolutions are done
  for(int i = 0; i < rev * STEPS_PER_REVOLUTION; i++)
  {
    digitalWrite(STEP, HIGH);
    digitalWrite(STEP2, HIGH);
    delayMicroseconds(DELAY_STEPPER);
    digitalWrite(STEP, LOW);
    digitalWrite(STEP2, LOW);
    delayMicroseconds(DELAY_STEPPER);
  }
}
