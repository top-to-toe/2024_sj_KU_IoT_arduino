void setup() {
Serial.begin(9600);
Serial.println("ADC Start~");

}

void loop() {
  int adc = 0;
  adc = analogRead(A4);
  Serial.println(adc);

}
