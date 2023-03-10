//This programme On and Off the LED light with the characters S or s and L or l

// Define the pin number for the LED
const int ledPin = LED_BUILTIN;

void setup() {  
  // Initialize the Serial Monitor
  Serial.begin(230400);

  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Check for incoming Serial data
    if (Serial.available() > 0) {
    // Read the incoming data
    char data = Serial.read();

    // If the data is 'S' or 's', turn the LED on
      if (data == 'S' || data == 's') {
      digitalWrite(ledPin, HIGH);
      Serial.println("LED ON");
    }

    // If the data is 'L' or 'l', turn the LED off
      if (data == 'L' || data == 'l') {
      digitalWrite(ledPin, LOW);
      Serial.println("LED OFF");
    }
  }
}
