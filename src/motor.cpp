#include <Arduino.h>

#include "motor.h"

void init_motors(void) {
    // Initialize the motor pin as an output
    pinMode(RIGHT_MOTOR_PWM_PIN, OUTPUT);
    pinMode(LEFT_MOTOR_PWM_PIN, OUTPUT);
    // Set the initial motor speed to 0 (stopped)
    analogWrite(RIGHT_MOTOR_PWM_PIN, 0);
    analogWrite(LEFT_MOTOR_PWM_PIN, 0);
}

void test_motors(uint8_t motor_pin) {
    // Increase motor speed from 0 to maximum gradually
    for (int speed = 0; speed <= 255; speed++) {
        analogWrite(motor_pin, speed); // Set the motor speed
        delay(10);                     // Delay for smoother speed increase
    }

    delay(1000); // Pause for 1 second at maximum speed

    // Decrease motor speed from maximum to 0 gradually
    for (int speed = 255; speed >= 0; speed--) {
        analogWrite(motor_pin, speed); // Set the motor speed
        delay(10);                     // Delay for smoother speed decrease
    }

    delay(1000); // Pause for 1 second at minimum speed
}
