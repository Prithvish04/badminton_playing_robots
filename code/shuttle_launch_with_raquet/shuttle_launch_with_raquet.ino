#include <Servo.h> 
Servo gripper,arm;  
int pos = 0;    
//int pin1=11;
//int pin2=10;
//int i;
int on=2;
int off=3;
void setup() 
{ //initialising
  gripper.attach(2);
  arm.attach(12); 
  
  pinMode(on,OUTPUT);
  pinMode(off,OUTPUT);
  arm.write(140); 
  gripper.write(140);
  delay(1000);
  pinMode(28,OUTPUT);
  pinMode(29,OUTPUT);
  //Serial.begin(9600);
  //delay(4000);
} 
 
void loop() 
{ 
  arm.write(130);
  delay(500);
  gripper.write(0); //grip pos=20 release pos=140
  delay(500);
  //arm.write(120);
  //delay(100);
  arm.write(100);     //up pos=150 down pos=130 
  delay(500);
  /*digitalWrite(on,HIGH);
  digitalWrite(off,LOW);
  delay(10);
  digitalWrite(on,LOW);
  delay(1000);
  digitalWrite(on,LOW);
  digitalWrite(off,HIGH);
  delay(10);
  digitalWrite(off,LOW);*/
  gripper.write(140);
  delay(200);
  digitalWrite(28,HIGH);
  digitalWrite(29,LOW);
  delay(200);
  digitalWrite(28,LOW);
  digitalWrite(29,HIGH);
  delay(100);
  digitalWrite(28,LOW);
  digitalWrite(29,LOW);  
} 
