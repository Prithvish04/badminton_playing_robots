#include <SoftwareSerial.h>

SoftwareSerial mySerial(10,11); //RX,TX

int A; //angle
int B; //displacement;
int velocity;
int thetha;
char M;
char ch;
boolean ts1;
boolean ts2;
boolean ts3;
int flag;
boolean flag2;
int maxdelay;
int mindelay;
int mtrA;
int mtrB;
int mtrC;
int pistonOn=29;
int pistonOff=28; //Numatic Pin No to activate and deactivate -- DigitalPins
int ServeOn=30;
int ServeOff=31; //Numatic Pin No to activate and deactivate -- DigitalPins
// 7,4,5,6
int Gripper = 6;
int Arm = 7;
int mtrAPin=9;
int mtrBPin=10;
int mtrCPin=8;
int mtrAPin_Direc=49;
int mtrBPin_Direc=53;
int mtrCPin_Direc=51;
int mtrA_Brake=43;
int mtrB_Brake=45;
int mtrC_Brake=47;
int maxPower = 255;
boolean direcA;
boolean direcB;
boolean direcC;
// Brake value (to activate brake)= high
boolean brakeA;
boolean brakeB;
boolean brakeC;
int hitdelay;
void setup()
{
  ts1=ts2=ts3=true;  //set as true becoz at startup all toggle switches are called and initialized
  mindelay=275;
  maxdelay=305;
  direcA=0;
  direcB=0; 
  direcC=0;
  brakeA=0;
  brakeB=0;
  brakeC=0;
  thetha=0;
  velocity=0;
  mtrA=0;
  mtrB=0;
  mtrC=0;
  hitdelay=285;
  pinMode(mtrAPin,OUTPUT);
  pinMode(mtrBPin,OUTPUT);
  pinMode(mtrCPin,OUTPUT);
  pinMode(mtrAPin_Direc,OUTPUT);
  pinMode(mtrBPin_Direc,OUTPUT);
  pinMode(mtrCPin_Direc,OUTPUT);
  pinMode(mtrA_Brake,OUTPUT);
  pinMode(mtrB_Brake,OUTPUT);
  pinMode(mtrC_Brake,OUTPUT);
  pinMode(pistonOn,OUTPUT);
  pinMode(pistonOff,OUTPUT);
  pinMode(ServeOn,OUTPUT);
  pinMode(ServeOff,OUTPUT);
  // Gripper and arm Pin Definition
  arm.attach(Arm);
  gripper.attach(Gripper);
  arm.write(130); 
  gripper.write(140);
  Serial.begin(9600);
  mySerial.begin(9600);
}

void execute()
{
  Serial.print(" A= ");
  Serial.print(A);
  Serial.print(" B= ");
  Serial.print(B);
  Serial.print(" M= ");
  Serial.println(M);
}
void readchar()
{
  Serial.print("Q");
  while(1)
  {
    if(mySerial.available()>0)
    {
      ch=mySerial.read();
      Serial.print(ch);
      Serial.println("Z");
      break;
    }
  }
}
void loop()
{
  if(mySerial.available()>0)
  {
    ch=mySerial.read();
    //Serial.print(ch);
    if(ch=='<')
    {
      Serial.println("NEW STRING");
      A=B=0;
      flag=0;
      M=' ';
    }
    else if(ch=='>')
    {
      flag=-1;
      Serial.println("ENTER");
      execute();
    }
    if(flag==0)
    {
      if(ch=='J'||ch=='B'||ch=='T')
      {
        //Serial.println("NEW STRING J");
        flag=1;
      }
    }
    else if(ch==':')
    {
      flag++;
    }
    else if(flag==2)
    {
      if(ch=='R'||ch=='L'||ch=='A'||ch=='B'||ch=='C'||ch=='D')
      {
        M=ch;
        flag=3;
        flag2=true;
      }
      else if(ch=='S')
      {
        M=ch;
        flag=3;
      }
      else if(ch=='1')
      {
        ts1=!ts1;
        flag=3;
      }
      else if(ch=='2')
      {
        ts2=!ts2;
        flag=3;
      }
      else if(ch=='3')
      {
        ts3=!ts3;
        flag=3;
      }
    }
    else if(flag==3)
    {
      if(ch=='e')
      {
        A=1;
        flag=4;
      }
      else if(ch=='t')
      {
        A=2;
        flag=4;
      }
    }
    else if(flag==4||flag==5)
    {
      if(flag2==true)
      {
        A=0;
        flag2=false;
      }
      if(ch>=48&&ch<=57)
        A=A*10+int(ch)-'0';
    }
    else if(flag==6)
    {
      if(ch>=48&&ch<=57)
        B=B*10+int(ch)-'0';
    } 
  }
}

