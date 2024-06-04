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
boolean flag;
//int flagnp;
//Servo gripper;
//Servo arm;
int maxdelay;
int mindelay;
int mtrA;
int mtrB;
int mtrC;
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
int hitdelay;
char st[25];
int len;
void setup()
{
  ts1=ts2=ts3=true;  //set as true becoz at startup all toggle switches are called and initialized
  flag=false;
  mindelay=275;
  maxdelay=305;
  direcA=0;
  direcB=0; 
  direcC=0;
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
  if(M=='T'&&flag)
  {
    if(A==1&&ts1==false)
    {
      //Serial.println("Load For SERVE");
      //arm.write(130);
      delay(500);
      //gripper.write(0);
      delay(500);
      //arm.write(100);
      flag=1;
    }
    else if(A==1&&ts1==true)
    {
      //Serial.println("SERVE");
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
  else if(M=='A'&&flag)
  {
    //Serial.println("Racquet HIT");
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
    //Serial.println("Rotate ClockWise");
    direcA=direcB=direcC=true;
    mtrA=mtrB=mtrC=60;
    runBaseMotors();
  }
  else if(M=='D')
  {
    //Serial.println("Rotate Anti-ClockWise");
    direcA=direcB=direcC=false;
    mtrA=mtrB=mtrC=60;
    runBaseMotors();
  }    
}

void setPower()
{
  double angle1,angle2,angle3;
  angle1=cos(radians(150-thetha));
  angle2=cos(radians(270-thetha));
  angle3=cos(radians(30-thetha));
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
  if(M=='L')
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
} 

void execute()
{
  if(flag==false&&A>4)
  flag=true;  
  velocity=B;
  thetha=A;
  setPower();
  //Print();
  checkButton();
  digitalWrite(ServeOn,LOW);
  digitalWrite(ServeOff,LOW);
  //delay(10);
}

void processString()
{
  A=B=0;
  M=' ';
  if(st[0]=='J')
  {
    if(st[9]=='L')
    {
      A=(st[14]-'0')*100+(st[15]-'0')*10+(st[16]-'0');
      B=(st[18]-'0')*100+(st[19]-'0')*10+(st[20]-'0');
      M='L';
    }
    else if(st[9]=='R')
    {
      A=(st[15]-'0')*100+(st[16]-'0')*10+(st[17]-'0');
      B=(st[19]-'0')*100+(st[20]-'0')*10+(st[21]-'0'); 
      M='R';
    }
  }
  else if(st[0]=='B')
  {
    if(st[7]!='S')
      M=st[7];
    else
      M=st[8];
  }
  else if(st[0]=='T')
  {
    // A-> the toggle number B-> the toggle value(true,false)
    M='T';
    A=st[7]-'0';
    if(st[9]=='t')
      B=1;
    else if(st[9]=='f')
      B=0;
    if(A==1)
      ts1=B;
  }
  execute();
}

void loop()
{
  if(Serial.available()>0)
  {
    ch=Serial.read();
    if(ch=='<')
      len=0;
    else if(ch=='>')
      processString();
    else
      st[len++]=ch;
    // string of the form = Joystick:Right:090:098 :-no '>'&'<'
  }
}

