int melody[] = {262,294,330,349,392,440,494,523};

void setup() {
}

void loop() {
   for (int i=0; i<=7; i++) {
     tone(11, melody[i],500);
     delay(500);
     //noTone(9);
    }
    delay(2000); 
}


  
