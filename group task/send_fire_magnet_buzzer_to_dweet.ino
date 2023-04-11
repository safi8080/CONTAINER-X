#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

//const char* ssid = "MIWIFI_s3uY";
//const char* password = "7GYQbNnM";

const char* ssid = "quepasatio";
const char* password = "mayco123";

const char* host = "dweet.io";
const char* thingName = "container";

WiFiClient client;

const int httpPort = 80;

int delayTime=200;

const int buzzerPin = D3; 
const int doorPin = D4;
int firePin = D5;
int door;
int fire;

void setup() {
  Serial.begin(230400);
  delay(10);

  pinMode(doorPin, INPUT);
  pinMode(firePin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(10);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());   
  
}

void loop() {
  // Delay for 5 seconds before taking the next temperature reading
  delay(1000);

  // Connect to dweet.io
  Serial.print("Connecting to ");
  Serial.println(host);

  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }

  door = digitalRead(doorPin);
  fire = digitalRead(firePin);

  if(fire == 0){
    digitalWrite(buzzerPin,LOW); // set the buzzer ON
    //Serial.print(" ");Serial.print("Fire Alarm:OFF");
  }

  else{
    digitalWrite(buzzerPin,HIGH);  // set the buzzer OFF
    //Serial.print(" ");Serial.print("Fire Alarm:ON");


    if(door == 0){
    digitalWrite(buzzerPin,HIGH);  // set the buzzer OFF
    //Serial.print(" ");Serial.print("Door:OPEN");
    
  }

  else{
    digitalWrite(buzzerPin,LOW); // set the buzzer ON
    //Serial.print(" ");Serial.print("Door:CLOSE");
  }
  }
  //Serial.println(" ");
  delay(delayTime);
  
 // Create the URL to send the temperature reading to dweet.io
  String url = "/dweet/for/" + String(thingName) + "?door=" + String(door) + "&fire=" + String(fire);

  // Send the temperature reading to dweet.io
  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");

  // Wait for the server's response
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 1000) {
      Serial.println("Client Timeout !");
      client.stop();
      return;
    }
  }

  // Print the server's response to the serial monitor
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("Closing connection");

}