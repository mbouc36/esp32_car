#include <BTConnect.h>
#include <Arduino.h>
#include <AutomatedResponse.h>

#define PIN_LED    2
#define PIN_BUTTON 13


void setup() {
  BL_Rx_Setup();
  automated_setup();

}

void loop() {
}