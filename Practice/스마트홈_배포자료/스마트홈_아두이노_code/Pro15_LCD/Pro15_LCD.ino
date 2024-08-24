#include "LiquidCrystal_I2C.h" 
LiquidCrystal_I2C lcd(0x27,16,2); 

void setup() {
  lcd.clear();   
  lcd.init(); 
  lcd.backlight();  
  lcd.setCursor(0,0);  
  lcd.print("Hello, World!"); 
  lcd.setCursor(0,1); 
  lcd.print("UnoBigBoard");
}

void loop() {
  lcd.init(); 
  lcd.setCursor(0,1); 
  lcd.print("TEST");
  delay(2000);
  
  lcd.setCursor(0,0);  
  lcd.print("Hello, World!"); 
  lcd.setCursor(0,1); 
  lcd.print("UnoBigBoard");
}
