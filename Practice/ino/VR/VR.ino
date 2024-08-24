const int pinVR = A4;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.print("adc value = ");
  Serial.println(analogRead(pinVR));
  delay(500);
}
