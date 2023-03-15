#include <Wire.h>
#include <DS3231.h>

DS3231 RTCclock;
RTCDateTime dt;

void setup()
{
Serial.begin(230400);
Serial.println("Initializing RTC module..");
RTCclock.begin();
// The following function allos to set
//the time manually (YYYY, MM, DD, HH, II, SS) / clock. setDateTime (2023, 03, 08, 20, 35, 00);
// Set time by using the compilation time
// Note that the following line will be executed with every reset
// (therefore, it will be necessary to upload a second sketch
//with the line commented)
RTCclock.setDateTime(__DATE__, __TIME__);
}
void loop()
{
dt = RTCclock.getDateTime();

Serial.print("TIME NOW: ");
Serial.print(dt.year); Serial.print("-");
Serial.print(dt.month); Serial.print("-");
Serial.print (dt.day); Serial.print(" ");
Serial.print(dt.hour); Serial.print(":");
Serial.print(dt.minute); Serial.print(":");
Serial.print (dt.second); Serial.println("");
delay (1000);
}