#include <Servo.h>

// 핀 정의
#define CLK         5    // 엔코더 CLK(A 위상)
#define DT          3    // 엔코더 DT(B 위상)
#define SW          4    // 엔코더 버튼 스위치
#define SERVO_PIN   9    // 서보 제어 핀
#define STEP_SIZE   5    // 한 스텝당 움직일 각도

int angle = 90;                    // 서보 각도 변수 (0~180), 초기값 90°
int currentStateCLK;               // 현재 CLK 상태
int lastStateCLK;                  // 이전 루프에서 읽은 CLK 상태
unsigned long lastButtonPress = 0; // 버튼 디바운스용 마지막 누름 시간
Servo myServo;                     // 서보 객체

void setup() {
  // 입력 핀 설정
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);

  // 시리얼 통신 시작
  Serial.begin(9600);

  // 초기 CLK 상태 읽기
  lastStateCLK = digitalRead(CLK);

  // 서보 초기화
  myServo.attach(SERVO_PIN);
  myServo.write(angle);
}

void loop() {
  // 1) CLK 상태 읽기
  currentStateCLK = digitalRead(CLK);

  // 2) LOW→HIGH 전환 시 회전 발생
  if (currentStateCLK != lastStateCLK && currentStateCLK == HIGH) {
    // DT 상태와 비교하여 방향 판별 및 각도 조정
    if (digitalRead(DT) == HIGH) {
      angle += STEP_SIZE;        // CW 회전: 각도 증가
    } else {
      angle -= STEP_SIZE;        // CCW 회전: 각도 감소
    }

    // 각도 범위 제한 (0~180)
    angle = constrain(angle, 0, 180);

    // 서보에 각도 적용
    myServo.write(angle);

    // 디버그: 시리얼에 각도 출력
    Serial.print("각도: ");
    Serial.println(angle);
  }

  // 3) 이전 CLK 상태 저장
  lastStateCLK = currentStateCLK;

  // 4) 버튼 눌림 감지 및 디바운스 처리
  if (digitalRead(SW) == LOW) {
    if (millis() - lastButtonPress > 50) {
      // 버튼 누르면 각도 90°로 리셋
      angle = 90;
      myServo.write(angle);
      Serial.println("버튼 눌림: 각도 90°로 리셋");
    }
    lastButtonPress = millis();
  }

  delay(1);  // 짧은 지연으로 안정적인 읽기
}
