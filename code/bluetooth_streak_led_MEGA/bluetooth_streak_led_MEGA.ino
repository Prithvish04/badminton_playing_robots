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
int arr[3];
void execute(int a,int b)
{
  arr[a-1]=b;
  for(int i=0;i<3;i++)
  {
    Serial.print(i+1);
    Serial.print(" ");
    Serial.println(arr[i]);
  }
  
  analogWrite(led1,arr[0]);
  analogWrite(led2,arr[1]);
  analogWrite(led3,arr[2]);
  if(arr[0]==0)
  digitalWrite(brk1,HIGH);
  else
  digitalWrite(brk1,LOW);
  if(arr[1]==0)
  digitalWrite(brk2,HIGH);
  else
  digitalWrite(brk2,LOW);
  if(arr[2]==0)
  digitalWrite(brk3,HIGH);
  else
  digitalWrite(brk3,LOW);
  
  
  /*Serial.print(a);
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
  */
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
   
   
  
