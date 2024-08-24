void setup() {
Serial.begin(9600);
Serial.println("ADC Start~");

}

void loop() {
  int adc = 0;
  double volt = 0.0;
  adc = analogRead(4);
  volt = 5 * adc /1023.0;
  Serial.println(volt);

}
