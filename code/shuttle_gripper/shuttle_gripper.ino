#include <Servo.h> 
Servo gripper,arm;  
int pos = 0;    
//int pin1=11;
//int pin2=10;
//int i;

void setup() 
{ //initialising
  gripper.attach(10);
  arm.attach(9); 
  
  arm.write(140); 
  
  gripper.write(140);
  delay(1000);
  //Serial.begin(9600);
  //delay(4000);
} 
 
void loop() 
{ arm.write(145);
  delay(500);
  gripper.write(20); //grip pos=20 release pos=140
  delay(500);
  //arm.write(120);
  //delay(100);
  arm.write(130);     //up pos=150 down pos=130 
  delay(3000);
  gripper.write(140);
  delay(100);
  
  //gripper.write(0);
  //arm.write(10);
  //delay(10000);
  /*
  if(Serial.available()>0)
  {  
      char ch=Serial.read();
      for(i=10;i<=80;i++)
      {
        arm.write(i);
        delay(5);
      }
      for(i=0;i<=140;i++)
      {
        gripper.write(i);
        delay(5);
      }
      for(i=80;i>=10;i--)
      {
        arm.write(i);
        delay(5);
      }
      for(i=140;i>=0;i--)
      {
        gripper.write(i);
        delay(5);
      }
  }
  */
} 
