char entry;
void setup()
{
pinMode(D4,OUTPUT);
Serial.begin(230400);
}

void loop()
{
  
  /*Serial.println("what do you want with your light");*/
if(Serial.available()>0)
{
  entry=Serial.read();
  if(entry=='S')
{
    digitalWrite(D4,LOW);
}
else if(entry=='I')
{
digitalWrite(D4,HIGH);
}
else
{
/*Serial.println("invalid input");*/
}
}
}
