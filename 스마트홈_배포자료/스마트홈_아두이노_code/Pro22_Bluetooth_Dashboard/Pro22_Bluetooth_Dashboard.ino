#include "Servo.h"
#include "DHT.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"

//control event
#define PIN_FAN       32
#define PIN_GAS_FAN   4
#define PIN_WINDOW    9
#define PIN_DOOR_LOCK 31

// receive event
#define PIN_PIR_DETOR   3
#define PIN_DOOR_BUTTON   2

#define RBG_R 23 
#define RBG_G 35 
#define RBG_B 36 

#define DHTTYPE DHT11
#define DHTPIN 12

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;


extern void MQ135_setup();
extern void MQ135_loop();
extern int mq135_lpg;
extern int mq135_co;
extern int mq135_smoke;

char sData[64] = { 0x00, };
#define R_MAXNUM 32 // 64
char rData[R_MAXNUM] = { 0x00, };
int rPos = 0;
int cdcValue = 0;
float temperature, humidity; 
int loop_count = 0;
int bell_pos = -1;
int melody[] = {262,294,330,349,392,440,494,523};

void printLCD(int col, int row , char *str) {
    for(int i=0 ; i < strlen(str) ; i++){
      lcd.setCursor(col+i , row);
      lcd.print(str[i]);
    }
}


void setup(){
	Serial.begin(9600);
  Serial1.begin(9600);  //Bluetooth Module
  
   lcd.init();
  lcd.backlight();
  printLCD(0, 0, "Smart Home ");
  printLCD(0, 1, "Are You Ready? "); 
  delay(5000);
  
  lcd.clear();
  printLCD(0, 0, "MQ135 GAS ");
  printLCD(0, 1, "Calibration"); 
  
  MQ135_setup();
  dht.begin();
  
  myServo.attach(PIN_WINDOW);
  pinMode(PIN_FAN, OUTPUT);
  pinMode(PIN_GAS_FAN, OUTPUT);
  pinMode(PIN_DOOR_LOCK, OUTPUT);
  pinMode(RBG_R,OUTPUT);
  pinMode(RBG_G,OUTPUT);
  pinMode(RBG_B,OUTPUT);

  myServo.write(0); // window close
  digitalWrite(PIN_FAN, false);
  digitalWrite(PIN_GAS_FAN, false);
  digitalWrite(PIN_DOOR_LOCK, false);

  digitalWrite(RBG_R, false);
  digitalWrite(RBG_G, false);
  digitalWrite(RBG_B, false);
}

void loop() {

   bool pir_state = digitalRead(PIN_PIR_DETOR);
   bool button_state = digitalRead(PIN_DOOR_BUTTON);
   Serial.print("button_state="); Serial.println(button_state);
   Serial.print("pir_state="); Serial.println(pir_state);

   if(button_state) { 
		digitalWrite(RBG_G, HIGH);
		bell_pos = 0;
   }
   else {
		digitalWrite(RBG_G, LOW);     
   }

   if(pir_state) { 
		digitalWrite(RBG_R, HIGH);
   }
   else {
		digitalWrite(RBG_R, LOW);
   }

    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
  
    lcd.clear();
    memset(sData, 0x00, 64);
    sprintf(sData,"Tem.%02dC Hum.%02d%%", (int)temperature,(int)humidity);
    printLCD(0, 0, sData);
    memset(sData, 0x00, 64);
    sprintf(sData, "CO%04d  CDC%02d",mq135_co,cdcValue);
    printLCD(0, 1, sData);

   loop_count += 1;
   if(loop_count % 5 == 0) 
   {
	   
    cdcValue = analogRead(A0); // Analog adc Value 
    // Serial.print(cdcValue); Serial.print(",");
    MQ135_loop();
	
	memset(sData, 0x00, 64);
   sprintf(sData,"{%02d.%02d,%02d,%1d,%04d,%04d,%04d,%04d,%1d}", 
   (int)temperature, ((int)(temperature*100))%100,
	 (int)humidity,  pir_state, mq135_lpg, mq135_co, mq135_smoke,
	 cdcValue,button_state);
	 Serial.println(sData);
	 Serial1.println(sData);
	  
   }
   delay(100);
   
// Bluetooth Received Data 
	while(0 < Serial1.available()) {
	  	char ch = Serial1.read();
  		rData[rPos] = ch;
  		rPos += 1;
  		// Serial.print(ch); // 문자열을 출력 
		
		if(ch == '\n'){					
  			/*
  			Serial.print("rPos=");
  			Serial.print(rPos);
  			Serial.print(" ");
  			Serial.println(rData);
  			*/
	String str(rData);
	  if(str.equals("W_ON\n") == true) myServo.write(10); // window close
	  if(str.equals("W_OFF\n") == true) myServo.write(90); // window open
	  // if(str.equals("S180") == true) myServo.write(180);

    if(str.equals("F_ON\n") == true) digitalWrite(PIN_FAN, true);
		if(str.equals("F_OFF\n") == true) digitalWrite(PIN_FAN, false);

		if(str.equals("GF_ON\n") == true) digitalWrite(PIN_GAS_FAN, true);
		if(str.equals("GF_OFF\n") == true) digitalWrite(PIN_GAS_FAN, false);
		      
		if(str.equals("D_ON\n") == true) digitalWrite(PIN_DOOR_LOCK, false);
		if(str.equals("D_OFF\n") == true) digitalWrite(PIN_DOOR_LOCK, true);			
			
  	rPos = 0;
  	memset(rData, 0x00, R_MAXNUM);
  	break;		
		}
			delay(10);
	}

   if(loop_count % 2 == 0) 
   {
   		if(0 <= bell_pos) { // bell sound
			tone(11, melody[bell_pos],500);
			bell_pos += 1;
			if(7 < bell_pos) bell_pos = -1;
   		}

   }
	
 }

 
