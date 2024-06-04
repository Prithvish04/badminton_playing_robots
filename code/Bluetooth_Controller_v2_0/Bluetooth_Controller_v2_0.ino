//#include <Servo.h>

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
int maxdelay;
int mindelay;
int mtrA;
int mtrB;
int mtrC;
//int ServeOn=13;
//int ServeOff=12; //Numatic Pin No to activate and deactivate -- DigitalPins
int ServeOn=7;
int ServeOff=6; //Numatic Pin No to activate and deactivate -- DigitalPins
// 7,4,5,6
//int Gripper = 3;
//int Arm = 2;
int mtrAPin=11;
int mtrBPin=9;
int mtrCPin=10;
int mtrAPin_Direc=3;
int mtrBPin_Direc=4;
int mtrCPin_Direc=2;
boolean direcA;
boolean direcB;
boolean direcC;
// Brake value (to activate brake)= high
//boolean brakeA;
//boolean brakeB;
//boolean brakeC;
int hitdelay;

void setup()
{
  ts1=ts2=ts3=true;  //set as true becoz at startup all toggle switches are called and initialized
  mindelay=275;
  maxdelay=305;
  direcA=0;
  direcB=0; 
  direcC=0;
  //brakeA=0;
  //brakeB=0;
  //brakeC=0;
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
  pinMode(ServeOn,OUTPUT);
  pinMode(ServeOff,OUTPUT);
  digitalWrite(ServeOn,LOW);
  digitalWrite(ServeOff,LOW);
  // Gripper and arm Pin Definition
  //arm.attach(Arm);
  //gripper.attach(Gripper);
  //arm.write(130); 
  //gripper.write(140);
  Serial.begin(57600);
}

void runBaseMotors()
{
  digitalWrite(mtrAPin_Direc,direcA);
  digitalWrite(mtrBPin_Direc,direcB);
  digitalWrite(mtrCPin_Direc,direcC);
  analogWrite(mtrAPin,mtrA);
  analogWrite(mtrBPin,mtrB);
  analogWrite(mtrCPin,mtrC);
  //delay(10);
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
      digitalWrite(ServeOn,HIGH);
      digitalWrite(ServeOff,LOW);
      delay(1000);
      digitalWrite(ServeOn,LOW);
      digitalWrite(ServeOff,HIGH);
      delay(500);
      digitalWrite(ServeOn,LOW);
      digitalWrite(ServeOff,LOW);
      //arm.write(130);
    }
  }
  else if(M=='A')
  {
    Serial.println("Racquet HIT");
    digitalWrite(ServeOn,HIGH);
    digitalWrite(ServeOff,LOW);
    delay(1000);
    digitalWrite(ServeOn,LOW);
    digitalWrite(ServeOff,HIGH);
    delay(500);
    digitalWrite(ServeOn,LOW);
    digitalWrite(ServeOff,LOW);
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
  //Serial.println("ENTERED THE FUNCTION");
  double angle1,angle2,angle3;
  //angle1= lx;
  //angle2= -0.5*lx + 0.866*ly;
  //angle3= -0.5*lx - 0.866*ly;
  /*
  angle1=cos(radians(thetha));
   angle2=cos(radians(120-thetha));
   angle3=cos(radians(240-thetha));
   */
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
  //Serial.print(" Brake A= ");
  //Serial.print(brakeA);
  //Serial.print(" Brake B= ");
  //Serial.print(brakeB);
  //Serial.print(" Brake C= ");
  //Serial.print(brakeC);

} 

void execute()
{
  Serial.print(" A= ");
  Serial.print(A);
  Serial.print(" B= ");
  Serial.print(B);
  Serial.print(" M= ");
  Serial.println(M);
  digitalWrite(ServeOn,LOW);
  digitalWrite(ServeOff,LOW);

  velocity=B;
  thetha=A;
  setPower();
  Print();
  checkButton();
  digitalWrite(ServeOn,LOW);
  digitalWrite(ServeOff,LOW);
  //delay(10);
}

void loop()
{
  if(Serial.available()>0)
  {
    ch=Serial.read();
    //Serial.print(ch);
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






