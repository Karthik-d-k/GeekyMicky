#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

// Motor pins (PWM pins are denoted by `~` sign on pinout diagram)
#define RIGHT_MOTOR_PWM_PIN D11
#define LEFT_MOTOR_PWM_PIN D10

void init_motors(void);
void test_motors(uint8_t motor_pin);

#endif
