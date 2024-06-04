int led1;
int led2;
int led3;
int led4;
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
char ch;
int A,B;

void execute(int a,int b)
{
  Serial.print(a);
  Serial.print(" ");
  Serial.println(b);
}

void loop()
{
  if(Serial1.available())
  {
    
    ch=Serial1.read();
    Serial.print(ch);
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
   {
   execute(A,B);
    Serial.println();
   }  
}
}
   
   
  
