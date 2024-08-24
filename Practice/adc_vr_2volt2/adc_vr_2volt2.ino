void setup() {
Serial.begin(9600);
Serial.println("ADC Start~");

}

void loop() {
  int adc = 0;
  long int mV = 0;
  adc = analogRead(4);
  mV = 5000 * adc /1023;
  long quot = mV / 1000;
  long remain = mV % 1000;
  Serial.print(quot);
  Serial.print(".");
  Serial.print(remain);
  Serial.println("(V)");

}
