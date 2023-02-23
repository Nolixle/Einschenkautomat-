const int DIR = 2;
const int STEP = 3;
const int steps_per_rev = 2000;

                            //geht nicht da DIR2 glieichen Pin wie DIR zugewiesen wurde 
                           //selbe für STEP2
                          //Vorschlag 
                         //const int DIR_stepper2 = 4;
                        //const int STEP_stepper2 = 5; 
const int DIR2 = 4;    // Stepper 2 
const int STEP2 = 5;
const int steps_per_rev2 = 2000;

void setup()
{
  Serial.begin(115200);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);

    pinMode(STEP2, OUTPUT);   // Neu Stepper 2 
    pinMode(DIR2, OUTPUT);
 
}

void loop()
{
  Serial.println("Spinning Clockwise...");
  digitalWrite(DIR, HIGH);
  
  digitalWrite(DIR2, HIGH); // Neu Stepper 2 



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

  {
    digitalWrite(STEP2 HIGH);   // Neu Stepper 2 
    delayMicroseconds(2000);
    digitalWrite(STEP2, LOW);
    delayMicroseconds(2000);
  }
}
