#include <Stepper.h>
int SPU = 2048; 
Stepper Motor(SPU, 3,5,4,6);

void setup() 
{
Motor.setSpeed(5);
}

void loop() {
Motor.step(2048);
delay(1000); 
Motor.step(-2048); 
delay(1000);
}


