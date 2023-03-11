#define DIR  2
#define STEP  3
#define steps_per_rev  2000 //STEPS_PER_REV //TODO define are always written with CAPITAL_LETTERS -> this is due to better readability
//when you built the code the compiler will replace all the names with the number it was defined
//when you write it as a normal variable you will be confused, which one is normal variable and the value can be changed or not 

#define DIR2  4    // Stepper 2 
#define STEP2  5
#define steps_per_rev2  2000

 void Funkton1(); //Functions never used 
 void Funktin2() //; //TODO Semicolon missing and typo Function is the correct spelling 
{
                                 
  for(int i = 0; i<steps_per_rev; i++)  //STEPS_PER_REV
  //{ //TODO brakets missing, you will get a compilier warning 
    digitalWrite(STEP, HIGH);   // da wird ein Schritt gemacht 
    delayMicroseconds(2000);
    digitalWrite(STEP, LOW);
    delayMicroseconds(2000);
  //} //TODO braket missing 
    for(int i = 0; i<steps_per_rev; i++) //STEPS_PER_REV
  //{ TODO breaket missing
    digitalWrite(STEP2, HIGH);
    delayMicroseconds(2000);
    digitalWrite(STEP2, LOW);
    delayMicroseconds(2000);
  //}
}

void setup()
//no empty line allowed //TODO delete empty line 
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