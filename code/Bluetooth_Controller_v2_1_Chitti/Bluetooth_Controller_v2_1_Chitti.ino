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
int maxdelay;
int mindelay;
int mtrA;
int mtrB;
int mtrC;
int ServeOn=7;
int ServeOff=8; //Numatic Pin No to activate and deactivate -- DigitalPins
int mtrAPin=10;
int mtrBPin=11;
int mtrCPin=9;
int mtrAPin_Direc=4;
int mtrBPin_Direc=5;
int mtrCPin_Direc=3;
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
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
  digitalWrite(A3,LOW);
  digitalWrite(ServeOn,LOW);
  digitalWrite(ServeOff,LOW);
  // Gripper and arm Pin Definition
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
  if(M=='A'&&flag)
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
      mtrA=mtrB=mtrC=50;
      runBaseMotors();
  }
  else if(M=='C')
  {
    //Serial.println("Rotate ClockWise");
    direcA=direcB=direcC=true;
    mtrA=mtrB=mtrC=50;
    runBaseMotors();
  }
  else if(M=='D')
  {
    //Serial.println("Rotate Anti-ClockWise");
    direcA=direcB=direcC=false;
    mtrA=mtrB=mtrC=50;
    runBaseMotors();
  }    
}

void setPower()
{
  double angle1,angle2,angle3;
  angle1=cos(radians(150-thetha-60));
  angle2=cos(radians(270-thetha-60));
  angle3=cos(radians(30-thetha-60));
  if(angle1<0.0)
    direcA=true;
  else
    direcA=false;
  if(angle2<0.0)
    direcB=true;
  else
    direcB=false;  
  if(angle3<0.0)
    direcC=true;
  else
    direcC=false;
  mtrA=velocity*abs(angle1);
  mtrB=velocity*abs(angle2);
  mtrC=velocity*abs(angle3);
  if(M=='L')
    runBaseMotors();
}


void execute()
{
  if(flag==false&&A>4)
    flag=true;  
  velocity=B;
  //thetha=((thetha+45)/90)*90;
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


