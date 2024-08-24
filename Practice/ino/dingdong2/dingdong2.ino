const int pinSW     =  2;
const int pinBuzz   = 11;
volatile bool inten  =  false;
const int ding  = 784;
const int dong  = 659;


void setup()
{
    pinMode(pinSW, INPUT);
    attachInterrupt(digitalPinToInterrupt(pinSW), intfunc, RISING);
}


void loop()
{
  if(inten){
    tone(pinBuzz, ding); delay(300); noTone(pinBuzz);
    tone(pinBuzz, dong); delay(500); noTone(pinBuzz);
    tone(pinBuzz, ding); delay(300); noTone(pinBuzz);
    tone(pinBuzz, dong); delay(500); noTone(pinBuzz);
    inten = false;
    
  }
}


void intfunc() // Interrupt function
{
  inten = true;
}
