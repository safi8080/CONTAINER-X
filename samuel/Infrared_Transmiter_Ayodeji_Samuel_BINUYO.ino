#include <IRremoteESP8266.h>
#include <IRsend.h>

IRsend irsend(D1); // the KY-005 Transmiter is connected to pin D1

void setup() {
  Serial.begin(230400);
}

void loop() {
  uint16_t data = 0x2FD48B; // Data to be transmitted
  irsend.sendNEC(data, 32);
  Serial.println("Signal sent!");
  delay(1000); // Wait 1 second before sending another signal
}
