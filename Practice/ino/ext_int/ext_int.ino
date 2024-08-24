const int pinSW     =  2;
volatile int state  =  0;


void setup()
{
    pinMode(13, OUTPUT);
    pinMode(pinSW, INPUT);
    attachInterrupt(digitalPinToInterrupt(pinSW), intfunc, RISING);
}


void loop()
{
}


void intfunc() // Interrupt function
{
  state ^= 1;
  digitalWrite(13, state);
}
