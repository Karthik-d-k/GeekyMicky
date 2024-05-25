#include <Arduino.h>

#include "config.h"
#include "motor.h"

void set_pwm_frequency(void) {
    // Divide by 1. frequency = 31.25 kHz;
    bitClear(TCCR1B, CS11);
    bitSet(TCCR1B, CS10);
}

#if TB6612FNG_ENABLE
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
    //  L   H   H   H    CCW
    fast_write_pin(RIGHT_MOTOR_PIN1, LOW);
    fast_write_pin(RIGHT_MOTOR_PIN2, HIGH);
    fast_write_pin(LEFT_MOTOR_PIN1, LOW);
    fast_write_pin(LEFT_MOTOR_PIN2, HIGH);

    analogWrite(RIGHT_MOTOR_PWM, speed);
    analogWrite(LEFT_MOTOR_PWM, speed);
}

void right_motors(int speed) {
    // IN1 IN2 PWM STBY
    //  L   H   H   H    CCW (RIGHT)
    // IN1 IN2 PWM STBY
    //  H   L   H   H    CW (LEFT)
    fast_write_pin(RIGHT_MOTOR_PIN1, LOW);
    fast_write_pin(RIGHT_MOTOR_PIN2, HIGH);
    fast_write_pin(LEFT_MOTOR_PIN1, HIGH);
    fast_write_pin(LEFT_MOTOR_PIN2, LOW);

    analogWrite(RIGHT_MOTOR_PWM, speed);
    analogWrite(LEFT_MOTOR_PWM, speed);
}

void left_motors(int speed) {
    // IN1 IN2 PWM STBY
    //  H   L   H   H    CW (RIGHT)
    // IN1 IN2 PWM STBY
    //  L   H   H   H    CCW (LEFT)
    fast_write_pin(RIGHT_MOTOR_PIN1, HIGH);
    fast_write_pin(RIGHT_MOTOR_PIN2, LOW);
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

#elif L9110_ENABLE
void init_motors(void) {
    set_pwm_frequency();
    pinMode(RIGHT_MOTOR_PIN1, OUTPUT);
    pinMode(LEFT_MOTOR_PIN1, OUTPUT);
    pinMode(RIGHT_MOTOR_PIN2, OUTPUT);
    pinMode(LEFT_MOTOR_PIN2, OUTPUT);
    stop_motors();
}

void stop_motors(void) {
    // IN1 IN2 OU1 OU2
    //  L   L   L   L    STOP
    fast_write_pin(RIGHT_MOTOR_PIN1, LOW);
    fast_write_pin(RIGHT_MOTOR_PIN2, LOW);
    fast_write_pin(LEFT_MOTOR_PIN1, LOW);
    fast_write_pin(LEFT_MOTOR_PIN2, LOW);
}

void forward_motors(int speed) {
    // IN1 IN2 OU1 OU2
    //  H   L   H   L    CW
    analogWrite(RIGHT_MOTOR_PIN1, speed);
    fast_write_pin(RIGHT_MOTOR_PIN2, LOW);
    analogWrite(LEFT_MOTOR_PIN1, speed);
    fast_write_pin(LEFT_MOTOR_PIN2, LOW);
}

void backward_motors(int speed) {
    // IN1 IN2 OU1 OU2
    //  L   H   L   H    CCW
    fast_write_pin(RIGHT_MOTOR_PIN1, LOW);
    analogWrite(RIGHT_MOTOR_PIN2, speed);
    fast_write_pin(LEFT_MOTOR_PIN1, LOW);
    analogWrite(LEFT_MOTOR_PIN2, speed);
}

void right_motors(int speed) {
    // IN1 IN2 OU1 OU2
    //  L   H   L   H    CCW (RIGHT)
    // IN1 IN2 OU1 OU2
    //  H   L   H   L    CW (LEFT)
    fast_write_pin(RIGHT_MOTOR_PIN1, LOW);
    analogWrite(RIGHT_MOTOR_PIN2, speed);
    analogWrite(LEFT_MOTOR_PIN1, speed);
    fast_write_pin(LEFT_MOTOR_PIN2, LOW);
}

void left_motors(int speed) {
    // IN1 IN2 OU1 OU2
    //  H   L   H   L    CW (RIGHT)
    // IN1 IN2 OU1 OU2
    //  L   H   L   H    CCW (LEFT)
    analogWrite(RIGHT_MOTOR_PIN1, speed);
    fast_write_pin(RIGHT_MOTOR_PIN2, LOW);
    fast_write_pin(LEFT_MOTOR_PIN1, LOW);
    analogWrite(LEFT_MOTOR_PIN2, speed);
}

void shortbrake_motors(void) {
    // short brake is not available in L9110, use stop instead
    // IN1 IN2 OU1 OU2
    //  L   L   L   L    STOP
    fast_write_pin(RIGHT_MOTOR_PIN1, LOW);
    fast_write_pin(RIGHT_MOTOR_PIN2, LOW);
    fast_write_pin(LEFT_MOTOR_PIN1, LOW);
    fast_write_pin(LEFT_MOTOR_PIN2, LOW);
}

#endif

void test_motors(int speed) {
    forward_motors(speed);
    delay(5000);
    backward_motors(speed);
    delay(5000);
    shortbrake_motors();
    forward_motors(speed);
    delay(5000);
    stop_motors();
    right_motors(speed);
    delay(5000);
    left_motors(speed);
    delay(5000);
    stop_motors();
}
