int led1=11;
int led2=10;
int led3=9;
int led4=8;
int s=0;
int flag;
void setup()
{
  /*pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  */
  Serial.begin(9600);
  Serial1.begin(9600);
}
//String a="HELLO";
char ch;
int A,B;
char unit;// to store the name J-L/R S-S
void execute(int a,int b)
{
  Serial.print(a);
  Serial.print(" ");
  Serial.println(b);
  
  if(a==1)
  {
    analogWrite(led1,b);
  }
  else if(a==2)
  {
    analogWrite(led2,b);
  }
  else if(a==3)
  {
    analogWrite(led3,b);
  }
  else if(a==4)
  {
    analogWrite(led4,b);
  }
}

void loop()
{
  if(Serial1.available())
  {
    ch=Serial1.read();
    //Serial.println(ch);
    if(ch=='<')
    {
      s=0;
      A=B=0;
      flag=0;
    }
    if(ch=='R'||ch=='L'||ch=='S')
    unit=ch;
   
   while(ch>=48&&ch<=57&&flag==0)
   {
     A=A*10+int(ch)-'0';
     while(Serial1.available()==0);
     ch=Serial1.read();
     if(ch<48||ch>57)
     flag=1;
   }
   while(ch>=48&&ch<=57&&flag==1)
   {
     B=B*10+int(ch)-'0';
     while(Serial1.available()==0);
     ch=Serial1.read();
     if(ch<48||ch>57)
     flag=2;
   }
   if(ch=='>')
   execute(A,map(B,0,100,0,255));
  }
}
   
   
  
