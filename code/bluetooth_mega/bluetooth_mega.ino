void setup()
{
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  Serial1.begin(38400);
  Serial.begin(38400);
}
void loop()
{
  if(Serial.available())
  {
    char ch=Serial.read();
    Serial1.print(ch);
  }
  if(Serial1.available())
  {
    char ch=Serial1.read();
    Serial.print(ch);
  } 
}
