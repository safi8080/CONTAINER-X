//M ERANO Flame module / Magnetic module
//Detects Fire and shows Fire alarm status
//Display Door open and close status

const int flamePin = D0; // connect pin for flame module
const int doorPin = D1; // connect pin for magnetic module
int flame;
int door;

void setup() {
  Serial.begin(230400);
  pinMode(flamePin, INPUT);
  pinMode(doorPin, INPUT);
}

void loop() {
  flame = digitalRead(flamePin);
  door = digitalRead(doorPin);

  if(flame == HIGH){
    Serial.print("FireAlarm:ON"); //detects fire, alarm status ON
  }else{
    Serial.print("FireAlarm:OFF"); //detects no fire, alarm status OFF
  }
  Serial.print(" ");
  
  if(door == HIGH){
    Serial.print("DoorStatus:CLOSE"); //door is closed
  }else{
    Serial.print("DoorStatus:OPEN"); //door is opened
  }
  Serial.println(" ");
  delay(1000);
}