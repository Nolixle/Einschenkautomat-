const int DIR = 2;
const int STEP = 3;
const int  steps_per_rev = 2000;

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