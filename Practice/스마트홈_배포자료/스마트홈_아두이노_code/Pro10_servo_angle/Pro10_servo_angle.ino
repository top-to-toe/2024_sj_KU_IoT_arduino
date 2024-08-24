#include "Servo.h"
Servo myServo;
 
void setup(){
  myServo.attach(9);
}
void loop(){
   myServo.write(10);
   delay(2000);
  
   myServo.write(45);
   delay(2000);

   myServo.write(90);
   delay(2000);
  
   myServo.write(160);
   delay(2000);
 }

 
