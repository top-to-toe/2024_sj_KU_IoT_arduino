#include "LiquidCrystal_I2C.h"
#include "Servo.h"
#define RBG_R 23 
#define RBG_G 35 
#define RBG_B 36 

#define PIN_GAS_FAN   4
#define PIN_WINDOW    9
#define PIN_FAN       32

extern void MQ135_setup();
extern void MQ135_loop();
extern int mq135_lpg;
extern int mq135_co;
extern int mq135_smoke;
Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);
char sData[64] = { 0x00, };
#define R_MAXNUM 32 // 64
char rData[R_MAXNUM] = { 0x00, };
int rPos = 0;

int loop_count = 0;
int gas_detect_timeout = 0;

int emergency_sound[] = {880,440,880,440,880,440,880,440};

void printLCD(int col, int row , char *str) {
    for(int i=0 ; i < strlen(str) ; i++){
      lcd.setCursor(col+i , row);
      lcd.print(str[i]);
    }
}

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);  //Bluetooth Module

  pinMode(PIN_FAN, OUTPUT);
  pinMode(PIN_GAS_FAN, OUTPUT);

  digitalWrite(PIN_FAN, false);
  digitalWrite(PIN_GAS_FAN, false);  
  pinMode(RBG_R, OUTPUT);
  pinMode(RBG_G, OUTPUT);
  pinMode(RBG_B, OUTPUT);
  myServo.attach(PIN_WINDOW);
  myServo.write(0); // window close
    
  lcd.init();
  lcd.backlight();

  printLCD(0, 0, "MQ135 GAS ");
  printLCD(0, 1, "Calibration"); 
  
  MQ135_setup();

  printLCD(0, 0, "GAS-SAFE        ");
  printLCD(0, 1, "NORMAL          "); 
}


void loop()
{
   loop_count += 1;
   if(loop_count % 10 == 0) 
   {  
      MQ135_loop();
   }
   
     if(0 < gas_detect_timeout){
        gas_detect_timeout -= 1;

        printLCD(0, 0, "GAS-DETECT      ");
        sprintf(sData, "%4d %4d %4d  ", 
        mq135_lpg, mq135_co, mq135_smoke);
        printLCD(0, 1, sData); 

		if(loop_count % 10 == 0) {
			memset(sData, 0x00, 64);
			sprintf(sData, "{%04d,%04d,%04d}", 
			  mq135_lpg, mq135_co, mq135_smoke);
			Serial.println(sData);
			Serial1.println(sData);
		}

        digitalWrite(PIN_FAN, true);
        digitalWrite(PIN_GAS_FAN, true);
        tone(11, emergency_sound[gas_detect_timeout % 8], 500);
        digitalWrite(RBG_R, gas_detect_timeout % 2); 
     }
     else {
        printLCD(0, 0, "GAS-SAFE        ");
        sprintf(sData, "%4d %4d %4d  ", 
          mq135_lpg, mq135_co, mq135_smoke);
        printLCD(0, 1, sData); 
      
	  
		if(loop_count % 10 == 0) {
			memset(sData, 0x00, 64);
			sprintf(sData, "{%04d,%04d,%04d}", 
			  mq135_lpg, mq135_co, mq135_smoke);
			Serial.println(sData);
			Serial1.println(sData);
		}
		    digitalWrite(PIN_FAN, false);
        digitalWrite(PIN_GAS_FAN, false);      
        digitalWrite(RBG_R, LOW); 
     }

      if(50 < mq135_smoke){
        printLCD(0, 0, "GAS-DETECT      ");
        printLCD(0, 1, "EMERGENCY!      ");         
        gas_detect_timeout = 40;
        digitalWrite(RBG_R, HIGH);
        myServo.write(40); delay(100);

		if(loop_count % 10 == 0) {
			Serial.println("GAS-DETECT");
			Serial1.println("GAS-DETECT");        
		}}
   myServo.write(0);
   
   if(0 < Serial.available()) {
      String str = Serial.readString();
      Serial.println(str);
    }

   while(0 < Serial1.available()) {
      char ch = Serial1.read();
      rData[rPos] = ch;
      rPos += 1;
      // Serial.print(ch); // 문자열을 출력 
    
      if(ch == '\n')  {
        Serial.println(rData); // 문자열을 출력 
      } }
      delay(100);
  }
