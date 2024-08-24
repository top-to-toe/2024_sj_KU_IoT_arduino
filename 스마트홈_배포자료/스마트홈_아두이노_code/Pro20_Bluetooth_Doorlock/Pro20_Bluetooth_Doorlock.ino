#include "LiquidCrystal_I2C.h"
#define PIN_DOOR_LOCK 31

// receive event
#define PIN_PIR_DETOR   3
#define PIN_DOOR_BUTTON   2
#define RBG_R 23 
#define RBG_G 35 
#define RBG_B 36 
#define PIN_DOOR_LOCK 31

LiquidCrystal_I2C lcd(0x27, 16, 2);

void printLCD(int col, int row , char *str) {
    for(int i=0 ; i < strlen(str) ; i++){
      lcd.setCursor(col+i , row);
      lcd.print(str[i]);
    }
}

int loop_count = 0;
int bell_pos = -1;
int melody_pos = -1;
int doorbell_timeout = -1;
int doorlock_timeout = -1;
int detect_timeout = -1;

#define R_MAXNUM 32 // 64
char rData[R_MAXNUM] = { 0x00, };
int rPos = 0;

int bell[] = {660,660,660,550,550,550,440,440};
int melody[] = {262,294,330,349,392,440,494,523};

void doorOpen(){
     // sound melody
     melody_pos = 0;
       
     // doorlock open
    digitalWrite(PIN_DOOR_LOCK, true);
    doorlock_timeout = 40;

  printLCD(0, 0, "DOOR-LOCK       ");
  printLCD(0, 1, "OPEN            "); 

  Serial.println("OPEN");
  Serial1.println("OPEN");
}

void doorClose(){
    printLCD(0, 0, "DOOR-LOCK       ");
    printLCD(0, 1, "CLOSE           "); 

    digitalWrite(PIN_DOOR_LOCK, false);
    Serial.println("CLOSE");
    Serial1.println("CLOSE"); 
}

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);  //Bluetooth Module

  lcd.init();
  lcd.backlight();

  printLCD(0, 0, "DOOR-LOCK");
  printLCD(0, 1, "CLOSE"); 

  pinMode(PIN_DOOR_BUTTON,INPUT);
  pinMode(PIN_DOOR_LOCK, OUTPUT);
  pinMode(RBG_R, OUTPUT);
  pinMode(RBG_G, OUTPUT);
  pinMode(RBG_B, OUTPUT);
    
  digitalWrite(PIN_DOOR_LOCK, false);
}

void loop()
{
  digitalWrite(RBG_R, LOW);
  digitalWrite(RBG_G, LOW);
  digitalWrite(RBG_B, LOW);
   
   bool pir_state = digitalRead(PIN_PIR_DETOR);
   bool door_state = digitalRead(PIN_DOOR_BUTTON);
   Serial.print("door_state="); Serial.print(door_state);
   Serial.print(", pir_state="); Serial.println(pir_state);

   if(doorbell_timeout == -1)
   {
     if(door_state) { 
      digitalWrite(RBG_G, HIGH);
      bell_pos = 0;
  
      printLCD(0, 0, "INPUT PASSWORD  ");
      printLCD(0, 1, "****            "); 
  
      Serial.println("DOORBELL");
      Serial1.println("DOORBELL");

      doorbell_timeout = 20;
     }
     else {
      digitalWrite(RBG_G, LOW);     
     }   
   }
   else {
    doorbell_timeout -= 1;
   }

   if(detect_timeout == -1)
   {
     if(pir_state) { 
      Serial.println("DETECT");
      Serial1.println("DETECT");
      digitalWrite(RBG_R,HIGH);
      detect_timeout = 40;
      
     }
     else {
     }
   }
   else {
      detect_timeout -= 1;
      if( detect_timeout % 2 == 0)
      {
        digitalWrite(RBG_R, HIGH);
      }
      else {
        digitalWrite(RBG_R, LOW);
      }
   }
   
   if(loop_count % 10 == 0) 
   {
	  Serial.println("");
      Serial1.println("");
   }

   if(loop_count % 2 == 0) 
   {
      if(0 <= bell_pos) { // bell sound
        tone(11, bell[bell_pos],500);
        bell_pos += 1;
        if(7 < bell_pos) bell_pos = -1;
        digitalWrite(RBG_B, HIGH);
      }

      if(0 <= melody_pos) { // melody sound
        tone(11, melody[melody_pos],500);
        melody_pos += 1;
        if(7 < melody_pos) melody_pos = -1;
        digitalWrite(RBG_G, HIGH);
      }

      if(0 <= doorlock_timeout)
      {
        doorlock_timeout -= 1;
        if(doorlock_timeout == 0)
        {
          doorClose();
        }
      }
   }

   if(0 < Serial.available())
   {
      String str = Serial.readString();
      Serial.println(str);

      // 패스워드가 맞음
      if(str.equals("1004") == true) {
        doorOpen();
        
      }
   }

   while(0 < Serial1.available()) {
      char ch = Serial1.read();
      rData[rPos] = ch;
      rPos += 1;
      // Serial.print(ch); // 문자열을 출력 
    
      if(ch == '\n')
      {
        Serial.println(rData); // 문자열을 출력 

        // 패스워드가 맞음
        if(memcmp(rData, "1004", 4) == 0) {
          doorOpen();
        }        

        rPos = 0;
        memset(rData, 0x00, R_MAXNUM);        
      }
   }
   
   delay(100);
   
   loop_count += 1;

   
}
