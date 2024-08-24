const int pinVR = A4;

void setup()
{
  Serial.begin(9600);
}
/*
1024:5 = adc:volt
1024*volt = 5 * adc
volt = 5 * adc / 1024
 */
 unsigned int adc = 0;
 double volt = 0.0;
void loop()
{
  adc = analogRead(pinVR);
  volt = 5 * (double)adc / 1023;
  Serial.print("adc = ");
  Serial.print(adc);
  Serial.print("    V = ");
  Serial.print(volt);
  Serial.println("(V)");
}
