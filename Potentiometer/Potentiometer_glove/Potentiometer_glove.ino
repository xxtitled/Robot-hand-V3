#include <Servo.h>

Servo myservo1;         // 엄지
Servo myservo2;         // 검지
Servo myservo3;         // 중지
Servo myservo4;         // 약지
Servo myservo5;         // 소지


int potpin  = 0;         // 엄지 potentiometer 연결 핀: 0
int potpin2 = 1;         // 검지 potentiometer 연결 핀: 1
int potpin3 = 2;         // 중지 potentiometer 연결 핀: 2
int potpin4 = 3;         // 약지 potentiometer 연결 핀: 3
int potpin5 = 4;         // 소지 potentiometer 연결 핀: 4

int val  = 0;            // 
int val2 = 0;
int val3 = 0;
int val4 = 0;
int val5 = 0;



void setup()
{

myservo1.attach(9);    // 엄지
myservo2.attach(10);   // 검지
myservo3.attach(11);   // 중지
myservo4.attach(12);   // 약지
myservo5.attach(13);   // 소지

}

void loop()
{
//potentiometer val needs to be determent because the potentiometer does not make the full turn. 
//Normaly val is between (1, 1023) 
//VB. val = map(val, 27, 533) instead off 


val = analogRead(potpin);           // reads the value of the potentiometer (value between 0 and 1023) 
val = map(val, 1, 500, 0, 176);    // scale it to use it with the servo (value between 0 and 180) 
myservo1.write(val);                // sets the servo position according to the scaled value 
delay(25);                          // waits for the servo to get there 

val2 = analogRead(potpin2);         
val2 = map(val2, 1, 280, 0, 176);  
myservo2.write(val2);                
delay(25);                          

val3 = analogRead(potpin3);        
val3 = map(val3, 1, 300, 0, 175);  
myservo3.write(val3);               
delay(25);

val4 = analogRead(potpin4);
val4 = map(val4, 1, 320, 0, 175);  
myservo4.write(val4);                
delay(25);                           

val5 = analogRead(potpin5);         
val5 = map(val5, 1, 320, 0, 175);  
myservo5.write(val5);               
delay(25);                          


}


