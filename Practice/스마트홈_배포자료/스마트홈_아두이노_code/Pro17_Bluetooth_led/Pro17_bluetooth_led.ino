void setup(){
  Serial1.begin(9600);
  pinMode(13, OUTPUT);
}
  
void loop() { 
  char cmd;
  
  if(Serial1.available()){
    cmd = (char)Serial1.read();
    if( cmd == '1') {
     digitalWrite(13, HIGH);
    }
    if( cmd == '2') {
     digitalWrite(13, LOW);
    }
 }
}
