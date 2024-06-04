#include <Servo.h> 
 
Servo servo1, servo2;  // create servo object to control a servo 
int key=8;
void setup() 
{ 
  pinMode(13,OUTPUT);
  pinMode(key,INPUT);
  servo1.attach(9);  // attaches the servo on pin 9 to the servo object 
  servo2.attach(11); // attach the racquet servo 
  servo1.write(0);
  digitalWrite(13,LOW);
  delay(500);
  servo2.write(0);
  delay(500);
  digitalWrite(13,HIGH);
  Serial.begin(9600);
} 
 
boolean flag=false;
int poten,old;
int hit;
void loop() 
{ 
      poten=analogRead(A0);
      hit=digitalRead(key);
      if(old!=poten)
      {
        poten=map(poten,0,1023,0,120);
        servo1.write(poten);
        servo2.write(0);
        delay(20);
        old=poten;
      }
      if(key==1)
      {
        servo2.write(30);
        delay(50);
        servo2.write(0);
        delay(200);
        servo2.write(120);
        delay(50);
        servo2.write(90);
        delay(200);
        servo2.write(0);
      }
        
} 
