void setup() {
pinMode(13, OUTPUT);  
pinMode(2, INPUT); 
}

void loop() {
 bool buttonState = digitalRead(2);
    
  if(buttonState  == HIGH) {  
      digitalWrite(13 , HIGH);   
   }
   
   else {     
      digitalWrite(13 , LOW);     
    }
}
