#include <BluetoothSerial.h> // 블루투스 연결
#include <ESP32Servo.h>

BluetoothSerial SerialBT;

// Servo 객체
Servo tb, ix, md, rg, pk; // 엄지, 검지, 중지, 약지, 소지

// PWM 핀
const int PIN_THUMB  = 18; // 엄지
const int PIN_INDEX  = 19; // 검지
const int PIN_MIDDLE = 21; // 중지
const int PIN_RING   = 22; // 약지
const int PIN_PINKY  = 23; // 소지

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  SerialBT.begin("VIN_ESP32");
  Serial.println("Bluetooth ready as [VIN_ESP32]");

  tb.attach(PIN_THUMB);
  ix.attach(PIN_INDEX);
  md.attach(PIN_MIDDLE);
  rg.attach(PIN_RING);
  pk.attach(PIN_PINKY);

  // 시작 시 모두 펼친 상태
  openAll();
}

void openAll() { // open || 열어 || 보자기: 모두 펼치기
  tb.write(0);
  ix.write(0);
  md.write(0);
  rg.write(0);
  pk.write(0);
  Serial.println(">> OPEN (all 0°)");
}

void closeAll() { // close || 닫아 || 바위: 모두 접기
  tb.write(180);
  ix.write(180);
  md.write(180);
  rg.write(180);
  pk.write(180);
  Serial.println(">> CLOSE (all 180°)");
}

void scissors() { // peace || scissors || 가위: 검지(index)·중지(middle)만 펼치고 나머지 접기
  tb.write(180);
  ix.write(0);
  md.write(0);
  rg.write(180);
  pk.write(180);
  Serial.println(">> SCISSORS (peach)");
}

void promise() { // promise || 약속: 소지(pinky)만 펼치고 나머지 접기
  tb.write(180);
  ix.write(180);
  md.write(180);
  rg.write(180);
  pk.write(0);
  Serial.println(">> PROMISE (pinky)");
}

void loop() {
  if (SerialBT.available()) {
    String cmd = SerialBT.readStringUntil('\n');
    cmd.trim();
    Serial.print("CMD> "); Serial.println(cmd);

    if (cmd.equalsIgnoreCase("open") || cmd.equals("열어") || cmd.equals("보자기")) {
      openAll();
    }
    else if (cmd.equalsIgnoreCase("close") || cmd.equals("닫아") || cmd.equals("바위")) {
      closeAll();
    }
    else if (cmd.equalsIgnoreCase("peace") || cmd.equalsIgnoreCase("scissors") || cmd.equals("가위")) {
      scissors();
    }
    else if (cmd.equalsIgnoreCase("promise") || cmd.equals("약속")) {
      promise();
    }
    else {
      Serial.println("Unknown command");
    }
  }
  delay(20);
}
