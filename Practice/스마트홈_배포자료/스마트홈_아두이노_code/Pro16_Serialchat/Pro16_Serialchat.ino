const int pin_red = 23;
const int pin_frn = 35;
const int pin_blu = 36;

void setup() {
  lcd.begin();
  lcd.print("## VR to LCD ##");
  lcd.setPosition(0, 1);
  lcd.print("adc = ")
  lcd.setPosition(0, 1);
  lcd.print("adc = ");
  delay(2000);
}

void loop(){
  lcd.setPosition(3, 1);
}
