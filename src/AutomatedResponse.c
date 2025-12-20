#include <Arduino.h>

#define LEFT_MOTOR_PIN 4
#define RIGHT_MOTOR_PIN 2
#define EEP_PIN 15 

/* ULT Defines for PWM */
#define PWN_PIN 2
#define CHN     0
#define FRQ     1000
#define PWM_BIT   8

void automated_setup(void) {

    /* init pins */
    ledcAttachChannal(PWN_PIN, FRQ, PWM_BIT, CHN);
    pinMode(EEP_PIN, OUTPUT);
    pinMode(RIGHT_MOTOR_PIN, OUTPUT);
    pinMode(LEFT_MOTOR_PIN, OUTPUT); 

    /* Set init values */
    digitalWrite(EEP_PIN,LOW);
}

void motor_driver_PWM(void) {
    for (int i = 0; i < 255; i++) { //make light fade in
        ledcWrite(PWN_PIN, i);
        delay(10); 
    }
    for (int i = 255; i > -1; i--) { 
        delay(10);
    } 
}


