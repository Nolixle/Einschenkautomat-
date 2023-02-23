#define STEPS_PER_REVOLUTION 2000
#define DELAY_STEPPER 2000;

const int DIR = 2;
const int STEP = 3;

const int steps_per_rev = STEPS_PER_REVOLUTION;

const int DIR2 = 4;    // Stepper 2 
const int STEP2 = 5;
const int steps_per_rev2 = STEPS_PER_REVOLUTION;

int rev = 5;

void setup()
{
  Serial.begin(115200);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);

  pinMode(STEP2, OUTPUT);   // Neu Stepper 2 
  pinMode(DIR2, OUTPUT);
  
  //switch on Stepper driver at System initialisation
  digitalWrite(DIR, HIGH);
  digitalWrite(DIR2, HIGH); // Neu Stepper 2 
}

void loop()
{ 
  Serial.println("Spinning Clockwise...");
  
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
