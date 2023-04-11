#include<Wire.h>
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

const int MPU=0x68;
int AcX,AcY,AcZ,GyX,GyY,GyZ,AcX2,AcY2,AcZ2,GyX2,GyY2,GyZ2;
int minVal=0;
int maxVal=65536;
int xinitial=-8;
int yinitial=0;
int zinitial=105;
int roll=0;
int pitch=0;
int yaw=0;

void setup() {
  Serial.begin(230400);
  delay(10);

  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0); 
  Wire.endTransmission(true); 

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

  int imu = roll;  
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);

  Wire.requestFrom(MPU,14,true);  
 
  GyX=Wire.read()<<8|Wire.read();    
  GyY=Wire.read()<<8|Wire.read();  
  GyZ=Wire.read()<<8|Wire.read(); 
  int xAng = map(GyX,minVal,maxVal,180,-180);
  int yAng = map(GyY,minVal,maxVal,180,-180);
  int zAng = map(GyZ,minVal,maxVal,180,-180); 
  
  delay(1000);

  GyX2=Wire.read()<<8|Wire.read();  
  GyY2=Wire.read()<<8|Wire.read();  
  GyZ2=Wire.read()<<8|Wire.read();  
  int xAng2 = map(GyX2,minVal,maxVal,180,-180);
  int yAng2 = map(GyY2,minVal,maxVal,180,-180);
  int zAng2 = map(GyZ2,minVal,maxVal,180,-180); 
  roll=xinitial-(abs(xAng2)-abs(xAng));                                      
  pitch=yinitial-(abs(yAng2)-abs(yAng));
  yaw=zinitial-(abs(zAng2)-abs(zAng));

  // Create the URL to send the temperature reading to dweet.io
  String url = "/dweet/for/" + String(thingName) + "?roll=" + String(roll) + "&pitch=" + String(pitch) + "&yaw=" + String(yaw);

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