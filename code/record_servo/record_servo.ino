#include <Servo.h>

Servo servo;
int a[500];
int i,x;
void setup()
{
  Serial.begin(9600);
  Serial.println("RECORDING Mode");
  servo.attach(9);
  servo.write(0);
  Serial.println("RECORDING Mode");
  for(i=0;i<500;i++)
  {
    x=analogRead(A0);
    x=map(x,0,1023,0,180);
    a[i]=x;
    Serial.println(x);
    delay(20);
    //servo.write(x);
  }
  Serial.println("DONE RECORDING");
  i=0;
}

void loop()
{
  /*i=analogRead(A0);
  i=map(i,0,1023,0,180);
  servo.write(i);
  delay(20);
  Serial.println(i);
*/
 while(i<500)
  {
    x=a[i++];
    servo.write(x);
    //Serial.print("DONE for ");
    Serial.println(x);
    delay(10);
  }
  //delay(2000);
}
