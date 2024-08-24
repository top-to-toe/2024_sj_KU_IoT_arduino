int VR = A4; 
int VR_Value = 0;       

void setup() {
  Serial.begin(9600);
}

void loop() {
 VR_Value = analogRead(VR);
 
  Serial.print("VR_Value = ");
  Serial.println(VR_Value);
  delay(1000);
 
}
