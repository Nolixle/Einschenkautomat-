#define DIR  2
#define STEP  3
#define steps_per_rev  2000 

#define DIR2  4    // Stepper 2 
#define STEP2  5
#define steps_per_rev2  2000

 void Funkton1();
 void Funktin2()
{
                                 
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
void setup()

{
  Serial.begin(115200);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(STEP2, OUTPUT);   
  pinMode(DIR2, OUTPUT);    
}
 






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
void Funktion1()
{

}

