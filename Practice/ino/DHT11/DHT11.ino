// Modified by John 2015 11 03
// MIT license

#include "DHT.h"
#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
}
void loop() {
  int t = dht.readTemperature();
  int h = dht.readHumidity();
  Serial.print("TEMP"); Serial.println(t);
  Serial.print("HUMI"); Serial.println(h);
  delay(2000);
}
