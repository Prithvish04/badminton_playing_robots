#include <SoftwareSerial.h>

/* You just have to make changes in update function. 
 Take values from BT Module and store them in "j_ang" (angle)
 and "sp" (speed).

Do remember to write the pin no. of motors below, as per 
 your connections 

Motor 1 - left
motor 2 - right
motor 3 - back
*/
SoftwareSerial bluetooth(0,1); // RX, TX
//byte enable1;    //Enable pin                            
byte lspd = 2;        //left motor speed control            
byte ldir1 = 4;      //left motor direction control 1       
byte ldir2 = 5;      //left motor direction control 2       
byte lbrake = 3 ;      //left motor brake                    

//byte enable2;  //Enable pin
byte rspd = 10;      //right motor speed control
byte rdir1 = 12;    //right motor direction control 1
byte rdir2 = 13;      //right motor direction control 2
byte rbrake = 11;  //right motor brake

//byte enable3;    //Enable pin
byte bspd = 6;        //back motor speed control
byte bdir1 = 8;       //back motor direction control 1
byte bdir2 = 9;       //back motor direction control 2
byte zbrake = 7;     //back motor brake       


char BData;
int A,B;


//float angle[]={1,0.5403,-0.41615,-0.98999,-0.65364,0.28366,0.96017,0.7539,-0.1455,-0.91113,-0.83907,0.0044257,0.84385,0.90745,0.13674,-0.75969,-0.95766,-0.27516,0.66032,0.9887,0.40808,-0.54773,-0.99996,-0.53283,0.42418,0.9912,0.64692,-0.29214,-0.96261,-0.74806,0.15425,0.91474,0.83422,-0.013277,-0.84857,-0.90369,-0.12796,0.76541,0.95507,0.26664,-0.66694,-0.98734,-0.39999,0.55511,0.99984,0.52532,-0.43218,-0.99234,-0.64014,0.30059,0.96497,0.74215,-0.16299,-0.91828,-0.82931,0.022127,0.85322,0.89987,0.11918,-0.77108,-0.95241,-0.2581,0.67351,0.9859,0.39186,-0.56245,-0.99965,-0.51777,0.44014,0.99339,0.63332,-0.30902,-0.96725,-0.73619,0.17172,0.92175,0.82433,-0.030975,-0.8578,-0.89597,-0.11039,0.77669,0.94968,0.24954,-0.68002,-0.98438,-0.3837,0.56975,0.99937,0.51018,-0.44807,-0.99437,-0.62644,0.31743,0.96946,0.73017,-0.18043,-0.92515,-0.81929,0.039821,0.86232,0.892,0.10159,-0.78223,-0.94687,-0.24096,0.68649,0.98278,0.37551,-0.577,-0.99902,-0.50254,0.45597,0.99527,0.61952,-0.32581,-0.97159,-0.7241,0.18913,0.92847,0.81418,-0.048664,-0.86677,-0.88797,-0.092776,0.78771,0.94398,0.23236,-0.6929,-0.98111,-0.36729,0.58421,0.99859,0.49487,-0.46383,-0.99609,-0.61255,0.33417,0.97365,0.71796,-0.19781,-0.93172,-0.80901,0.057503,0.87115,0.88386,0.083959,-0.79314,-0.94103,-0.22374,0.69925,0.97935,0.35904,-0.59137,-0.99808,-0.48716,0.47165,0.99683,0.60553,-0.34249,-0.97563,-0.71177,0.20648,0.9349,0.80378,-0.066337,-0.87546,-0.87969,-0.075136,0.7985,0.93799,0.21511,-0.70555,-0.97753,-0.35077,0.59848,0.99749,0.47941,-0.47944,-0.9975,-0.59846,0.3508,0.97753,0.70553,-0.21513,-0.93801,-0.79848,0.075166,0.8797,0.87544,0.066307,-0.80379,-0.93489,-0.20645,0.7118,0.97562,0.34247,-0.60555,-0.99683,-0.47163,0.48719,0.99808,0.59135,-0.35907,-0.97936,-0.69923,0.22377,0.94104,0.79312,-0.083989,-0.88388,-0.87113,-0.057472,0.80903,0.93171,0.19778,-0.71799,-0.97364,-0.33414,0.61257,0.99609,0.4638,-0.4949,-0.99859,-0.58418,0.36732,0.98111,0.69287,-0.23239,-0.94399,-0.7877,0.092806,0.88798,0.86675,0.048634,-0.8142,-0.92846,-0.1891,0.72412,0.97159,0.32578,-0.61954,-0.99526,-0.45594,0.50257,0.99902,0.57698,-0.37554,-0.98279,-0.68646,0.24099,0.94688,0.78221,-0.10162,-0.89202,-0.8623,-0.039791,0.81931,0.92514,0.1804,-0.73019,-0.96945,-0.3174,0.62647,0.99436,0.44805,-0.5102,-0.99937,-0.56973,0.38373,0.98438,0.68,-0.24957,-0.94969,-0.77667,0.11042,0.89598,0.85779,0.030945,-0.82435,-0.92174,-0.17169,0.73621,0.96724,0.30899,-0.63334,-0.99339,-0.44012,0.5178,0.99965,0.56243,-0.39188,-0.9859,-0.67348,0.25813,0.95242,0.77106,-0.11921,-0.89988,-0.8532,-0.022097,0.82933,0.91827,0.16296,-0.74217,-0.96496,-0.30056,0.64017,0.99233,0.43215,-0.52535,-0.99984,-0.55509,0.40001,0.98734,0.66692,-0.26667,-0.95508,-0.76539,0.12799,0.90371,0.84855,0.013247,-0.83424,-0.91473,-0.15422,0.74808,0.9626,0.29211,-0.64694,-0.9912,-0.42415,0.53286,0.99996,0.5477,-0.40811,-0.98871,-0.66029,0.27519,0.95767,0.75967,-0.13677,-0.90746,-0.84384,-0.0043956,0.83909,0.91112,0.14547,-0.75392,-0.96016,-0.28363,0.65367,0.98999,0.41612,-0.54033,-1,-0.54028,0.41617,0.99,0.65362};
int sp;
int j_ang;
float ang;
double speed_wh1;
double speed_wh2;
double speed_wh3;
int sp1;
int sp2;
int sp3;
int k,flag;
char str[20];
void setup() 
{
 // pinMode(enable1, OUTPUT);
  pinMode(lspd, OUTPUT);
  pinMode(ldir1, OUTPUT);
  pinMode(ldir2, OUTPUT);
  pinMode(lbrake, OUTPUT);
  
  //pinMode(enable2, OUTPUT);
  pinMode(rspd, OUTPUT);
  pinMode(rdir1, OUTPUT);
  pinMode(rdir2, OUTPUT);
  pinMode(rbrake, OUTPUT);
  
  //pinMode(enable3, OUTPUT);
  pinMode(bspd, OUTPUT);
  pinMode(bdir1, OUTPUT);
  pinMode(bdir2, OUTPUT); 
  pinMode(zbrake, OUTPUT);  
  bluetooth.begin(38400);
  Serial.begin(9600);
//  digitalWrite(enable1, LOW);      //Enable all the motor drivers
 // digitalWrite(enable2, LOW);
 // digitalWrite(enable3, LOW);
  
}
char ch;
void update()
{
  int pt=0;
  str[pt++]=bluetooth.read();
  
  while(str[pt]!='>')
  {
    while(bluetooth.available()==0);
    str[pt++]=bluetooth.read();
  }
  pt=0;
  while(1)
  {
  //if(Serial.available())
  {
    BData=str[pt++];
    if(BData=='<')
     {
       k=0;
       flag=0;
       A=B=0;
     }
    else if(BData=='>')
    {
      Serial.print(A);
      Serial.print("\t");
      Serial.println(B);
      j_ang=A+90;
      if(j_ang>358)
      j_ang=0;
      sp=B;
      break;     
      //delay(50);
    }
    else
    {
      if(BData>='0'&&BData<='9')
      {
        if(flag<3)
        {
          A=A*10+BData-'0';
          flag++;
        }
        else if(flag<6)
        {
          B=B*10+BData-'0';
          flag++;
        }
      }
    }
  }   }
  
  //j_ang = Take the angle value from BT joystick (float value);
  //              (subtract 90 to change the origin axis)
  //sp = Take the radius vaue from BT joystick (int value);
   ang=(float)0.01745*j_ang;
   
   
}

void speed_cont()
{
 
speed_wh1 = (double)2/3 * sp * cos( ang);
speed_wh2 = (double)2/3 * sp * cos( ang - 2.094);
speed_wh3 = (double)2/3 * sp * cos( ang - 4.188);

}

void manual()
{
 if(speed_wh1>0)
{ 
  sp1 = (int)map(speed_wh1,0,66.667,0,255);
  digitalWrite(lbrake, LOW);
  digitalWrite(ldir1, LOW);
  digitalWrite(ldir2, HIGH);
  analogWrite(lspd, sp1);
}
else if(speed_wh1<0)
{
  speed_wh1=-1*speed_wh1;
  sp1 = (int)map(speed_wh1,0,66.667,0,255);
  digitalWrite(lbrake, LOW);
  digitalWrite(ldir1, HIGH);
  digitalWrite(ldir2, LOW);
  analogWrite(lspd, sp1);
  
}
else
{
  analogWrite(lspd, 0);
  digitalWrite(lbrake, HIGH);
  
}

if(speed_wh2>0)
{ 
  sp2 = (int)map(speed_wh2,0,66.667,0,255);
  digitalWrite(rbrake, LOW);
  digitalWrite(rdir1, LOW);
  digitalWrite(rdir2, HIGH);
  analogWrite(rspd, sp2);
}
else if(speed_wh2<0)
{
  speed_wh2=-1*speed_wh2;
  sp2 = (int)map(speed_wh2,0,66.667,0,255);
  digitalWrite(rbrake, LOW);
  digitalWrite(rdir1, HIGH);
  digitalWrite(rdir2, LOW);
  analogWrite(rspd, sp2);
  
}
else
{
  analogWrite(rspd, 0);
  digitalWrite(rbrake, HIGH);
  
}

if(speed_wh3>0)
{ 
  sp3 = (int)map(speed_wh3,0,66.667,0,255);
  digitalWrite(zbrake, LOW);
  digitalWrite(bdir1, LOW);
  digitalWrite(bdir2, HIGH);
  analogWrite(bspd, sp3);
}
else if(speed_wh3<0)
{
  speed_wh3=-1*speed_wh3;
  sp3 = (int)map(speed_wh3,0,66.667,0,255);
  digitalWrite(zbrake, LOW);
  digitalWrite(bdir1, LOW);
  digitalWrite(bdir2, HIGH);
  analogWrite(bspd, sp3);
  
}
else
{
  analogWrite(bspd, 0);
  digitalWrite(zbrake, HIGH);
  
}
   
}
void loop() 
{
update(); 
speed_cont();
manual();
}
