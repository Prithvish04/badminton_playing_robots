#include <SoftwareSerial.h>
SoftwareSerial mySerial(10,11); //RX and TX

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
//int flagnp;
//Servo gripper;
//Servo arm;
boolean direcA;
boolean direcB;
boolean direcC;
int maxdelay;
int mindelay;
int mtrA;
int mtrB;
int mtrC;
int hitdelay;

void setup()
{
  Serial.begin(57600);
  mySerial.begin(57600);
}

void Print()
{
  Serial.print("Hit Delay=");
  Serial.println(hitdelay);
  Serial.print(" Speed MTR A= ");
  Serial.print(mtrA);
  Serial.print(" Speed MTR B= ");
  Serial.print(mtrB);
  Serial.print(" Speed MTR C= ");
  Serial.print(mtrC);
  Serial.print(" MTR_DIREC A= ");
  Serial.print(direcA);
  Serial.print(" MTR_DIREC B= ");
  Serial.print(direcB);
  Serial.print(" MTR_DIREC C= ");
  Serial.println(direcC);
} 
void runBaseMotors()
{
  //digitalWrite(mtrAPin_Direc,direcA);
  //digitalWrite(mtrBPin_Direc,direcB);
  //digitalWrite(mtrCPin_Direc,direcC);
  //analogWrite(mtrAPin,mtrA);
  //analogWrite(mtrBPin,mtrB);
  //analogWrite(mtrCPin,mtrC);
  delay(10);
}
void checkButton()
{
  if(M=='T')
  {
    if(A==1&&ts1==false)
    {
      Serial.println("Load For SERVE");
      //arm.write(130);
      delay(500);
      //gripper.write(0);
      delay(500);
      //arm.write(100);
      flag=1;
    }
    else if(A==1&&ts1==true)
    {
      Serial.println("SERVE");
      //grip pos=20 release pos=140
      //arm up pos=100 down pos=130 
      //gripper.write(140);
      delay(hitdelay);

      delay(1000);

      delay(500);
      //arm.write(130);
    }
  }
  else if(M=='A')
  {
    Serial.println("Racquet HIT");
    
    delay(1000);
    
    delay(500);

  }   
  else if(M=='B')
  {
    mtrA=mtrB=mtrC=0;
    runBaseMotors();
  }
  else if(M=='C')
  {
    Serial.println("Rotate ClockWise");
    direcA=direcB=direcC=true;
    mtrA=mtrB=mtrC=60;
    runBaseMotors();
  }
  else if(M=='D')
  {
    Serial.println("Rotate Anti-ClockWise");
    direcA=direcB=direcC=false;
    mtrA=mtrB=mtrC=60;
    runBaseMotors();
  }    
}


void setPower()
{
  double angle1,angle2,angle3;
  angle1=cos(radians(150-thetha+120));
  angle2=cos(radians(270-thetha+120));
  angle3=cos(radians(30-thetha+120));
  if(angle1<0.0)
    direcA=false;
  else
    direcA=true;
  if(angle2<0.0)
    direcB=false;
  else
    direcB=true;  
  if(angle3<0.0)
    direcC=false;
  else
    direcC=true;
  mtrA=velocity*abs(angle1);
  mtrB=velocity*abs(angle2);
  mtrC=velocity*abs(angle3);

  runBaseMotors();
}
void execute()
{
  Serial.print(" A= ");
  Serial.print(A);
  Serial.print(" B= ");
  Serial.print(B);
  Serial.print(" M= ");
  Serial.println(M);

  velocity=B;
  thetha=A;
  setPower();
  Print();
  checkButton();
  
}

void loop()
{
  if(mySerial.available()>0)
  {
    ch=mySerial.read();
    Serial.print(ch);
    if(ch=='<')
    {
      //Serial.println("NEW STRING");
      A=B=0;
      flag=0;
      M=' ';
    }
    else if(ch=='>')
    {
      flag=-1;
      B=3*B/2;
      //Serial.println("ENTER");
      execute();
    }
    if(flag==0)
    {
      if(ch=='J'||ch=='B'||ch=='T')
      {
        //Serial.println("NEW STRING J");
        flag=1;
        M=ch;  
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
        //Serial.println(ch);
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
        A=1;
        flag=3;
      }
      else if(ch=='2')
      {
        ts2=!ts2;
        A=2;
        flag=3;
      }
      else if(ch=='3')
      {
        ts3=!ts3;
        A=3;
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
    //execute();  
  }
}






