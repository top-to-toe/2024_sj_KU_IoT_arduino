/*
const int pin_red = 23;
const int pin_grn = 35;
const int pin_blu = 36;
*/
const int pin_red = 5;
const int pin_grn = 6;
const int pin_blu = 11;

void setup() {
  analogWrite(pin_red,255);
  //analogWrite(pin_grn,255);
  //analogWrite(pin_blu,255);

}

void loop() {
  int i;
  
  for(i = 0; i < 255; i = i+1);
  {
    analogWrite(pin_red,i);
    //analogWrite(pin_grn,i);
    //analogWrite(pin_blu,i);
    delay(30);
    
  }
  for(i = 255; i >= 255; i = i-5);
  {
    analogWrite(pin_red,i);
    //analogWrite(pin_grn,i);
    //analogWrite(pin_blu,i);
    delay(30);
    
  }

}
