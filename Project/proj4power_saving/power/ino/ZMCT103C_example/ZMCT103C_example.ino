/*
 *    ESP8266             ZMCT103C
 *    ----------------------------
 *        Vin ------------ Vcc
 *        GND ------------ GND
 *         A0 ------------ OUT
 *    ----------------------------
*/
int sensorPin = A0;            // ZMCT103C Out
float calibrationFactor = 0.050; // calibrationFactor (depend on sensor & circuit)

void setup() {
  Serial.begin(115200);
}

void loop() {
  float nVPP = getVPP();        // mesure Vp-p
  float current = nVPP * calibrationFactor; // calcurate current

  Serial.print("Vp-p: ");
  Serial.print(nVPP, 3);
  Serial.println("(V)");

  Serial.print("Current: ");
  Serial.print(current, 5);
  Serial.println("(A)");

  Serial.print("Power : ");
  float watt = current * 220;
  Serial.print(watt, 3);
  Serial.println("(W)");

  delay(1000); // mesure every second
}

/************************************ 
function for mesure Vp-p
*************************************/
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
