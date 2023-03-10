int ledPin=D4;
char mayco;

void setup() {
  Serial.begin(230400);
  Serial.println("'M'-LED ON , 'O'-LED OFF");
  pinMode(ledPin,OUTPUT);
}

void loop() {
  if(Serial.available()){
    char mayco=Serial.read();
   
    if (mayco == 'M' || mayco == 'm'){
      digitalWrite(ledPin,LOW);
      Serial.println("LED ON");
    } 
    
    else if (mayco == 'O' || mayco == 'o'){
      digitalWrite(ledPin,HIGH);
      Serial.println("LED OFF");
    } 

    else {
      Serial.println("invalid input");
    } 
    
  }
}

