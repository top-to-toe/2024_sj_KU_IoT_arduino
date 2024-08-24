const int pinLED = 13;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(pinLED, OUTPUT);
  Serial.begin(9600);
  Serial.println("program start ~");
}

void loop() {
  if(Serial.available() > 0)
  {
    char ch = Serial.read();

    if(ch == '1')
    {
      digitalWrite(pinLED, HIGH);
      Serial.println("LED is On");
    }
    else if(ch == '0')
    {
      digitalWrite(pinLED, LOW);
      Serial.println("LED is Off");
    }
    else;
  }
}
