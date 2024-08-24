#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#define DHT11_PIN 12

void setup() {
  Serial.begin(115200);
}

void loop() {
  DHT.read(DHT11_PIN);
  Serial.print("temp");
  Serial.println(DHT.temperature);
  Serial.print("humi");
  Serial.println(DHT.humidity);
  delay(1000);
}
