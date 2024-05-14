#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

// Motor pins (PWM pins are denoted by `~` sign on pinout diagram)
// Analog pins are referred w/ `Ax` but digital pins are referred w/ numbers
const uint8_t RIGHT_MOTOR_PIN1 = 2;
const uint8_t RIGHT_MOTOR_PIN2 = 3;
const uint8_t RIGHT_MOTOR_PWM = 10;

const uint8_t LEFT_MOTOR_PIN1 = 4;
const uint8_t LEFT_MOTOR_PIN2 = 5;
const uint8_t LEFT_MOTOR_PWM = 11;

const uint8_t MOTOR_STANDBY = 7;

typedef struct {
    int pin_A;
    int pin_B;
    int speed;
} MOTOR;

void set_pwm_frequency(void);

void init_motors(void);

void stop_motors(void);

void forward_motors(int speed);

void backward_motors(int speed);

void shortbrake_motors(void);

void test_motors(int speed);

#endif
