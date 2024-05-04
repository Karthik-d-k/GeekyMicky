#include <Arduino.h>

#include "motor.h"

MOTOR RIGHT_MOTOR;
MOTOR LEFT_MOTOR;

void motor_init(MOTOR* motor_ptr, int pin_A, int pin_B) {
    pinMode(pin_A, OUTPUT);
    pinMode(pin_B, OUTPUT);
    motor_ptr->pin_A = pin_A;
    motor_ptr->pin_B = pin_B;
    motor_ptr->speed = 0;
}

void motor_set_forward(MOTOR* motor_ptr, int speed) {
    analogWrite(motor_ptr->pin_A, speed);
    analogWrite(motor_ptr->pin_B, 0);
    motor_ptr->speed = speed;
}

void motor_set_backward(MOTOR* motor_ptr, int speed) {
    analogWrite(motor_ptr->pin_A, 0);
    analogWrite(motor_ptr->pin_B, speed);
    motor_ptr->speed = speed;
}

int motor_get_speed(MOTOR* motor_ptr) {
    return motor_ptr->speed;
}

void init_motors(void) {
    motor_init(&RIGHT_MOTOR, RIGHT_MOTOR_PIN1, RIGHT_MOTOR_PIN2);
    motor_init(&LEFT_MOTOR, LEFT_MOTOR_PIN1, LEFT_MOTOR_PIN2);
}

void test_motors(int speed) {
    motor_set_forward(&RIGHT_MOTOR, speed);
    motor_set_forward(&LEFT_MOTOR, speed);
    delay(2000);
    motor_set_backward(&RIGHT_MOTOR, speed);
    motor_set_backward(&LEFT_MOTOR, speed);
    delay(2000);
}
