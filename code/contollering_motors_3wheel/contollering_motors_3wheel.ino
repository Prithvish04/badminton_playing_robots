int m1f=11;
int m1r=10;
int m2f=6;
int m2r=5;

// m1->left; m2->right

int s=0;
int flag;
void setup()
{
  /*pinMode(m1f,OUTPUT);
  pinMode(m1r,OUTPUT);
  pinMode(m2f,OUTPUT);
  pinMode(m2r,OUTPUT);
  */
  Serial.begin(9600);
  //Serial.begin(9600);
}
//String a="HELLO";
char ch;
int A,B;
//A=angle
//B=value

void execute(int a,int b)
{
  /*Serial.print(a);
  Serial.print(" ");
  Serial.println(b);
  */
  if(b==0)
  {
    analogWrite(m1f,0);
    analogWrite(m1r,0);
    analogWrite(m2f,0);
    analogWrite(m2r,0);
  }
  else if(a==0)
  {
    analogWrite(m1f,b);
    analogWrite(m1r,0);
    analogWrite(m2f,b);
    analogWrite(m2r,0);
  }
  else if(a==180)
  {
    analogWrite(m1f,0);
    analogWrite(m1r,b);
    analogWrite(m2f,0);
    analogWrite(m2r,b);
  }
  else if(a==270)
  {
    analogWrite(m1f,b);
    analogWrite(m1r,0);
    analogWrite(m2f,0);
    analogWrite(m2r,0);
  }
  else
  {
    if(a<=90)
    {
      analogWrite(m1f,int(b*(1-a/90)));
      analogWrite(m1r,0);
      analogWrite(m2f,b);
      analogWrite(m2r,0);  
    }
    else if(a<180)
    {
      a=a-90;
      analogWrite(m1f,0);
      analogWrite(m1r,int(b*(1-a/90)));
      analogWrite(m2f,0);
      analogWrite(m2r,b);  
    }
    else if(a<270)
    {
      a=a-180;
      analogWrite(m1f,0);
      analogWrite(m1r,b);
      analogWrite(m2f,0);
      analogWrite(m2r,int(b*(1-a/90)));  
    }
    else if(a<360)
    {
      a=a-270;
      analogWrite(m1f,b);
      analogWrite(m1r,0);
      analogWrite(m2f,int(b*(1-a/90)));
      analogWrite(m2r,0);
       
    }
        
  }
}

void loop()
{
  /*if(Serial.available())
  {
    ch=Serial.read();
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
     while(Serial.available()==0);
     ch=Serial.read();
     if(ch<48||ch>57)
     flag=1;
   }
   while(ch>=48&&ch<=57&&flag==1)
   {
     B=B*10+int(ch)-'0';
     while(Serial.available()==0);
     ch=Serial.read();
     if(ch<48||ch>57)
     flag=2;
   }
  
   if(ch=='>')
   {
       Serial.println(A);
       Serial.println(B);
      execute(A,B+155);
   }
  }*/
  A=B=0;
  int j=0;
  for(int i=0;i<360;i++)
  {
    execute(A+i,(B+j)*2);
    j++;
    if(j==90)
    j=0;
    delay(10);
  }
}
   
   
  
