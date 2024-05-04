#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>

// ref: https://github.com/tylersweat/arduino-L293D

// Motor pins (PWM pins are denoted by `~` sign on pinout diagram)
// Analog pins are referred w/ `Ax` but digital pins are referred w/ numbers
const uint8_t RIGHT_MOTOR_PIN1 = 7;
const uint8_t RIGHT_MOTOR_PIN2 = 8;
const uint8_t RIGHT_MOTOR_PWM_PIN = 9;

const uint8_t LEFT_MOTOR_PIN1 = 2;
const uint8_t LEFT_MOTOR_PIN2 = 4;
const uint8_t LEFT_MOTOR_PWM_PIN = 3;

typedef struct {
    int pin_E;
    int pin_A;
    int pin_B;
    int speed;
} L293D;

type struct
{
    float speedX;
    float speedY;
    float speedZ;
    float rotSpeed;
} MPU6050_Gyr;

extern MPU6050_Gyr GYROSCOPE_OUT;

void L293D_init(L293D *l293d_ptr, int pin_E, int pin_A, int pin_B);

void L293D_set(L293D* l293d_ptr, double speed);

void L293D_set_int(L293D* l293d_ptr, int speed);

int L293D_get(L293D* l293d_ptr);

void init_motors(void);

void test_right_motors(void);

void test_left_motors(void);

#endif
