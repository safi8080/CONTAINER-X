
#include "DHT.h"
#define DHTTYPE DHT11
#define dht_dpin D1

DHT dht(dht_dpin, DHTTYPE);

void setup()

{
dht.begin();
Serial.begin(9600);
delay(10);
Serial.println("initializing ESP8266...");
}

void loop()
{
 
delay(3000);
float t=dht.readTemperature();
float s=15;

if (t>s)
{
Serial.print(" temprature is ");
Serial.print(t);
Serial.print(" C ");
Serial.print(" which is greater than ");
Serial.println(s);
}
else if (t=s)
{
Serial.print(" temprature is ");
Serial.print(t);
Serial.print(" C ");
Serial.print(" which is equal to ");
Serial.println(s);
}

else
{
Serial.print(" temprature is ");
Serial.print(t);
Serial.print(" C ");
Serial.print(" which is less than ");
Serial.println(s); 
}
}