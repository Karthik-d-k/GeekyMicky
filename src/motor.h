#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

// Motor pins
#define RIGHT_MOTOR_PWM_PIN A6
#define LEFT_MOTOR_PWM_PIN A7

void init_motors(void);
void test_motors(int motor_pin);

#endif
