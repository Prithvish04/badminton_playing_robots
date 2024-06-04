int hit=9;
int reload=10;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available()>0)
  {
    char ch=Serial.read();
    
    if(ch=='h')
    {
      digitalWrite(hit,HIGH);
      digitalWrite(reload,LOW);
    }
    if(ch=='r')
    {
      digitalWrite(hit,LOW);
      digitalWrite(reload,HIGH);
    }
  }
}
    
