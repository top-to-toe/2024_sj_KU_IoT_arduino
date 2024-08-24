String inputString = "";

void setup() {
  // initialize serial:
  Serial.begin(9600);
  inputString.reserve(20);
}

void loop() {
  if(Serial.available()>0) {
    char ch = Serial.read();
    if(ch != '\n') {
      inputString += ch;
    }
    else {
      Serial.println(inputString);
      inputString = "";
    }
  }
}
