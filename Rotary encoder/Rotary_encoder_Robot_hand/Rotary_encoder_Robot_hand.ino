#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>  // PCA9685 드라이버 라이브러리 포함 

// PCA9685 16채널 PWM 서보 드라이버 객체 생성 (I2C 주소 0x40)
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

const uint8_t N = 5;  // 제어할 서보+인코더 채널 수

// 각 채널별 로터리 인코더 핀 배열 정의 // 16채널 PWM 서보 드라이버 핀 SDA -> A4 , SCL --> A5
const uint8_t clkPins[N] = {2, 3, 4, 5, 6};   // A 위상(클럭) 입력 핀
const uint8_t dtPins [N] = {7, 8, 9, 10, 11}; // B 위상(디리전) 입력 핀
const uint8_t swPins [N] = {12, 13, A0, A1, A2}; // 엔코더 버튼 입력 핀

// 서보 펄스폭 범위 정의 (0° -> SERVOMIN, 180° -> SERVOMAX)
#define SERVOMIN 150  // 약 500µs 펄스: 0° 대응
#define SERVOMAX 600  // 약 2500µs 펄스: 180° 대응

const int STEP = 25;  // 로터리 인코더 한 클릭당 서보가 움직일 각도(°)

int angles[N];             // 각 채널의 현재 서보 각도 저장
int lastCLK[N];            // 각 채널 이전 루프에서 읽은 CLK 상태 저장
unsigned long lastBtn[N];  // 버튼 디바운스용 마지막 눌림 시간 저장

void setup() {
  // I2C 통신 초기화 및 PCA9685 설정
  Wire.begin();            // I2C 버스 시작
  pwm.begin();             // PCA9685 초기화
  pwm.setPWMFreq(50);      // 서보 제어용 주파수 50Hz 설정

  // 시리얼 통신 시작 (디버그 출력용)
  Serial.begin(115200);
  Serial.println("Fixed STEP 모드: 클릭당 25°씩 동작합니다.");

  // 각 채널별 초기 설정
  for (uint8_t i = 0; i < N; i++) {
    pinMode(clkPins[i], INPUT_PULLUP);  // A 위상: 풀업 입력
    pinMode(dtPins [i], INPUT_PULLUP);  // B 위상: 풀업 입력
    pinMode(swPins [i], INPUT_PULLUP);  // 버튼: 풀업 입력

    angles[i]  = 0;                      // 초기 각도 0°
    lastCLK[i] = digitalRead(clkPins[i]); // 초기 CLK 상태 읽기
    lastBtn[i] = 0;                       // 버튼 디바운스 타이머 초기화

    // 초기 서보 위치(0°) 출력
    uint16_t pulse = map(angles[i], 0, 180, SERVOMIN, SERVOMAX);
    pwm.setPWM(i, 0, pulse);
  }
}

void loop() {
  // 각 채널별로 입력 상태 확인
  for (uint8_t i = 0; i < N; i++) {
    // 1) A 위상(클럭) 상태 읽기
    int cur = digitalRead(clkPins[i]);

    // 2) 풀업 상태 HIGH -> LOW -> HIGH 로 변화(LOW->HIGH 엣지) 감지
    if (cur != lastCLK[i] && cur == HIGH) {
      // B 위상과 비교하여 회전 방향 결정
      if (digitalRead(dtPins[i]) == HIGH) {
        angles[i] += STEP;  // 시계 방향 회전 시 각도 증가
      } else {
        angles[i] -= STEP;  // 반시계 방향 회전 시 각도 감소
      }

      // 각도 범위(0°~180°)로 제한
      angles[i] = constrain(angles[i], 0, 180);

      // 서보 PWM 펄스 폭 계산 후 출력
      uint16_t pulse = map(angles[i], 0, 180, SERVOMIN, SERVOMAX);
      pwm.setPWM(i, 0, pulse);

      // 디버그: 시리얼 모니터에 각도 출력
      Serial.print("Servo ");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(angles[i]);
    }
    // 3) 현재 CLK 상태를 저장해서 다음 루프에 비교
    lastCLK[i] = cur;

    // 4) 버튼 누름 시 서보 각도를 0°로 리셋 (디바운스 처리)
    if (digitalRead(swPins[i]) == LOW && millis() - lastBtn[i] > 50) {
      angles[i] = 0;  // 각도 0°로 초기화
      uint16_t pulse = map(0, 0, 180, SERVOMIN, SERVOMAX);
      pwm.setPWM(i, 0, pulse);

      // 디버그: 리셋 메시지 출력
      Serial.print("Servo ");
      Serial.print(i);
      Serial.println(" reset to 0°");

      lastBtn[i] = millis();  // 디바운스 타이머 갱신
    }
  }

  // 짧은 딜레이로 폴링 안정화
  delay(1);
}
