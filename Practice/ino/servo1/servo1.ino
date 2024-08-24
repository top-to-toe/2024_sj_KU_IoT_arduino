#include <Servo.h>

Servo servo;

void setup() {
  servo.attach(9);  // attaches the servo on pin 9 to the servo object
  servo.write(0);
  delay(1000);
  servo.write(90);
  delay(1000);
  servo.write(180);
  delay(1000);
}

void loop() {
}
