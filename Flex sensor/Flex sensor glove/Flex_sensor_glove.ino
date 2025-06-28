#include <Servo.h>     

Servo servo_thumb;      
Servo servo_index;
Servo servo_middle;
Servo servo_ring;
Servo servo_pinky;

const int flexpin_thumb = A0;
const int flexpin_index = A1;
const int flexpin_middle = A2;
const int flexpin_ring = A3;
const int flexpin_pinky = A4;

void setup() 
{
 
  Serial.begin(9600);
 
  servo_thumb.attach(13);  
  servo_index.attach(12);
  servo_middle.attach(11);
  servo_ring.attach(10);
  servo_pinky.attach(9);

} 
 
void loop()
{
  
  int flexposition_thumb;    
  int flexposition_index;
  int flexposition_middle;
  int flexposition_ring;
  int flexposition_pinky;
  
  int servoposition_thumb;   
  int servoposition_index;
  int servoposition_middle;
  int servoposition_ring;
  int servoposition_pinky;
  
  flexposition_thumb = analogRead(flexpin_thumb);
  flexposition_index = analogRead(flexpin_index);
  flexposition_middle = analogRead(flexpin_middle);
  flexposition_ring = analogRead(flexpin_ring);
  flexposition_pinky = analogRead(flexpin_pinky);
  
  servoposition_thumb = map(flexposition_thumb, 745, 945, 0, 180);
  servoposition_thumb = constrain(servoposition_thumb, 0, 180);
  
  servoposition_index = map(flexposition_index, 745, 945, 0, 180);
  servoposition_index = constrain(servoposition_index, 0, 180);
  
  servoposition_middle = map(flexposition_middle, 745, 945, 0, 180);
  servoposition_middle = constrain(servoposition_middle, 0, 180);
  
  servoposition_ring = map(flexposition_ring, 745, 945, 0, 180);
  servoposition_ring = constrain(servoposition_ring, 0, 180);
  
  servoposition_pinky = map(flexposition_pinky, 745, 945, 0, 180);
  servoposition_pinky = constrain(servoposition_pinky, 0, 180);
  
  servo_thumb.write(servoposition_thumb);
  delay(20);
  servo_index.write(servoposition_index);
  delay(20);
  servo_middle.write(servoposition_middle);
  delay(20);
  servo_ring.write(servoposition_ring);
  delay(20);
  servo_pinky.write(servoposition_pinky);
  delay(20);  
  
  Serial.print("sensor_thumb: ");
  Serial.print(flexposition_thumb);
  Serial.print("servo_thumb: ");
  Serial.println(servoposition_thumb);
  
  Serial.print("sensor_idex: ");
  Serial.print(flexposition_index);
  Serial.print("servo_index: ");
  Serial.println(servoposition_index);

  Serial.print("sensor_middle: ");
  Serial.print(flexposition_middle);
  Serial.print("servo_middle: ");
  Serial.println(servoposition_middle);

  Serial.print("sensor_ring: ");
  Serial.print(flexposition_ring);
  Serial.print("servo_ring: ");
  Serial.println(servoposition_ring);

  Serial.print("sensor_pinky: ");
  Serial.print(flexposition_pinky);
  Serial.print("servo_pinky: ");
  Serial.println(servoposition_pinky);
  
}