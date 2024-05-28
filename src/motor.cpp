#include <Arduino.h>

#include "SparkFun_TB6612.h"
#include "config.h"
#include "motor.h"

#if TB6612FNG_ENABLE

// Initializing motors.  The library will allow you to initialize as many
// motors as you have memory for.  If you are using functions like forward
// that take 2 motors as arguements you can either write new functions or
// call the function more than once.
Motor RIGHT_MOTOR = Motor(RIGHT_MOTOR_PIN1, RIGHT_MOTOR_PIN2, RIGHT_MOTOR_PWM, RIGHT_MOTOR_OFFSET, MOTOR_STANDBY);
Motor LEFT_MOTOR = Motor(LEFT_MOTOR_PIN1, LEFT_MOTOR_PIN2, LEFT_MOTOR_PWM, LEFT_MOTOR_OFFSET, MOTOR_STANDBY);

void init_motors(void) {
    stop_motors();
}

void stop_motors(void) {
    brake(RIGHT_MOTOR, LEFT_MOTOR);
}

void forward_motors(int speed) {
    forward(RIGHT_MOTOR, LEFT_MOTOR, speed);
}

void backward_motors(int speed) {
    back(RIGHT_MOTOR, LEFT_MOTOR, -speed);
}

void right_motors(int speed) {
    right(RIGHT_MOTOR, LEFT_MOTOR, speed);
}

void left_motors(int speed) {
    left(RIGHT_MOTOR, LEFT_MOTOR, speed);
}

void shortbrake_motors(void) {
    stop_motors();
}

void test_motors(int speed) {
    // Use of the drive function which takes as arguements the speed
    // and optional duration.  A negative speed will cause it to go
    // backwards.  Speed can be from -255 to 255.  Also use of the
    // brake function which takes no arguements.
    RIGHT_MOTOR.drive(255, 1000);
    RIGHT_MOTOR.drive(-255, 1000);
    RIGHT_MOTOR.brake();
    delay(1000);

    // Use of the drive function which takes as arguements the speed
    // and optional duration.  A negative speed will cause it to go
    // backwards.  Speed can be from -255 to 255.  Also use of the
    // brake function which takes no arguements.
    LEFT_MOTOR.drive(255, 1000);
    LEFT_MOTOR.drive(-255, 1000);
    LEFT_MOTOR.brake();
    delay(1000);

    // Use of the forward function, which takes as arguements two motors
    // and optionally a speed.  If a negative number is used for speed
    // it will go backwards
    forward(RIGHT_MOTOR, LEFT_MOTOR, 150);
    delay(1000);

    // Use of the back function, which takes as arguments two motors
    // and optionally a speed.  Either a positive number or a negative
    // number for speed will cause it to go backwards
    back(RIGHT_MOTOR, LEFT_MOTOR, -150);
    delay(1000);

    // Use of the brake function which takes as arguments two motors.
    // Note that functions do not stop motors on their own.
    brake(RIGHT_MOTOR, LEFT_MOTOR);
    delay(1000);

    // Use of the left and right functions which take as arguements two
    // motors and a speed.  This function turns both motors to move in
    // the appropriate direction.  For turning a single motor use drive.
    left(RIGHT_MOTOR, LEFT_MOTOR, 100);
    delay(1000);
    right(RIGHT_MOTOR, LEFT_MOTOR, 100);
    delay(1000);

    // Use of brake again.
    brake(RIGHT_MOTOR, LEFT_MOTOR);
    delay(1000);
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

#endif
