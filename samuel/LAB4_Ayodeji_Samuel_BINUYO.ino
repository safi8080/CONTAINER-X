#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// Replace with your network credentials
const char* ssid = "vivo 1820";
const char* password = "12345678";

// Create an instance of the WiFiClient object
WiFiClient client;

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Connect to the server (postman-echo.com)
  if (client.connect("postman-echo.com", 80)) {
    Serial.println("Connected to server");
    // Send a GET request
    client.println("GET /get HTTP/1.1");
    client.println("Host: postman-echo.com");
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("Connection failed");
  }
}

void loop() {
  // Read the response from the server and print it to the Serial Monitor
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  // Check if the connection to the server is closed
  if (!client.connected()) {
    Serial.println();
    Serial.println("Connection closed");
    delay(10000);
    // Reconnect to the server
    if (client.connect("postman-echo.com", 80)) {
      Serial.println("Connected to server");
      // Send a GET request
      client.println("GET /get HTTP/1.1");
      client.println("Host: postman-echo.com");
      client.println("Connection: close");
      client.println();
    } else {
      Serial.println("Connection failed");
    }
  }
}
