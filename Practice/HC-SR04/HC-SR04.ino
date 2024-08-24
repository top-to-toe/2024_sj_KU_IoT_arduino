const int pinTrig = 4;
const int pinEcho = 5;

void setup() {
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  Serial.begin(9600);
  Serial.println("mesure distance with HC-SR04");
}

void loop() {

  trig(); /* transmit trigger pulese */  // 트리거 펄스를 발생시키는 함수 호출
  unsigned long echo_time = get_echoTime();  // Echo 시간을 받아옴

  if (echo_time != 0) {
    /*
      거리 계산 공식:
      소리의 속도는 340m/s (또는 340,000mm/s), 이를 이용하여 Echo 시간을 거리로 변환
      거리(mm) = 17 * Echo 시간(us) / 100
    */
    unsigned int distance = 17 * echo_time / 100;  // Echo 시간을 거리로 변환
    Serial.print("distance = ");
    Serial.println(distance);  // 거리를 시리얼 모니터에 출력
  } else {
    Serial.println("out of range!");  // Echo 시간이 유효하지 않을 때 "out of range!" 출력
  }
  delay(1000);
}

void trig(void) {
  digitalWrite(pinTrig, HIGH);  // Trigger 핀을 HIGH로 설정하여 펄스 발생
  delayMicroseconds(10);         // 10us 대기
  digitalWrite(pinTrig, LOW);   // Trigger 핀을 LOW로 설정
}

unsigned long get_echoTime(void) {

  unsigned long echoTime = 0;  // Echo 시간 변수 초기화

  while (digitalRead(pinEcho) == LOW );  // Echo 핀이 LOW인 동안 대기

  unsigned long startTime = micros();  // Echo 핀이 HIGH가 되었을 때의 시간을 기록

  while (digitalRead(pinEcho) == HIGH);  // Echo 핀이 HIGH인 동안 대기
  echoTime = micros() - startTime;  // Echo 시간 계산

  /*
    유효한 Echo 시간 범위: 240us에서 23000us 사이
    이 범위를 벗어나면 0을 반환하여 유효하지 않은 값을 나타냄
  */
  if (echoTime >= 240 && echoTime <= 23000)
    return echoTime;  // 유효한 Echo 시간 반환
  else
    return 0;  // 유효하지 않은 Echo 시간이므로 0 반환
}
