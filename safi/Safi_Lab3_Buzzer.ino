int buzzer = D8;
void setup()
{
  pinMode(buzzer,OUTPUT);
}
void loop()
{
 unsigned char i;
 while(1)
{
  for(i=0;i<100;i++)
{
digitalWrite(buzzer,HIGH);
delay(1);
digitalWrite(buzzer,LOW);
delay(1);
}

 for(i=0;i<100;i++)
{
digitalWrite(buzzer,HIGH);
delay(4);
digitalWrite(buzzer,LOW);
delay(4);

}

}

}
