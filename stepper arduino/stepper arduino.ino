const int DIR = 2;
const int STEP = 3;
const int steps_per_rev = 2000;

//geht nicht da DIR2 glieichen Pin wie DIR zugewiesen wurde 
//selbe für STEP2
//Vorschlag 
//const int DIR_stepper2 = 4;
//const int STEP_stepper2 = 5; 
const int DIR2 = 2;    // Stepper 2 
const int STEP2 = 3;
const int steps_per_rev2 = 2000;

void setup()
{
  Serial.begin(115200);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
}
void loop()
{
  digitalWrite(DIR, HIGH);
  Serial.println("Spinning Clockwise...");
  
  //turn motor
  for(int i = 0; i<steps_per_rev; i++)
  {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(2000);
    digitalWrite(STEP, LOW);
    delayMicroseconds(2000);
  }
  delay(1000); 
  
  digitalWrite(DIR, LOW);
  Serial.println("Spinning Anti-Clockwise...");

  for(int i = 0; i<steps_per_rev; i++)
  {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(1000);
    digitalWrite(STEP, LOW);
    delayMicroseconds(1000);
  }
  delay(1000);
}