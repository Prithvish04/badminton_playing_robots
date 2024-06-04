#include<SoftwareSerial.h>
/*
pin 0=Rx
pin 1=Tx
key =9;
vcc =5V
gnd =gnd
*/
SoftwareSerial bluetooth(10, 11); // RX, TX
int led = 13;
char BData;
char str[20];
int A;//j_ang;
int B;//sp;
int j,k;
int flag;
int count=0;
char ch;
void setup()
{
  bluetooth.begin(19200);
  Serial.begin(19200);
  pinMode(led,OUTPUT);
  //Serial.begin(9600);
  //pinMode(led,OUTPUT);
}
/*void skip(short i)
{
     //char BData;
     short j;
     for(j=0;j<i;j++)
     {
      while (bluetooth.available()==0);
       BData=bluetooth.read();
     }
}*/
void loop()
{
  digitalWrite(led,LOW);
  if(bluetooth.available())
  {
    BData=bluetooth.read();
    
    //A=(int)(BData-'0');
    Serial.println(BData);
    //Serial.println(A);
     /* for(int i=0;i<A;i++)
      {
        Serial.println(count);
count=count+1;
digitalWrite(led,HIGH);
        delay(200);
        digitalWrite(led,LOW);
        delay(200);
      }*/
      //A=0;
    /*if(BData=='S')
     {
       k=0;
       flag=0;
       A=B=0;
     }
    else if(flag==4)
    {
      for(int i=0;i<A;i++)
      {
        digitalWrite(led,HIGH);
        delay(100);
        digitalWrite(led,LOW);
        delay(100);
      }
      digitalWrite(led,B*10);
      
    }
    else
    {
      if(BData>='0'&&BData<='9')
      {
        if(flag<1)
        {
          A=A*10+BData-'0';
          flag++;
        }
        else if(flag<4)
        {
          B=B*10+BData-'0';
          flag++;
        }
      }*/
      
    //}
  }   
}

/*
void master1()
{
    k=0;
    while (bluetooth.available()==0); // change to if
       BData=bluetooth.read();
    
   // if(BData=='<')
    while(BData!='>')
    {
                     A=B=0;
                     //skip(1); 
                      if(BData=='J')
                      {
                                   str[k++]='J';
                                   skip(1);
                                   while (bluetooth.available()==0); // change to if
                                     BData=bluetooth.read();
                                   if(BData=='R')
                                   {
                                                  str[k++]='R';
                                                  skip(5);
                                   }
                                   if(BData=='L')
                                   {
                                                 str[k++]='L';
                                                 skip(4);
                                   }
                                   A=0;
                                   for(j=0;j<3;j++)
                                   {
                                                   while (bluetooth.available()==0); // change to if
                                                     BData=bluetooth.read();
                                                   BData-='0';
                                                   A=A*10+BData;
                                   }
                                   skip(1);
                                   B=0;
                                   for(j=0;j<3;j++)
                                   {
                                                   while (bluetooth.available()==0); // change to if
                                                     BData=bluetooth.read();
                                                   BData-='0';
                                                   B=B*10+BData;
                                   }
                       }
					  if(BData>=65&&BData<=68)
					  {	  
                                                  str[k++]=BData;
						  skip(2);
						  break;
                       
					  }
                      if(BData=='T')
                      {
                                    str[k++]=BData;
                                    skip(1);
                                    while (bluetooth.available()==0); // change to if
                                     BData=bluetooth.read();
                                    A=BData-'0';
                                    skip(1);
                                    while (bluetooth.available()==0); // change to if
                                     BData=bluetooth.read();
                                    if(BData=='t')
                                    {
                                                   B=1;
                                                   skip(3);
                                    }
                                    else if(BData=='f')
                                    {
                                         B=0;
                                         skip(4);
                                    }
                      }
                      if(BData=='S')
                      {
                                    str[k++]=BData;
                                    skip(1);
                                    while (bluetooth.available()==0); // change to if
                                     BData=bluetooth.read();
                                    A=BData-'0';
                                    skip(1);
                                    B=0;
                                   for(j=0;j<3;j++)
                                   {
                                                   while (bluetooth.available()==0); // change to if
                                                       BData=bluetooth.read();
                                                   BData-='0';
                                                   B=B*10+BData;
                                   }
                      }
                                    
                      while (bluetooth.available()==0); // change to if
                         BData=bluetooth.read();             
                      //BData=getche();
                      //cout<<"\nDone!";
    } 
    //str[k]='\n';
    Serial.print(str);
    Serial.print("\t");
    Serial.print(A);
    Serial.print("\t");
    Serial.println(B);
    //cout<<str<<"\t"<<A<<"\t"<<B;
    
}*/
