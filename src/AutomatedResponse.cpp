#include <Arduino.h>

#define LEFT_MOTOR_PIN 4
#define RIGHT_MOTOR_PIN 2
#define EEP_PIN 15 

/* ULT Defines for PWM */
#define PWM_PIN 33
#define CHN     0
#define FRQ     1000
#define PWM_BIT   8

void automated_setup(void) {

    /* init pins */
    ledcSetup(CHN, FRQ, PWM_BIT);
    ledcAttachPin(PWM_PIN, CHN);
    pinMode(EEP_PIN, OUTPUT);
    pinMode(RIGHT_MOTOR_PIN, OUTPUT);
    pinMode(LEFT_MOTOR_PIN, OUTPUT);

    /* Set init values */
    digitalWrite(EEP_PIN,HIGH);
    digitalWrite(LEFT_MOTOR_PIN,HIGH);
    digitalWrite(RIGHT_MOTOR_PIN,LOW);
}

void motor_driver_PWM(void) {
    ledcWrite(0, 255);
    return;
    for (int i = 0; i < 255; i++) { //make light fade in
        ledcWrite(0, i);
        delay(10); 
    }
    for (int i = 255; i > -1; i--) { 
        ledcWrite(0, i);
        delay(10);
    } 
}


