int on=30;
int off=31;
void setup()
{
  pinMode(on,OUTPUT);
  pinMode(off,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available()>0)
  {
    char ch=Serial.read();
    digitalWrite(on,HIGH);
    digitalWrite(off,LOW);
    delay(1500);
    digitalWrite(on,LOW);
    digitalWrite(off,HIGH);
    delay(1500);    
    digitalWrite(on,LOW);
    digitalWrite(off,LOW);
  }
}


