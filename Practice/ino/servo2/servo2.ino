#include <Servo.h>
#define MAX 180
#define MIN   0
#define STEP 10
const int pinServo = 9;
Servo servo;
int pos = 90;

void setup() {
  Serial.begin(9600);
  servo.attach(pinServo);
  servo.write(pos);
  delay(15);
}

void loop() {
  if(Serial.available() > 0)
  {
    char ch = Serial.read();
    if(ch == '=') //'+'
    {
      if(pos + STEP <= MAX)
      {
        pos = pos + STEP;
      }
      else
      {
        pos = MAX;
      }
    }
    else if(ch == '-')
    {
      if(pos - STEP >= MIN)
      {
        pos = pos - STEP;
      }
      else
      {
        pos = MIN;
      }
    }
    else;
    Serial.print("pos = ");
    Serial.println(pos);
    servo.write(pos);
    delay(15);
    }
}
