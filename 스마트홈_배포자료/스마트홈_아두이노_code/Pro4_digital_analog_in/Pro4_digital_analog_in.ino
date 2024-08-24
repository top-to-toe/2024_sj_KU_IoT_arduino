void setup() {
pinMode(23 , OUTPUT);  
pinMode(A4, INPUT); 
Serial.begin(9600);
}

void loop() {
  boolean VR_state = digitalRead(A4);
  int VR_adc = analogRead(4);
  float VR_voltage = (float)(VR_adc * 5) / 1023;

  Serial.print("VR_State = ");
  Serial.println(VR_state);

  Serial.print("VR_adc = ");
  Serial.println(VR_adc);

  Serial.print("VR_voltage = ");
  Serial.print(VR_voltage);
  Serial.println('V');
  Serial.println("\t");
  delay(1000);

  if(VR_state  == HIGH)   
      digitalWrite(23 , HIGH);   
  else      
      digitalWrite(23 , LOW);     
   }

   
