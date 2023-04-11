#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

const char* ssid = "MIWIFI_s3uY";
const char* password = "7GYQbNnM";

const char* host = "dweet.io";
const char* thingName = "container";

WiFiClient client;

const int httpPort = 80;

void setup() {
  Serial.begin(115200);
  delay(10);

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
  delay(5000);

  // Connect to dweet.io
  Serial.print("Connecting to ");
  Serial.println(host);

  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }

  // Read temperature from the DS18B20 sensor
  float temperature = readTemperature();

  // Print temperature to the serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("C");

  // Create the URL to send the temperature reading to dweet.io
  String url = "/dweet/for/" + String(thingName) + "?temperature=" + String(temperature);

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

// Read temperature from the DS18B20 sensor
float readTemperature() {
  // Data wire is connected to the Arduino digital pin D1
  #define ONE_WIRE_BUS D1

  // Setup a oneWire instance to communicate with any OneWire devices
  OneWire oneWire(ONE_WIRE_BUS);

  // Pass oneWire reference to DallasTemperature library
  DallasTemperature sensors(&oneWire);

  // Start up the library
  sensors.begin();

  // Call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  sensors.requestTemperatures();

  // Read temperature from the DS18B20 sensor
  float temperature = sensors.getTempCByIndex(0);

  return temperature;
}
