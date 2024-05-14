#include <Arduino.h>

#include "config.h"
#include "motor.h"

MOTOR RIGHT_MOTOR;
MOTOR LEFT_MOTOR;

void set_pwm_frequency(void) {
    // Divide by 1. frequency = 31.25 kHz;
    bitClear(TCCR1B, CS11);
    bitSet(TCCR1B, CS10);
}

void init_motors(void) {
    set_pwm_frequency();
    pinMode(RIGHT_MOTOR_PIN1, OUTPUT);
    pinMode(RIGHT_MOTOR_PIN2, OUTPUT);
    pinMode(LEFT_MOTOR_PIN1, OUTPUT);
    pinMode(LEFT_MOTOR_PIN2, OUTPUT);
    pinMode(RIGHT_MOTOR_PWM, OUTPUT);
    pinMode(LEFT_MOTOR_PWM, OUTPUT);
    pinMode(MOTOR_STANDBY, OUTPUT);

    fast_write_pin(MOTOR_STANDBY, HIGH);
    stop_motors();
}

void stop_motors(void) {
    // IN1 IN2 PWM STBY
    //  L   L   H   H    STOP
    fast_write_pin(RIGHT_MOTOR_PIN1, LOW);
    fast_write_pin(RIGHT_MOTOR_PIN2, LOW);
    fast_write_pin(LEFT_MOTOR_PIN1, LOW);
    fast_write_pin(LEFT_MOTOR_PIN2, LOW);

    fast_write_pin(RIGHT_MOTOR_PWM, HIGH);
    fast_write_pin(LEFT_MOTOR_PWM, HIGH);
}

void forward_motors(int speed) {
    // IN1 IN2 PWM STBY
    //  H   L   H   H    CW
    fast_write_pin(RIGHT_MOTOR_PIN1, HIGH);
    fast_write_pin(RIGHT_MOTOR_PIN2, LOW);
    fast_write_pin(LEFT_MOTOR_PIN1, HIGH);
    fast_write_pin(LEFT_MOTOR_PIN2, LOW);

    analogWrite(RIGHT_MOTOR_PWM, speed);
    analogWrite(LEFT_MOTOR_PWM, speed);
}

void backward_motors(int speed) {
    // IN1 IN2 PWM STBY
    //  L   H   H   H    STOP
    fast_write_pin(RIGHT_MOTOR_PIN1, LOW);
    fast_write_pin(RIGHT_MOTOR_PIN2, HIGH);
    fast_write_pin(LEFT_MOTOR_PIN1, LOW);
    fast_write_pin(LEFT_MOTOR_PIN2, HIGH);

    analogWrite(RIGHT_MOTOR_PWM, speed);
    analogWrite(LEFT_MOTOR_PWM, speed);
}

void shortbrake_motors(void) {
    // IN1 IN2 PWM STBY
    //  H   L   L   H    STOP
    fast_write_pin(RIGHT_MOTOR_PIN1, HIGH);
    fast_write_pin(RIGHT_MOTOR_PIN2, LOW);
    fast_write_pin(LEFT_MOTOR_PIN1, HIGH);
    fast_write_pin(LEFT_MOTOR_PIN2, LOW);

    fast_write_pin(RIGHT_MOTOR_PWM, LOW);
    fast_write_pin(LEFT_MOTOR_PWM, LOW);
}

void test_motors(int speed) {
    forward_motors(speed);
    delay(5000);
    backward_motors(speed);
    delay(5000);
    shortbrake_motors();
    forward_motors(speed);
    delay(5000);
    stop_motors();
}
