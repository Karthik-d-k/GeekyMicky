#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

// ref: https://github.com/tylersweat/arduino-MOTOR

// Motor pins (PWM pins are denoted by `~` sign on pinout diagram)
// Analog pins are referred w/ `Ax` but digital pins are referred w/ numbers
const uint8_t RIGHT_MOTOR_PIN1 = 11;
const uint8_t RIGHT_MOTOR_PIN2 = 10;

const uint8_t LEFT_MOTOR_PIN1 = 6;
const uint8_t LEFT_MOTOR_PIN2 = 5;

typedef struct {
    int pin_A;
    int pin_B;
    int speed;
} MOTOR;

void set_pwm_frequency(void);

void motor_init(MOTOR* motor_ptr, int pin_A, int pin_B);

void motor_set_forward(MOTOR* motor_ptr, int speed);

void motor_set_backward(MOTOR* motor_ptr, int speed);

int motor_get_speed(MOTOR* motor_ptr);

void init_motors(void);

void stop_motors(void);

void test_motors(int speed);

#endif
