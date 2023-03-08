char entry;
void setup()
{
pinMode(D4,OUTPUT);
Serial.begin(230400);
digitalWrite(D4,HIGH);

}

void loop()
{
  Serial.println(" press S for on and I for off condition");

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
