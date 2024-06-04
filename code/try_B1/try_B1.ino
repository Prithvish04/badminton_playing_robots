int led=13;

void setup()
{
  Serial.begin(38400);
  pinMode(led,OUTPUT);
}

void loop()
{
  if(Serial.available())
  {
    char c=Serial.read();
    
    if(c>=97&&c<=122)
    {
      digitalWrite(led,HIGH);
      delay(10000);
    }
    else
    {
      digitalWrite(led,LOW);
    }
  }
}
