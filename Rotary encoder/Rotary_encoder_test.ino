/*
  회전 방향, 회전 횟수(카운터), 버튼 누름 --> 시리얼 모니터에 출력
*/

// 로터리 엔코더 핀 정의
#define CLK 2   // CLK 출력(A 위상) -> 디지털 핀 2
#define DT 3    // DT 출력(B 위상) -> 디지털 핀 3
#define SW 4    // 엔코더 버튼 스위치 -> 디지털 핀 4

int counter = 0;                    // 회전 카운터 변수
int currentStateCLK;                // 현재 CLK 상태 저장 변수
int lastStateCLK;                   // 이전 루프에서의 CLK 상태 저장 변수
String currentDir = "";           // 회전 방향 문자열("CW" 또는 "CCW")
unsigned long lastButtonPress = 0;  // 버튼 디바운스용 마지막 눌림 시간(ms)

void setup() {
  // 핀 모드 설정
  pinMode(CLK, INPUT);              // CLK 입력 설정
  pinMode(DT, INPUT);               // DT 입력 설정
  pinMode(SW, INPUT_PULLUP);        // SW 풀업 입력 설정 (버튼 눌림 시 LOW)

  Serial.begin(9600);               // 시리얼 통신 시작 (9600 bps)

  lastStateCLK = digitalRead(CLK);  // 초기 CLK 상태 읽어 저장
}

void loop() {
  // 현재 CLK 상태 읽기
  currentStateCLK = digitalRead(CLK);

  // CLK 상태 변경(LOW→HIGH) 감지 시 회전 처리
  if (currentStateCLK != lastStateCLK && currentStateCLK == HIGH) {
    // DT 상태와 비교하여 회전 방향 결정
    if (digitalRead(DT) != currentStateCLK) {
      counter--;                   // CCW(반시계) 회전: 카운터 감소
      currentDir = "CCW";
    } else {
      counter++;                   // CW(시계) 회전: 카운터 증가
      currentDir = "CW";
    }

    // 회전 방향과 카운터 값 시리얼 출력
    Serial.print("방향: ");
    Serial.print(currentDir);
    Serial.print(" | 카운터: ");
    Serial.println(counter);
  }

  // 이전 CLK 상태 업데이트
  lastStateCLK = currentStateCLK;

  // 버튼 상태 읽기 (LOW 시 눌림)
  int btnState = digitalRead(SW);

  // 버튼 눌림 감지 및 디바운스 처리
  if (btnState == LOW) {
    // 마지막 눌림 이후 50ms 지났으면 새로운 눌림으로 간주
    if (millis() - lastButtonPress > 50) {
      Serial.println("버튼 눌림!");
    }
    lastButtonPress = millis();     // 마지막 눌림 시간 갱신
  }

  delay(1);  // 짧은 지연으로 입력 안정화
}
