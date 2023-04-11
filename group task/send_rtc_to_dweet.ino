#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <DS3231.h>

const char* ssid = "quepasatio";
const char* password = "mayco123";

const char* host = "dweet.io";
const char* thingName = "container";

WiFiClient client;

DS3231 RTCclock;
RTCDateTime dt;

const int httpPort = 80;

int delayTime=200;

void setup() {
  Serial.begin(230400);
  delay(10);

  RTCclock.begin();
  RTCclock.setDateTime(__DATE__, __TIME__);

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
  
  dt = RTCclock.getDateTime();


//Serial.print(dt.year); Serial.print("-");
//Serial.print(dt.month); Serial.print("-");
//Serial.print (dt.day); Serial.print(" ");
//Serial.print(dt.hour); Serial.print(":");
//Serial.print(dt.minute); Serial.print(":");
//Serial.print (dt.second); Serial.println("");
//delay (1000);

 // Create the URL to send the temperature reading to dweet.io
  String url = "/dweet/for/" + String(thingName) + "?date=" + String(dt.year) + String("/") + String(dt.month) + String("/") + String(dt.day) + "&time=" + String(dt.hour) + String(":") + String(dt.minute) + String(":") + String(dt.second);

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