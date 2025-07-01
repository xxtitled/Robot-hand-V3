#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("VIN_ESP32");
  Serial.println("Bluetooth ready. Pair & connect!");
}

void loop() {
  // PC 시리얼 → BT
  if (Serial.available()) {
    char c = Serial.read();
    SerialBT.write(c);
  }

  // BT → ESP32
  if (SerialBT.available()) {
    char c = SerialBT.read();  // 한 글자 읽기
    Serial.print("[BT char] ");
    Serial.println(c);
    // 필요하면 문자열 buf에 이어붙이기 가능
  }

  delay(10);
}
