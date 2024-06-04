int mtr1=11;
int mtr2=10;
int mtr3=9;
//int led4=6;
int s=0;
int flag;
int ct[3][2];
int i,j;
void setup()
{
  /*pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  */
  for(i=0;i<3;i++)
  for(j=0;j<2;j++)
  ct[i][j]=0;
  Serial.begin(9600);
  Serial1.begin(9600);
}
//String a="HELLO";
char ch;
int A,B;
void execute(int a,int b,char ch)
{
    if(ch=='S')
    {
      ct[a-1][1]=b;
    }
    if(ch=='A')
    {
      if(ct[0][0]==0)
      ct[0][0]=1;
      else
      ct[0][0]=0;
    }
    else if(ch=='C')
    {
      if(ct[1][0]==0)
      ct[1][0]=1;
      else
      ct[1][0]=0;
    }
    else if(ch=='D')
    {
      if(ct[2][0]==0)
      ct[2][0]=1;
      else
      ct[2][0]=0;
    }
    if(ct[0][0]==1)
    analogWrite(mtr1,ct[0][1]);
    if(ct[1][0]==1)
    analogWrite(mtr2,ct[1][1]);
    if(ct[2][0]==1)
    analogWrite(mtr3,ct[2][1]);
     for(i=0;i<3;i++)
     {
       Serial.print(ct[i][0]);
       Serial.print(" ");
       Serial.println(ct[i][1]);
     }
}
/*
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
}*/
char unit;

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
   if(ch=='A'||ch=='C'||ch=='D'||ch=='S')
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
   execute(A,map(B,0,100,0,255),unit);
  }
}
   
   
  
