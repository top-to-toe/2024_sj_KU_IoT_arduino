#define OPEN digitalWrite(31,HIGH)
#define CLOSE digitalWrite(31,LOW)

const int pinSW = 2;
const int pinDoor = 31;
String inputString = "";
String tempString = "";
String passwd = "1234";
bool stringComplete = false;

void setup() {
  pinMode(pinSW, INPUT);
  Serial.begin(9600);
  inputString.reserve(10);
}

void loop() {
  int swState = digitalRead(pinSW);
  if(swState == HIGH)
  {
    CLOSE;
    snd_close();
  }
  if (stringComplete) {
    Serial.println(inputString);
    if(inputString.substring(0, 2) == "pw")
    {
      tempString = inputString.substring(2, 6);
      Serial.println(tempString);
      if(tempString == passwd)
      {
        OPEN; // digitalWrite(31, HIGH);
    
        Serial.println("open");
        Serial.println("clode");
      }
      else;
      
    }
    if(inputString.substring(0, 2) == "ch")
    {
      passwd = inputString.substring(2, 6);
      Serial.print("password changed to ");
      Serial.println(passwd);
      
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
