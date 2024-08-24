void setup() {
pinMode(31, OUTPUT); 
pinMode(23, OUTPUT);    
pinMode(35, OUTPUT); 
pinMode(2, INPUT); 
}

void loop() {
 bool buttonState = digitalRead(2);
    
  if(buttonState  == HIGH) {  
      digitalWrite(31 , HIGH);
      digitalWrite(23 , LOW);
      digitalWrite(35 , HIGH);    
   }
   
   else {     
       digitalWrite(31 , LOW);
       digitalWrite(23 , HIGH); 
       digitalWrite(35 , LOW);     
    }
}
