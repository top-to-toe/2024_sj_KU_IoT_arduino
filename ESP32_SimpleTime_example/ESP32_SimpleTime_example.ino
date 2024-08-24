#include <WiFi.h>
#include "time.h"

const char* ssid       = "KT_GiGA_5G_43E1";
const char* password   = "6gb28gd078";

const char* ntpServer = "pool.ntp.org";
uint8_t timeZone = 9;
uint8_t summerTime = 0; // 3600

void printLocalTime() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void setup() {
  Serial.begin(115200);
  Serial.printf("Connecting to %s ", ssid);  //connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  configTime(3600 * timeZone, 3600 * summerTime, ntpServer); //init and get the time
  printLocalTime();
  WiFi.disconnect(true);  //disconnect WiFi as it's no longer needed
  WiFi.mode(WIFI_OFF);
}

void loop() {
  delay(1000);
  printLocalTime();
}
