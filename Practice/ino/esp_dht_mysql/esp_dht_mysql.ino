#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include "DHT.h"

#define DHTPIN 5
#define typeDHT DHT11

DHT dht(DHTPIN, typeDHT);

char ssid[] = "KT_GiGA_2G_43E1";
char pass[] = "6gb28gd078";
byte mac[6];

//WiFiServer server(80);
/*
IPAddress ip(172, 30, 1, 6);
IPAddress gateway(172, 30, 1, 254);
IPAddress subnet(255, 255, 255, 0);
*/
WiFiClient client;
MySQL_Connection conn((Client *)&client);

//char INSERT_SQL[] = "INSERT INTO officeto_plants.TBL_READINGS(ID_PLANT, AIR_HUMIDITY, AIR_TEMPERATURE, SOIL_MOISTURE_1) VALUES (1, NULL, NULL, %d)";
char INSERT_SQL[] = "INSERT INTO dht11.dev01(Temperature, Humidity) VALUES (%d, %d)";
char query[128];

IPAddress server_addr(172, 30, 1, 104);   // MySQL server IP
char user[]     = "user1";                   // MySQL user
char password[] = "1234";                   // MySQL password

void setup()
{
  Serial.begin(115200);
  pinMode(DHTPIN, INPUT);
/*
  Serial.println("Initialising connection");
  Serial.print(F("Setting static ip to : "));
  Serial.println(ip);
*/
  Serial.println("");
  Serial.println("");
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  //WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("--------------------------");
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
  Serial.println("");
  Serial.print("Assigned IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("--------------------------");
  Serial.println("");

  Serial.println("Connecting to database");
  Ethernet.begin(mac);
  while (conn.connect(server_addr, 3306, user, password) != true) {
    delay(200);
    Serial.print ( "." );
  }
  Serial.println("");
  Serial.println("Connected to SQL Server!");  
}

void loop()
{
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  int Temperature = int(t) % 100;
  int Humidity    = int(h) % 100;

  if( Temperature != 47 && Humidity != 47 )
  {
    Serial.print(Temperature);  Serial.print("%\t");
    Serial.print(Humidity);     Serial.print("*C\n");
  
    sprintf(query, INSERT_SQL, Temperature, Humidity);
  
    Serial.println("Recording data.");
    Serial.println(query);
    Serial.println();
    
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn); 
    cur_mem->execute(query);
    delete cur_mem;
  }
  else
  {
    Serial.println("error~\n");
  }
  delay(10000); //10 sec
}
