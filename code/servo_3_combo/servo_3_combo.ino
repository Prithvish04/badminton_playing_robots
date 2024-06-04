#include <Servo.h> 
 
Servo servo1, servo2, servo3;  // create servo object to control a servo 
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
 
void out(int a, int b,int c)
{
  Serial.print(a);
  Serial.print(" ");
  Serial.print(b);
  Serial.print(" ");
  Serial.println(c);
}
 
boolean flag=false;
int poten,old;
int hit;
int ser1,ser2,ser3;
void loop() 
{ 
      poten=analogRead(A0);
      //ser1=analogRead(A0);
      //ser2=analogRead(A1);
      //ser3=analogRead(A2);
      //out(ser1,ser2,ser3);
      
      hit=digitalRead(key);
      //if(old!=poten)
      {
        poten=map(poten,0,1023,0,180);
        servo1.write(poten);
        servo2.write(0);
        Serial.println(poten);
        delay(20);
        old=poten;
      }
      if(poten==180)
      {
        servo2.write(50);
        delay(900);
        servo2.write(0);
        delay(1200);
        servo2.write(180);
        delay(900);
        servo2.write(140);
        delay(800);
        servo2.write(0);
      }
        
} 
