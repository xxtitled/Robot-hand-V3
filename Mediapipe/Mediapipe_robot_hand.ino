#include <Servo.h>

Servo servo_1;
Servo servo_2;
Servo servo_3;
Servo servo_4;
Servo servo_5;

void setup() {
  Serial.begin(9600);

  // 각 핀과 서보를 연결
  servo_1.attach(13); // 엄지
  servo_2.attach(12); // 중지
  servo_3.attach(11); // 검지
  servo_4.attach(10); // 약지
  servo_5.attach(9); // 소지
  delay(500);

  // 초기 위치로 모든 서보를 이동
  servo_1.write(0);
  servo_2.write(0);
  servo_3.write(0);
  servo_4.write(0);
  servo_5.write(0);
  delay(5000);
}

void loop() {
  // 시리얼 버퍼에 읽을 데이터가 있으면 if문 실행 / 즉,  읽을 바이트가 하나라도 들어와 있으면 그 내부를 실행하고, 없으면 건너뛰라는 것
  while (Serial.available() > 0) {
    char data = Serial.read();

    // 홀수 '구부린 상태', 짝수 '펴진 상태'
    // ‘1’ 입력 시 엄지(1번) 서보를 170도로 회전
    if (data == '1') {
      servo_1.write(170);
    }
    // ‘2’ 입력 시 엄지(1번) 서보를 0도로 회전
    if (data == '2') {
      servo_1.write(0);
    }
    // ‘3’ 입력 시 검지(2번) 서보를 170도로 회전
    if (data == '3') {
      servo_2.write(170);
    }
    // ‘4’ 입력 시 검지(2번) 서보를 0도로 회전
    if (data == '4') {
      servo_2.write(0);
    }
    // ‘5’ 입력 시 중지(3번) 서보를 170도로 회전
    if (data == '5') {
      servo_3.write(170);
    }
    // ‘6’ 입력 시 중지(3번) 서보를 0도로 회전
    if (data == '6') {
      servo_3.write(0);
    }
    // ‘7’ 입력 시 약지(4번) 서보를 170도로 회전
    if (data == '7') {
      servo_4.write(170);
    }
    // ‘8’ 입력 시 약지(4번) 서보를 0도로 회전
    if (data == '8') {
      servo_4.write(0);
    }
    // ‘9’ 입력 시 소지(5번) 서보를 170도로 회전
    if (data == '9') {
      servo_5.write(170);
    }
    // ‘0’ 입력 시 소지(5번) 서보를 0도로 회전
    if (data == '0') {
      servo_5.write(0);
    }
    delay(10);  // 작은 딜레이로 서보 과부하 방지
  }
}
