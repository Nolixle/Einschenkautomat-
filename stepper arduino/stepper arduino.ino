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
  //TODO sieht aus wie zusammengespaxt 
    pinMode(DIR2, OUTPUT);    //TODO konstanter Abstand sieht bessser und professsioner aus
 
}
  //TODO baue/oder teste Code bevor du pisht, immer nur funktioniernden COde pushen
void loop()
{
  Serial.println("Spinning Clockwise...");
  digitalWrite(DIR, HIGH);
  digitalWrite(DIR2, HIGH); // Neu Stepper 2 



  do{ //TODO nicht funcktional, da Durchführung nicht definiert ist
    for(int i = 0; i<steps_per_rev; i++)

      //TODO Klammern fehlen
      //for(...)
      //{
      //   Code   
      //}
  
    digitalWrite(STEP, HIGH);
    delayMicroseconds(2000);
    digitalWrite(STEP, LOW);
    delayMicroseconds(2000);
  }while(Durchführugn)

  do{//TODO schiebe Code von in eine For schleife 
  //-> einzelne SChritte sollen gleichzeitig und nicht nacheinander ausgeführt werden 
    for(int i = 0; i<steps_per_rev; i++)
  
    digitalWrite(STEP2, HIGH);
    delayMicroseconds(2000);
    digitalWrite(STEP2, LOW);
    delayMicroseconds(2000);
  }while(Durchführung)

 
    //TODO lösche unnötige KOmmentare, nie "toten Code"  pushen                               
                                                               // weis nicht ob ich die nachfolgenden noch Brauch 
                                                              // delay(1000); 
  
                                                             //digitalWrite(DIR, LOW);
                                                             //Serial.println("Spinning Anti-Clockwise...");
}
