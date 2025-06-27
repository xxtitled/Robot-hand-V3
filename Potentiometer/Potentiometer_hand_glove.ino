#include <Servo.h>

Servo myservo1;         // thumb
Servo myservo2;         // dig 2
Servo myservo3;         // dig 3
Servo myservo4;         // dig 4
Servo myservo5;         // dig 5


int potpin  = 0;         // thumb 0A -analog pin used to connect the potentiometer-
int potpin2 = 1;         // dig 2 01 -analog pin used to connect the potentiometer-
int potpin3 = 2;         // dig 3 02 -analog pin used to connect the potentiometer-
int potpin4 = 3;         // dig 3 03 -analog pin used to connect the potentiometer-
int potpin5 = 4;         // dig 4 04 -analog pin used to connect the potentiometer-

int val  = 0;            // variable to read the value from the analog pin
int val2 = 0;
int val3 = 0;
int val4 = 0;
int val5 = 0;



void setup()
{

myservo1.attach(9);    // attaches the servo on pin 9 to the servo object
myservo2.attach(10);   // attaches the servo on pin 10 to the servo object
myservo3.attach(11);   // attaches the servo on pin 11 to the servo object
myservo4.attach(12);   // attaches the servo on pin 12 to the servo object
myservo5.attach(13);   // attaches the servo on pin 13 to the servo object

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

val2 = analogRead(potpin2);         // reads the value of the potentiometer (value between 0 and 1023)
val2 = map(val2, 1, 280, 0, 176);  // scale it to use it with the servo (value between 0 and 180)
myservo2.write(val2);               // sets the servo position according to the scaled value 
delay(25);                          // waits for the servo to get there // waits for the servo to get there 

val3 = analogRead(potpin3);         // reads the value of the potentiometer (value between 0 and 1023)
val3 = map(val3, 1, 300, 0, 175);  // scale it to use it with the servo (value between 0 and 180)
myservo3.write(val3);               // sets the servo position according to the scaled value 
delay(25);

val4 = analogRead(potpin4);         // reads the value of the potentiometer (value between 0 and 1023)
val4 = map(val4, 1, 320, 0, 175);  // scale it to use it with the servo (value between 0 and 180)
myservo4.write(val4);               // sets the servo position according to the scaled value 
delay(25);                          // waits for the servo to get there 

val5 = analogRead(potpin5);         // reads the value of the potentiometer (value between 0 and 1023)
val5 = map(val5, 1, 320, 0, 175);  // scale it to use it with the servo (value between 0 and 180)
myservo5.write(val5);               // sets the servo position according to the scaled value 
delay(25);                          // waits for the servo to get there 


}
