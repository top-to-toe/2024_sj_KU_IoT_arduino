#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

String inputString = "";         // a String to hold incoming data
String str2lcd = "";
bool stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(20);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,1);
}

void write_lcd(void)
{
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(str2lcd);
}


void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    if(inputString.substring(0, 3) == "lcd")
    {
      str2lcd = inputString.substring(3);
      write_lcd();
      
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = Serial.read();
    // add it to the inputString:
    if(inChar != '\n'){
      inputString += inChar;
    }
    else {
      stringComplete = true;
    }
  }
}
