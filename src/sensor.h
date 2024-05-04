#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

// Ultrasonic pins
const int FRONT_US_TRIG = 5;
const int FRONT_US_ECHO = 6;
const int RIGHT_US_TRIG = 11;
const int RIGHT_US_ECHO = 12;
const int LEFT_US_TRIG = 19;
const int LEFT_US_ECHO = 18;

void init_ultrasonic(int us_trig_pin, int us_echo_pin);

float get_ultrasonic_dist(int us_trig_pin, int us_echo_pin);

bool is_wall_present(int us_trig_pin, int us_echo_pin, float threshold);

#endif
