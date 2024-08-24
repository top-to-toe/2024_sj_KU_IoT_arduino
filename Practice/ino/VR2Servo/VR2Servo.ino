#include <Servo.h>
Servo servo;
const int pinVR = A4;
const int pinServo = 9;
int pos = 90;
void setup()
{
  servo.attach(pinServo);
  servo.write(pos);
}

int adc = 0;

void loop()

{
  adc = analogRead(pinVR);
  /*
    1023:180 = adc:angle
    1023 * angle = 180 * adc
    angle = 180 * adc / 1023
   */

pos = map(adc, 0, 1023, 0, 180);
    servo.write(pos);
    delay(15);
}
