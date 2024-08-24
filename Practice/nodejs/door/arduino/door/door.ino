#define OPEN digitalWrite(31,HIGH)
#define CLOSE digitalWrite(31,LOW)
#include "DHT.h"
#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

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

void loop() {
  int swState = digitalRead(pinSW);
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  
  if(swState == HIGH){
    CLOSE;
    //snd_close();
    Serial.println("doorclose");
  }
  //Serial.print("humi");
  //Serial.println(h);
  //Serial.print("temp");
  //Serial.println(t);
  
  if (stringComplete) {
    Serial.println(inputString);
    if(inputString.substring(0, 2) == "pw")
    {
      tempString = inputString.substring(2, 6);
      Serial.println(tempString);
      if(tempString == passwd)
      {
        OPEN; // digitalWrite(31, HIGH);
    
        Serial.println("dooropen");
        //snd_open();
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

void snd_open(){
  tone(pinBuzz, 262); delay(250); noTone(pinBuzz);
  tone(pinBuzz, 330); delay(250); noTone(pinBuzz);
  tone(pinBuzz, 392); delay(250); noTone(pinBuzz);
}

void snd_close(){
  tone(pinBuzz, 392); delay(250); noTone(pinBuzz);
  tone(pinBuzz, 330); delay(250); noTone(pinBuzz);
  tone(pinBuzz, 262); delay(250); noTone(pinBuzz);
}
