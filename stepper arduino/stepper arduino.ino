const int DIR = 2;
const int STEP = 3;
const int steps_per_rev = 2000; //TODO nutze besser define die kannst du dann quer durch 

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
  //TODO baue/oder teste Code bevor du pusht, immer nur funktioniernden COde pushen
void loop()
{
  Serial.println("Spinning Clockwise...");
  digitalWrite(DIR, HIGH);
  digitalWrite(DIR2, HIGH); // Neu Stepp
  
   
    for(int i = 0; i<steps_per_rev; i++)

    digitalWrite(STEP, HIGH);   // da wird ein Schritt gemacht 
    delayMicroseconds(2000);
    digitalWrite(STEP, LOW);
    delayMicroseconds(2000);
 
    for(int i = 0; i<steps_per_rev; i++)
  
    digitalWrite(STEP2, HIGH);
    delayMicroseconds(2000);
    digitalWrite(STEP2, LOW);
    delayMicroseconds(2000);

  
}

