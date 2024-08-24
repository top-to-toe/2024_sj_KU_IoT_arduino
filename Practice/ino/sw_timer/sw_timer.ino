const int periode = 1500;
long prv_millis = 0;
long cur_millis = 0;
void setup() {
  Serial.begin(9600);
}

void loop()
{
  cur_millis = millis();
  if(cur_millis - prv_millis > periode)
  {
    Serial.println("===");
    prv_millis = cur_millis;
  }
}
