const int pinDoor = 31;
void setup() {
  pinMode(pinDoor, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available())
  {
    char ch = Serial.read();
    if(ch == '1')
      digitalWrite(pinDoor, HIGH);
    else if(ch == '0')
      digitalWrite(pinDoor, LOW);
    else;
  }
}
