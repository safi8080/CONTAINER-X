#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

const uint16_t RECV_PIN = D1; //  the KY-002 receiver is connected to pin D1

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(230400);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.print("Data Received: 0x");
    Serial.print(results.value, HEX);
    Serial.print(" (");
    Serial.print(results.bits, DEC);
    Serial.println(" bits)");
    irrecv.resume(); // Receive the next signal
  }
  delay(100);
}
