// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  pos=90;
  myservo.write(0);
  Serial.begin(9600);
} 
 
boolean flag=false;
void loop() 
{ 
    for(int i=0;i<240;i++)
    {
      myservo.write(i);
      int x=analogRead(A0);
      Serial.println(x);
      //delay(1);
    }
    for(int i=240;i>=0;i--)
    {
      myservo.write(i);
      int x=analogRead(A0);
      Serial.println(x);
      //delay(1);
    }
} 
