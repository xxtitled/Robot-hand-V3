#include <Servo.h>

#define THRESHOLD    400
#define EMG_PIN      A0
#define NUM_SERVOS   5

// 서보를 꽂은 디지털 PWM 핀 배열 (예: 9,10,11,12,13)
const uint8_t servoPins[NUM_SERVOS] = {9, 10, 11, 12, 13};

Servo servos[NUM_SERVOS];

void setup() {
  Serial.begin(9600);

  // 각 서보 초기화 및 0°로 세팅
  for (uint8_t i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(0);
  }
}

void loop() {
  int value = analogRead(EMG_PIN);
  uint8_t angle = (value > THRESHOLD) ? 180 : 0;

  // 모든 서보를 같은 각도로 구동
  for (uint8_t i = 0; i < NUM_SERVOS; i++) {
    servos[i].write(angle);
  }

  Serial.println(value);
  delay(100);
}
