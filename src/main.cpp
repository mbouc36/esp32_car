#include <BTConnect.h>
#include <Arduino.h>
#include <AutomatedResponse.h>


void setup() {
  //BL_Rx_Setup();
  automated_setup();
  

}

void loop() {
  motor_driver_PWM();
}