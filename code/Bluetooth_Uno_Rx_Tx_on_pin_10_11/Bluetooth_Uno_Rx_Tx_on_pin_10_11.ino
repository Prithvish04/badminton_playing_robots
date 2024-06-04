#include <SoftwareSerial.h>
SoftwareSerial mySerial(10,11); //RX and TX

// FOR AT COMMANDS 
//COM port Both NL&CR
int baud1=38400;
int baud2=38400;
void setup()
{
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  Serial.begin(9600);
  digitalWrite(13,HIGH);
  mySerial.begin(9600);
}

void loop()
{
  if(mySerial.available()>0)
  {
    char ch=mySerial.read();
    Serial.print(ch);
    if(ch=='.')
    Serial.println("");
  }
  if(Serial.available()>0)
  {
    char ch=Serial.read();
    mySerial.print(ch);
  }
}
