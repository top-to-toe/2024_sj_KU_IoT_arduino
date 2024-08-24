#define OPEN digitalWrite(31,HIGH)
#define CLOSE digitalWrite(31,LOW)

const int pinBuzz = 11;
const int pinSW = 2;
const int pinDoor = 31;
String inputString = "";
String tempString = "";
String passwd = "1234";
bool stringComplete = false;

int note[] = {262,294,330,349,392,440,494,523};

void setup() {
  pinMode(pinSW, INPUT);
  Serial.begin(9600);
  inputString.reserve(10);
}

void snd_open(void){
  tone(pinBuzz, 262);  delay(250);  noTone(pinBuzz);
  tone(pinBuzz, 330);  delay(250);  noTone(pinBuzz);
  tone(pinBuzz, 392);  delay(250);  noTone(pinBuzz);
}

void snd_close(void){
  tone(pinBuzz, 392);  delay(250);  noTone(pinBuzz);
  tone(pinBuzz, 330);  delay(250);  noTone(pinBuzz);
  tone(pinBuzz, 262);  delay(250);  noTone(pinBuzz);
}

void loop() {
  int swState = digitalRead(pinSW);
  if(swState == HIGH){
    CLOSE;
    snd_close();
        Serial.println("doorclose");
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
        snd_open();
        Serial.println("dooropen");
    
        Serial.println("open");
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
