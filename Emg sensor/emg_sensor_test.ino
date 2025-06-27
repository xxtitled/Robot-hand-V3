#include <Servo.h>
Servo myservo;

const int emgPin    = A0;
const int servoPin  = 9;
int minEMG = 8;    // 평소 값
int maxEMG = 16;    // 힘 줄 때 최고 관찰값

void setup() {
  myservo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  int emg = analogRead(emgPin);
  // 관찰된 범위에 맞춰 맵핑
  int pos = map(emg, minEMG, maxEMG, 0, 180);
  pos = constrain(pos, 0, 180);

  myservo.write(pos);
  Serial.print("A");
  Serial.print(emg);
  Serial.print("B");
  Serial.println(pos);

  delay(100);
}

