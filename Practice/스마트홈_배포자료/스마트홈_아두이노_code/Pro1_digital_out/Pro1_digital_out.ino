void setup() {
  pinMode(23, OUTPUT);
}

void loop() {
  int delay_time = 1000; 
  digitalWrite(23, HIGH); 
  delay(delay_time);   
  digitalWrite(23, LOW);   
  delay(delay_time);                       
}
