#include <Servo.h> 

Servo sh;  // create servo object to control a servo 
Servo el;              // a maximum of eight servo objects can be created  
 
void setup() 
{ 
  sh.attach(9);  // attaches the servo on pin 9 to the servo object 
  el.attach(10);
  el.write(20);
  sh.write(40);
} 
 
 
void loop() 
{ 
  el.write(60);
  sh.write(120);
  delay(1000);
  sh.write(40);
  delay(1000);
  el.write(100);
  delay(1000);
  
  sh.write(120);
  delay(1000);
  sh.write(40);
  delay(1000);
  el.write(100);
  delay(1000);
  
  sh.write(150);
  delay(1000);
  sh.write(40)
} 
