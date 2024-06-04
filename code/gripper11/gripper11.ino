// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
Servo myservo;
int pos = 0;    // variable to store the servo position 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  
} 
 
 
void loop() 
{ 
  
  for(pos = 140; pos >=0; pos -= 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(10);
  }
  //for(pos = 120; pos >=0; pos -= 1)  // goes from 0 degrees to 180 degrees 
  delay(2000);
} 
