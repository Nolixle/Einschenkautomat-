#define DIR  2
#define STEP  3
#define STEPS_PER_REV  2000 
//when you built the code the compiler will replace all the names with the number it was defined
//when you write it as a normal variable you will be confused, which one is normal variable and the value can be changed or not 

#define DIR2  4    // Stepper 2 
#define STEP2  5
#define STEPS_PER_REV2  2000

void funktion(void); //Functions never used 


void funktion()
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
for(int i = 0; i<STEPS_PER_REV; i++) 
 {
   digitalWrite(STEP, HIGH);
   delayMicroseconds(1000);
   digitalWrite(STEP, LOW);
    delayMicroseconds(1000);
    }
   
   


}
void funktion2()
{
  for(int i = 0; i<STEPS_PER_REV; i++) 
     {
        digitalWrite(STEP2, LOW);
    delayMicroseconds(1000);
    digitalWrite(STEP2, HIGH);   // da wird ein Schritt gemacht 
    delayMicroseconds(1000);
     }
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
  
  funktion(); 
}

/*correct function decalreation and usage 
void function(void);

void function()
{
  //Sourcecode 
}
*/

/*
//structure of code 
//defines and variables
#define DIR 1 
//function declaration 
void function(void);
void setup()
{
  //source code 
}
void loop()
{
  //source code
}

*/