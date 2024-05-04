#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

// Power coefficients and Pins for Sharp IR sensor (GP2Y0A21YK0F)
#define FRONT_IR_PIN A0
#define RIGHT_IR_PIN A1
#define LEFT_IR_PIN A2
#define VCC 5000 // mv
#define POWER_COEFF_C 29.988
#define POWER_COEFF_P -1.173

// Ultrasonic pins
const int FRONT_US_TRIG = 5;
const int FRONT_US_ECHO = 6;
const int RIGHT_US_TRIG = 11;
const int RIGHT_US_ECHO = 12;
const int LEFT_US_TRIG = 19;
const int LEFT_US_ECHO = 18;

typedef struct {
    uint16_t adc_value;
    uint8_t distance;
} IRInfo;

IRInfo get_ir_sensor_values(uint8_t pin);

void init_ultrasonic(int us_trig_pin, int us_echo_pin);

float get_ultrasonic_dist(int us_trig_pin, int us_echo_pin);

bool is_wall_present(uint8_t pin, uint8_t threshold);

#endif
