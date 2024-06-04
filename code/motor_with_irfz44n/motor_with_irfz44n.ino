int pwr;
boolean val;
void setup()
{
  pwr=0;
  val=false;
  Serial.begin(9600);
  pinMode(13,INPUT);
  pinMode(3,OUTPUT);
}

void loop()
{
  if(Serial.available()>0)
  {
    char ch=Serial.read();
    val=!val;
 
  }
  if(pwr>255||pwr<0)
  pwr=100;
  digitalWrite(13,digitalRead(13));
  digitalWrite(3,val);
  Serial.println(val);
}
