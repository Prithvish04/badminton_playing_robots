int num1=9;
int num2=10;
int val;
void setup()
{
  pinMode(num1,OUTPUT);
  pinMode(num2,OUTPUT);
  val=0;
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available()>0)
  {
    char ch=Serial.read();
    val++;
    if(val==3)
    val=0;
  }
  switch(val)
  {
    case 0:
          digitalWrite(num1,HIGH);
          digitalWrite(num2,LOW);
          break;
    case 1:
          digitalWrite(num2,HIGH);
          digitalWrite(num1,LOW);
          break;
    case 2:
          digitalWrite(num1,LOW);
          digitalWrite(num2,LOW);
          break;
  }
  Serial.println(val);
}

