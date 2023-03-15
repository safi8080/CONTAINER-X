#include <Wire.h>
#include <DS3231.h>
#include "DHT.h"
#define DHTTYPE DHT11
#define dht_dpin D1

DHT dht(dht_dpin, DHTTYPE);
DS3231 RTCclock;
RTCDateTime dt;

void setup() {
Serial.begin(230400);
Serial.println("Initializing RTC module..");
RTCclock.begin();
RTCclock.setDateTime(__DATE__, __TIME__);
dht.begin();
Serial.begin(9600);
delay(10);
Serial.println("Initializing ESP8266...");// put your setup code here, to run once:

}

void loop() {
dt = RTCclock.getDateTime();

float h = dht.readHumidity();
float t = dht.readTemperature();

Serial.print("TIME NOW: ");
Serial.print(dt.year); Serial.print("-");
Serial.print(dt.month); Serial.print("-");
Serial.print (dt.day); Serial.print(" ");
Serial.print(dt.hour); Serial.print(":");
Serial.print(dt.minute); Serial.print(":");
Serial.print (dt.second); Serial.print("");
Serial.print("  ");
Serial.print("Current humidity = ");
Serial.print(h);
Serial.print("%");
Serial.print("  ");
Serial.print("Temperature = ");
Serial.print(t);
Serial.println("C ");
delay (1000); // put your main code here, to run repeatedly:

}
