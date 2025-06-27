#include <Servo.h>

#define THRESHOLD 400
#define EMG_PIN    A0
#define SERVO_PIN  A5

Servo SERVO_1;

void setup() {
  Serial.begin(9600);
  SERVO_1.attach(SERVO_PIN);
}

void loop() {
  int value = analogRead(EMG_PIN);

  if (value > THRESHOLD) {
    SERVO_1.write(170);
  } else {
    SERVO_1.write(10);
  }

  Serial.println(value);
  delay(100);
}