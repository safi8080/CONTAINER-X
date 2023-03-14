#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is connected to the Arduino digital pin D1
#define ONE_WIRE_BUS D1

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

void setup() {
  // Start serial communication
  Serial.begin(230400);

  // Start up the library
  sensors.begin();
}

void loop() {  
  // Call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  sensors.requestTemperatures();

  // Read temperature from the DS18B20 sensor
  float temperature = sensors.getTempCByIndex(0);

  // Print temperature to the serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("C");

  // Check if temperature is above or below 20°C
  if (temperature > 22.60) {
    Serial.println("Temperature above 22.60 Degree Celcius");
  } else {
    Serial.println("Temperature below 22.60 Degree Celcius");
  }

  // Wait for a moment before taking another reading
  delay(5000);
}
