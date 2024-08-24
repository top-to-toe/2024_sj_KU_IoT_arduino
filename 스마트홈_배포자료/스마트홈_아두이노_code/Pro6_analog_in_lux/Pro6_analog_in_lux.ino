void setup() {
   Serial.begin(9600);
}

void loop() {
  int Photo_adc = analogRead(A0); 
  float Photo_voltage = float(Photo_adc*5)/1023;
  float Rp = (10*Photo_voltage)/(5-Photo_voltage);
  float y = (log10(200/Rp))/0.7; 
  float Ea = pow(10,y);  
  
  Serial.print("Photo_adc = ");
  Serial.println(Photo_adc);

  Serial.print("Photo_voltage = ");
  Serial.println(Photo_voltage);

  Serial.print("Ea_value = ");
  Serial.print(Ea);
  Serial.println("Lux");
  Serial.println("\t");
  delay(1000);
}
