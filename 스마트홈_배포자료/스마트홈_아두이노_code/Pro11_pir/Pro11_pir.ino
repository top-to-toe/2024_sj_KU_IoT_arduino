int pirState = LOW;   // 센서 초기상태는 움직임이 없음을 가정
int val = 0;          // 센서 신호의 판별을 위한 변수
 
void setup(){
    pinMode(23, OUTPUT);    
    pinMode(35, OUTPUT);    
    pinMode(3, INPUT);   
    Serial.begin(9600);   
}
 
void loop(){
  val = digitalRead(3);  
    
  if (val == HIGH) {                   
    digitalWrite(23, HIGH);     
    digitalWrite(35, LOW);   
    if (pirState == LOW){                         
         Serial.println("Welcome!");   
         pirState = HIGH; }
   } 
   else {                             
    digitalWrite(23, LOW);       
    digitalWrite(35, HIGH);      
    if (pirState == HIGH){                
        Serial.println("Good Bye~");   
        pirState = LOW;}
   }
    Serial.println("~~~"); delay(100); 
  } 

  
