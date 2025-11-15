#include <Arduino.h>

#define PIN_LED 2   // Built-in LED is on GPIO2

void setup() {
  pinMode(PIN_LED, OUTPUT);     // Set LED pin as output
}

void loop() {
  digitalWrite(PIN_LED, HIGH);  // LED OFF on WROVER (active-low)
  delay(1000);                  // wait 1 second

  digitalWrite(PIN_LED, LOW);   // LED ON
  delay(1000);                  // wait 1 second
}