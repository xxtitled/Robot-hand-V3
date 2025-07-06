#define THRESHOLD 450
#define EMG_PIN A0

void setup() {
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(EMG_PIN);
  Serial.println(value);
  
  delay(50);
}