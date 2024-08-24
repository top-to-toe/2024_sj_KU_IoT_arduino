/* SmartFarm MMB BD Pro9 Temp & Humi Data Reading
   www.blueinno.co.kr 
   2020. 11. 10 
 */
#include "DHT.h"
DHT dht(12, DHT11);
int temp, humi;
unsigned long time1 =0;
 
void setup() {
  dht.begin();
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  humi = dht.readHumidity();
  temp = dht.readTemperature();
  unsigned long time2 = millis();
  delay(100);
  if ( (time2-time1)>999) {
  Serial1.print(temp);
  Serial1.print(",");
  Serial1.print(humi);
  //Serial1.print("\n");
  
  Serial.print(temp);
  Serial.print(",");
  Serial.println(humi);
  
  time1=time2;
  }
 }

 
