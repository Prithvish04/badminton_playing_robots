 // ### Code For Shaktiman ### //


#include <PS2X_lib.h>
#include <Servo.h> 
// Variables For the Servo.
Servo gripper;
Servo arm;

int maxdelay;
int mindelay;
//Variable For PS2 Controller
PS2X ps2x; // create PS2 Controller Class
int error = 0;
byte type = 0;
byte vibrate = 0;
float lx;
float ly;
float rx;
float thetha; // angle at which we want the robot to move.
float velocity;
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
int flag;
int hitdelay;
void setup()
{
   mindelay=27+5;
   maxdelay=305;
   flag=0;
   direcA=0;
   direcB=0; 
   direcC=0;
   brakeA=0;
   brakeB=0;
   brakeC=0;
   thetha=0;
   velocity=255;
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
   
   // Checking for any Errors in Controller.
   error = ps2x.config_gamepad(22,3,4,5, false, false);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
   if(error == 0)
   {
    Serial.println("Found Controller, configured successful");
   }
   else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   Serial.print(ps2x.Analog(1), HEX);
   type = ps2x.readType();
   switch(type) 
   {
     case 0:
        Serial.println("Unknown Controller type");
        break;
     case 1:
        Serial.println("DualShock Controller Found");
        break;
     case 2:
        Serial.println("GuitarHero Controller Found");
        break;
   }
}

/*
PSB_START = start
PSB_SELECT = select
PSB_PAD_UP = Pad Button UP
PSB_PAD_RIGHT = Pad Button RIGHT
PSB_PAD_LEFT = Pad Button LEFT
PSB_PAD_DOWN = Pad Button DOWN
PSB_L2 
PSB_L3
PSB_R2
PSB_R3
->Buttons
PSB_RED
PSB_PINK
PSB_BLUE
PSB_GREEN
-> Joystick
PSS_RX
PSS_RY
PSS_LX
PSS_LY
ps2x.Button(nameOfButton);
ps2x.Analog(nameOfButton); -> Returns a analog value.
*/
/*
      if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on) -L2,L3,R2,R3
      if(ps2x.Button(PSB_GREEN))        
      if(ps2x.ButtonPressed(PSB_RED))             //will be TRUE if button was JUST pressed 
      if(ps2x.ButtonReleased(PSB_PINK))           //will be TRUE if button was JUST released
      if(ps2x.NewButtonState(PSB_BLUE))           //will be TRUE if button was JUST pressed OR released
*/       

void runBaseMotors()
{
  digitalWrite(mtrAPin_Direc,direcA);
  digitalWrite(mtrBPin_Direc,direcB);
  digitalWrite(mtrCPin_Direc,direcC);
  analogWrite(mtrAPin,mtrA);
  analogWrite(mtrBPin,mtrB);
  analogWrite(mtrCPin,mtrC);
  delay(10);
}

void setPower()
{
  //Serial.println("ENTERED THE FUNCTION");
  double angle1,angle2,angle3;
  //angle1= lx;
  //angle2= -0.5*lx + 0.866*ly;
  //angle3= -0.5*lx - 0.866*ly;
  angle1=cos(radians(thetha));
  angle2=cos(radians(120-thetha));
  angle3=cos(radians(240-thetha));
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
  velocity=map(velocity,0,128,0,100);
  //if(angle1>0&&angle2>0&&angle3>0)
  //mtrA=velocity*abs(angle1)+30;
  //else
  mtrA=velocity*abs(angle1);
  mtrB=velocity*abs(angle2);
  mtrC=velocity*abs(angle3);
  
  runBaseMotors();
}
void turnR()
{
  mtrA = 100;
  mtrB = 70;  
  mtrC = 70;
  direcA = false;
  direcB = true;
  direcC = true;
  runBaseMotors();
  Serial.println("Turn Right");
  delay(100);
}
void turnL()
{
  mtrA = 100;
  mtrB = 70;
  mtrC = 70;
  direcA = true;
  direcB = false;
  direcC = false;
  runBaseMotors();  
  Serial.println("Turn Left");
  delay(100);
}
  

void checkButton()
{
  if(ps2x.Button(PSB_SELECT))
  {
    Serial.println("SELECT Pressed");
  }
  else if(ps2x.Button(PSB_START))
  {
    hitdelay=295;
  }
  // To Activate the serving mechanism'
  else if(ps2x.Button(PSB_PAD_DOWN)&&flag==0)
  {
    Serial.println("DOWN BUTTON PRESSED");
    arm.write(130);
    delay(500);
    gripper.write(0);
    delay(500);
    arm.write(100);
    flag=1;
  }
  else if(ps2x.Button(PSB_PAD_UP)&&flag==1)
  {
    Serial.println("GREEN PRESSED");
   // arm.write(130);
   // delay(500);
    //grip pos=20 release pos=140
    //arm up pos=100 down pos=130 
    gripper.write(140);
    delay(hitdelay);
    digitalWrite(ServeOn,HIGH);
    digitalWrite(ServeOff,LOW);
    delay(1000);
    digitalWrite(ServeOn,LOW);
    digitalWrite(ServeOff,HIGH);
    delay(500);
    digitalWrite(ServeOn,LOW);
    digitalWrite(ServeOff,LOW);
    arm.write(130);
    flag=0;
  } 
  else if(ps2x.Button(PSB_GREEN))
  {
    digitalWrite(ServeOn,HIGH);
    digitalWrite(ServeOff,LOW);
    delay(1000);
    digitalWrite(ServeOn,LOW);
    digitalWrite(ServeOff,HIGH);
    delay(500);
    digitalWrite(ServeOn,LOW);
    digitalWrite(ServeOff,LOW);
  }
  else if(ps2x.Button(PSB_BLUE))
  {
    brakeA=true;
    brakeB=true;
    brakeC=true;
    digitalWrite(mtrA_Brake,brakeA);
    digitalWrite(mtrB_Brake,brakeB);
    digitalWrite(mtrC_Brake,brakeC);
    delay(500);
    brakeA=false;
    brakeB=false;
    brakeC=false;
    digitalWrite(mtrA_Brake,brakeA);
    digitalWrite(mtrB_Brake,brakeB);
    digitalWrite(mtrC_Brake,brakeC);
    Serial.println("BLUE PRESSED");
  }
  else if(ps2x.Button(PSB_L2)) //To Hit the Shuttle
  {
     Serial.println("L2 PRESSED");
    direcA=direcB=direcC=true;
    mtrA=mtrB=mtrC=120;
    runBaseMotors();
    delay(70);
    
  }
  else if(ps2x.Button(PSB_R2)) //To return to original Positions
  {
    Serial.println("R2 PRESSED");
    direcA=direcB=direcC=false;
    mtrA=mtrB=mtrC=120;
    runBaseMotors();
    delay(70);
  }
  else if(ps2x.Button(PSB_L1))
  {
     Serial.println("L1 PRESSED");
    turnL();
  }
  else if(ps2x.Button(PSB_R1))
  {
     Serial.println("R1 PRESSED");
    turnR();
  }
  
  // To Activate and Deactivate the Hitting Raquet
  if(ps2x.Button(PSB_PAD_RIGHT))
  {
    //Setting equal powers to motors to make the bot rotate
    /*digitalWrite(pistonOn,HIGH);
    digitalWrite(pistonOff,LOW);
    Serial.println("HIT PISTON");
    delay(300);
    digitalWrite(pistonOn,LOW);
    digitalWrite(pistonOff,LOW);    
    */
    hitdelay=hitdelay+1;
    if(hitdelay==maxdelay)
    hitdelay=hitdelay-1;
  }
  else if(ps2x.Button(PSB_PAD_LEFT))
  {
    /*
    digitalWrite(pistonOn,LOW);
    digitalWrite(pistonOff,HIGH);
    Serial.println("RETURN PISTON");
    delay(300);
    digitalWrite(pistonOn,LOW);
    digitalWrite(pistonOff,LOW); 
    */
     hitdelay=hitdelay-1;
    if(hitdelay==mindelay)
    hitdelay=hitdelay+1;
    
  }
  else if(ps2x.Button(PSB_RED))
  {
    hitdelay=maxdelay;
  }
  else if(ps2x.Button(PSB_PINK))
  {
    hitdelay=mindelay;
  }
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
  Serial.print(direcC);
  Serial.print(" Brake A= ");
  Serial.print(brakeA);
  Serial.print(" Brake B= ");
  Serial.print(brakeB);
  Serial.print(" Brake C= ");
  Serial.print(brakeC);
  Serial.println("");
} 

void loop()
{
  
   digitalWrite(pistonOn,LOW);
   digitalWrite(pistonOff,LOW);
   digitalWrite(ServeOn,LOW);
   digitalWrite(ServeOff,LOW);
   error = ps2x.config_gamepad(22,3,4,5, true, true);
   if(error == 1) //skip loop if no controller found
      return;
   if(type == 2)
   {  //Guitar Hero Controller
      ps2x.read_gamepad();          //read controller
      return;
   }
   else 
   { //DualShock Controller
      ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
      vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on
                                             //how hard you press the blue (X) button   
   }
   digitalWrite(mtrA_Brake,brakeA);
   digitalWrite(mtrB_Brake,brakeB);
   digitalWrite(mtrC_Brake,brakeC);
   lx=ps2x.Analog(PSS_LX)-127;
   ly=128-ps2x.Analog(PSS_LY);
   //rx=ps2x.Analog(PSS_RX);
   //Cartecian to Polar Coordinates
   velocity=sqrt(lx*lx+ly*ly); 
   thetha=atan(abs(ly/lx));
   if(lx<=0.0&&ly<=0.0)
   thetha=thetha+radians(180);
   else if(lx>=0.0&&ly<=0.0)
   thetha=radians(360)-thetha;
   else if(lx<=0.0&&ly>=0.0)
   thetha=radians(180)-thetha;
   thetha=degrees(thetha);
   //if(lx!=0&&ly!=0)
   setPower();
   //turnLR();
   Print();
   checkButton();
   digitalWrite(pistonOn,LOW);
   digitalWrite(pistonOff,LOW);
   //delay(10);
}
