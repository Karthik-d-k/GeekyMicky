#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

// Ultrasonic pins
const uint8_t FRONT_US_TRIG = 14;
const uint8_t FRONT_US_ECHO = 15;
const uint8_t RIGHT_US_TRIG = 16;
const uint8_t RIGHT_US_ECHO = 17;
const uint8_t LEFT_US_TRIG = 18;
const uint8_t LEFT_US_ECHO = 19;

void init_ultrasonic(void);

float get_ultrasonic_dist(int us_trig_pin, int us_echo_pin);

bool is_wall_present(int us_trig_pin, int us_echo_pin, float threshold);

#endif
