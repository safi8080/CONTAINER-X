#include <DHT.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

const char* ssid = "MIWIFI_s3uY";
const char* password = "7GYQbNnM";

const char* host = "dweet.io";
const char* thingName = "container";

WiFiClient client;

const int httpPort = 80;

#define DHTPIN D2          // Pin connected to the DHT11 sensor
#define DHTTYPE DHT11      // DHT11 sensor type

DHT dht(DHTPIN, DHTTYPE);

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

  dht.begin();    // Initialize the DHT11 sensor
}

void loop() {
  // Delay for 5 seconds before taking the next reading
  delay(5000);

  // Connect to dweet.io
  Serial.print("Connecting to ");
  Serial.println(host);

  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }

  // Read temperature and humidity from the DHT11 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Print temperature and humidity to the serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  // Create the URL to send the temperature and humidity data to dweet.io
  String url = "/dweet/for/" + String(thingName) + "?temperature=" + String(temperature) + "&humidity=" + String(humidity);

  // Send the temperature and humidity data to dweet.io
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
