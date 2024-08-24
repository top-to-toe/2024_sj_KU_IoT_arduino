int analogInPin = A0;  
int sensorADC = 0;        

void setup() {
 Serial.begin(9600);
}

void loop() {
  sensorADC = analogRead(analogInPin);
  Serial.print("CDS ADC Value = ");
  Serial.println(sensorADC);
 
  delay(100);
}
