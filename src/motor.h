#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

// Motor pins (PWM pins are denoted by `~` sign on pinout diagram)
const uint8_t RIGHT_MOTOR_PWM_PIN = 11;
const uint8_t LEFT_MOTOR_PWM_PIN = 10;

void init_motors(void);
void test_motors(uint8_t motor_pin);

#endif
