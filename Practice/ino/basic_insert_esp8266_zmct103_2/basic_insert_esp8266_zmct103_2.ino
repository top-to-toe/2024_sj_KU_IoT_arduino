/*
 *    ESP8266             ZMCT103C
 *    ----------------------------
 *        Vin ------------ Vcc
 *        GND ------------ GND
 *         A0 ------------ OUT
 *    ----------------------------
/*
  MySQL Connector/Arduino Example : connect by wifi

  This example demonstrates how to connect to a MySQL server from an
  Arduino using an Arduino-compatible Wifi shield. Note that "compatible"
  means it must conform to the Ethernet class library or be a derivative
  with the same classes and methods.
  
  For more information and documentation, visit the wiki:
  https://github.com/ChuckBell/MySQL_Connector_Arduino/wiki.

  INSTRUCTIONS FOR USE

  1) Change the address of the server to the IP address of the MySQL server
  2) Change the user and password to a valid MySQL user and password
  3) Change the SSID and pass to match your WiFi network
  4) Connect a USB cable to your Arduino
  5) Select the correct board and port
  6) Compile and upload the sketch to your Arduino
  7) Once uploaded, open Serial Monitor (use 115200 speed) and observe

  If you do not see messages indicating you have a connection, refer to the
  manual for troubleshooting tips. The most common issues are the server is
  not accessible from the network or the user name and password is incorrect.

  Created by: Dr. Charles A. Bell
*/
#include <ESP8266WiFi.h>           // Use this for WiFi instead of Ethernet.h
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
IPAddress server_addr( 172,16,0,7);  // IP of the MySQL *server* here
char user[] = "user1";              // MySQL user login username
char password[] = "1234";        // MySQL user login password



// Sample query
char INSERT_SQL[] = "INSERT INTO power.dev01(Ampere, Watt) VALUES (%f, %f)";
char query[128];

// WiFi card example
//*
char ssid[] = "iptimeA604R_2.4G";         // your SSID
char pass[] = "raspberry";     // your SSID Password
//*/

WiFiClient client;                 // Use this for WiFi instead of EthernetClient
MySQL_Connection conn(&client);
MySQL_Cursor* cursor;

int sensorPin = A0;            // ZMCT103C Out
float calibrationFactor = 0.050; // calibrationFactor (depend on sensor & circuit)
void setup(){
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect. Needed for Leonardo only

  // Begin WiFi section
  Serial.printf("\nConnecting to %s", ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // print out info about the connection:
  Serial.println("\nConnected to network");
  Serial.print("My IP address is: ");
  Serial.println(WiFi.localIP());

  Serial.print("Connecting to SQL...  ");
  if (conn.connect(server_addr, 3306, user, password))
    Serial.println("OK.");
  else
    Serial.println("FAILED.");
  
  // create MySQL cursor object
  cursor = new MySQL_Cursor(&conn);
}

void loop()
{
  float nVPP = getVPP();        // mesure Vp-p
  
  float Ampere = nVPP * calibrationFactor; // calcurate current
  float Watt = Ampere * 220;
  Serial.print("Vp-p: ");
  Serial.print(nVPP, 3);
  Serial.println("(V)");

  Serial.print("Current: ");
  Serial.print(Ampere, 5);
  Serial.println("(A)");

  Serial.print("Power : ");
  Serial.print(Watt, 3);
  Serial.println("(W)");

  delay(1000);
  sprintf(query, INSERT_SQL, Ampere, Watt);
    
  if (conn.connected())
    cursor->execute(query);

  delay(3600000); // every 1hour
}

float getVPP() {
  float result;
  int readValue;                // read from sensor
  int maxValue = 0;             // variable for maximum value
  int minValue = 1024;          // variable for minimum Value
  uint32_t start_time = millis();

  while((millis() - start_time) < 1000) {  // Sampling for 1(sec)
    readValue = analogRead(sensorPin);
    // update  maxValue
    if (readValue > maxValue) {
      maxValue = readValue;
    }
    // update  minValue
    if (readValue < minValue) {
      minValue = readValue;
    }
  }

  // calcurate Vp-p
  result = ((maxValue - minValue) * 5.0) / 1024.0;
  
  return result;
}
