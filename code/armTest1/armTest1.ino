#include <Servo.h> 
Servo myservo;  // create servo object to control a servo 
void setup() 
{ 
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() 
{ 
  if(Serial.available()>0)
  {
    char ch=Serial.read();
    myservo.write(0);
    delay(1000);
    myservo.write(180);
    delay(2000);
  }
    
} 
