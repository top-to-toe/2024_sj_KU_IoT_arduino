#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
const int pinVR = A4;
void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("ADC result!");
}

int adc = 0;

void loop()

{
  adc = analogRead(pinVR);
  //lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("    ");
  lcd.setCursor(0,1);
  lcd.print(adc);
  delay(100);
}
