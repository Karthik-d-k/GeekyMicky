#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

#define TB6612FNG_ENABLE false
#define L9110_ENABLE !TB6612FNG_ENABLE

// Motor pins (PWM pins are denoted by `~` sign on pinout diagram)
// Analog pins are referred w/ `Ax` but digital pins are referred w/ numbers

#if TB6612FNG_ENABLE
const uint8_t RIGHT_MOTOR_PIN1 = 2;
const uint8_t RIGHT_MOTOR_PIN2 = 3;
const uint8_t RIGHT_MOTOR_PWM = 10;

const uint8_t LEFT_MOTOR_PIN1 = 4;
const uint8_t LEFT_MOTOR_PIN2 = 5;
const uint8_t LEFT_MOTOR_PWM = 11;

const uint8_t MOTOR_STANDBY = 7;
#elif L9110_ENABLE
const uint8_t RIGHT_MOTOR_PIN1 = 3;
const uint8_t RIGHT_MOTOR_PIN2 = 10;

const uint8_t LEFT_MOTOR_PIN1 = 5;
const uint8_t LEFT_MOTOR_PIN2 = 11;
#endif

const int FORWARD_MOTOR_SPEED = 100;
const int TURNING_MOTOR_SPEED = 100;

void set_pwm_frequency(void);

void init_motors(void);

void stop_motors(void);

void forward_motors(int speed);

void backward_motors(int speed);

void right_motors(int speed);

void left_motors(int speed);

void shortbrake_motors(void);

void test_motors(int speed);

#endif
