#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

// Ultrasonic pins
const int FRONT_US_TRIG = 14;
const int FRONT_US_ECHO = 15;
const int RIGHT_US_TRIG = 16;
const int RIGHT_US_ECHO = 17;
const int LEFT_US_TRIG = 18;
const int LEFT_US_ECHO = 19;

void init_ultrasonic(int us_trig_pin, int us_echo_pin);

float get_ultrasonic_dist(int us_trig_pin, int us_echo_pin);

bool is_wall_present(int us_trig_pin, int us_echo_pin, float threshold);

#endif
