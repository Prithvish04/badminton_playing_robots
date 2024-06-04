#include <PS2X_lib.h>  //for v1.6
#include <Servo.h> 
 
Servo arm,gripper,arm3,arm1,arm2;
PS2X ps2x; // create PS2 Controller Class
int i;
//right now, the library does NOT support hot pluggable controllers, meaning
//you must always either restart your Arduino after you conect the controller,
//or call config_gamepad(pins) again after connecting the controller.
int error = 0;
byte type = 0;
byte vibrate = 0;
int lx,ly,rx,ry;
int brake1 = 43;
int direc1 = 49;
int brake2 = 45;
int brake3 = 47;
int direc2=51;
int direc3 = 53;
int speed1 = 10;
int speed2 = 8;
int speed3 = 9;
int mtr1;
int mtr2;
int mtr3;


void setup()
{

  pinMode(brake1,OUTPUT);
  pinMode(direc1,OUTPUT);
  pinMode(speed1,OUTPUT);
  pinMode(brake2,OUTPUT);
  pinMode(direc2,OUTPUT);
  pinMode(speed2,OUTPUT);
  pinMode(brake3,OUTPUT);
  pinMode(direc3,OUTPUT);
  pinMode(speed3,OUTPUT);
  Serial.begin(57600);
 arm.attach(9);
 gripper.attach(10);
 arm3.attach(11);
digitalWrite(brake1,LOW);
digitalWrite(brake2,LOW);
digitalWrite(brake3,LOW);
digitalWrite(direc1,LOW);
digitalWrite(direc2,LOW);
digitalWrite(direc3,LOW);
digitalWrite(speed2,LOW);
digitalWrite(speed3,LOW);
mtr1=0;
mtr2=0;
mtr3=0;
 //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************

 error = ps2x.config_gamepad(8,9,10,11, false, false);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error

 if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
  Serial.println("holding L1 or R1 will print out the analog stick values.");
  Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
  
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
  
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
  
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  
    Serial.print(ps2x.Analog(1), HEX);
  
   type = ps2x.readType();
     switch(type) {
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

void loop(){
   /* You must Read Gamepad to get new values
   Read GamePad and set vibration values
   ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
   if you don't enable the rumble, use ps2x.read_gamepad(); with no values
  
   you should call this at least once a second
   */
  
  error = ps2x.config_gamepad(8,9,10,11, true, true);
  
 if(error == 1) //skip loop if no controller found
  return;

 if(type == 2)
 { //Guitar Hero Controller
  
   ps2x.read_gamepad();          //read controller
  
   return;
 }

 else { //DualShock Controller

    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
  
    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
         Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
         Serial.println("Select is being held");
        
        
     if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
       //digitalWrite(8,HIGH);
       //digitalWrite(9,HIGH);
       //digitalWrite(10,HIGH);
       Serial.println("Up held this hard: ");
       //Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
      }
      else if(ps2x.Button(PSB_PAD_RIGHT)){
       Serial.println("Right held this hard: ");
        //Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
      }
      else if(ps2x.Button(PSB_PAD_LEFT)){
       Serial.println("LEFT held this hard: ");
        //Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
      }
      else if(ps2x.Button(PSB_PAD_DOWN)){
          // digitalWrite(8,LOW);
       //digitalWrite(9,LOW);
       //digitalWrite(10,LOW);
       Serial.println("DOWN held this hard: ");
    // Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
      }
  
      vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on
                                             //how hard you press the blue (X) button   
  
    if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
    {
    
      
        
        if(ps2x.Button(PSB_L3))
        
           Serial.println("L3 pressed");
        if(ps2x.Button(PSB_R3))
         Serial.println("R3 pressed");
        if(ps2x.Button(PSB_L2))
        { Serial.println("L2 pressed");
      //  runmotor();
      }
        if(ps2x.Button(PSB_R2))
        {//stopmotor();
         Serial.println("R2 pressed");}
        if(ps2x.Button(PSB_GREEN))
         Serial.println("Triangle pressed");
        
    } 
        
  
    if(ps2x.ButtonPressed(PSB_RED))             //will be TRUE if button was JUST pressed
         {Serial.println("Circle just pressed");
         }
        
    if(ps2x.ButtonReleased(PSB_PINK))             //will be TRUE if button was JUST released
         {Serial.println("Square just released");
      }   
  
    if(ps2x.NewButtonState(PSB_BLUE))            //will be TRUE if button was JUST pressed OR released
    {     Serial.println("X just changed");   
          mtr1+=10;
          mtr2=0;
          mtr3=0;
          analogWrite(speed1,mtr1);
          analogWrite(speed2,mtr2);
          analogWrite(speed3,mtr3);
    }
    if(ps2x.NewButtonState(PSB_PINK))
    {
      Serial.println("X just changed");   
          mtr1-=10;
          mtr2=0;
          mtr3=0;
          analogWrite(speed1,mtr1);
          analogWrite(speed2,mtr2);
          analogWrite(speed3,mtr3);
    }
          
          
  
    if(lx!=ps2x.Analog(PSS_LX)||ly!=ps2x.Analog(PSS_LY)||rx!=ps2x.Analog(PSS_RX)||ry!=ps2x.Analog(PSS_RY))
      {
        Serial.print("Stick Values : ");
        Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX 
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_LX), DEC);
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_RY), DEC);
        Serial.print(",");
        //Serial.print(rx);
        Serial.println(ps2x.Analog(PSS_RX));
       }
       
       
       
        
      }
 
    lx=ps2x.Analog(PSS_LX);
    ly=ps2x.Analog(PSS_LY);
    rx=ps2x.Analog(PSS_RX);
    ry=ps2x.Analog(PSS_RY);
    analogWrite(speed1,int(ly));
    digitalWrite(brake1,LOW);
    digitalWrite(direc1,HIGH);
    Serial.println(int(ly));
    /*
    gripper.write(map(lx,0,255,0,180));
    arm.write(map(ry,0,255,0,180));
    */
    /*
    if(ps2x.ButtonPressed(PSB_RED))
    {
      for(i=10;i<=90;i++)
      {
        arm.write(i);
        delay(5);
      }
      for(i=0;i<=140;i++)
      {
        gripper.write(i);
        delay(5);
      }
      for(i=90;i>=10;i--)
      {
        arm.write(i);
        delay(5);
      }
      for(i=140;i>=0;i--)
      {
        gripper.write(i);
        delay(5);
      }
    }
    */
    delay(100);
}

//arm1  l

/*void runmotor()
{
  analogWrite(speedy,255);
}
void stopmotor()
{
  analogWrite(speedy,0);
}*/

