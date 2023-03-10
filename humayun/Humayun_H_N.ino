byte Letter = 0;

void setup() {
pinMode(LED_BUILTIN, OUTPUT);
Serial.begin(230400);
}

void loop() {
if (Serial.available() > 0)
{
  Letter = Serial.read();
  Serial.println(Letter);
  if (Letter == 72)
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
  else if (Letter == 78)
  {
    digitalWrite(LED_BUILTIN, HIGH); 
  }
}
}