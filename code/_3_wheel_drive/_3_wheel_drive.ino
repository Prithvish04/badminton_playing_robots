#include <SoftwareSerial.h>
SoftwareSerial mySerial(10,11); //RX and TX

char ch;
int A,B;
int flag;
void setup()
{
  pinMode(13,OUTPUT);
  //Serial.begin(9600);
  digitalWrite(13,LOW);
  mySerial.begin(38400);
}

void loop()
{
  if(mySerial.available())
  {
    ch=mySerial.read();
    //Serial.println(ch);
    if(ch=='<')
    {
      //s=0;
      A=B=0;
      flag=0;
    }

   while(ch>=48&&ch<=57&&flag==0)
   {
     A=A*10+int(ch)-'0';
     while(mySerial.available()==0);
     ch=mySerial.read();
     if(ch<48||ch>57)
     flag=1;
   }
   while(ch>=48&&ch<=57&&flag==1)
   {
     B=B*10+int(ch)-'0';
     while(mySerial.available()==0);
     ch=mySerial.read();
     if(ch<48||ch>57)
     flag=2;
   }
   if(ch=='>')
   {
     //Serial.print(A);
     //Serial.print(" ");
     //Serial.println(B);
     if(B<90 && A>50)
     {
       digitalWrite(13,HIGH);
       delay(1500);
       digitalWrite(13,LOW);
     }
   }
  }
}
