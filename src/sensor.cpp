#include <Arduino.h>

#include "sensor.h"
#include <stdio.h>

void init_ultrasonic(int us_trig_pin, int us_echo_pin) {
    pinMode(us_trig_pin, OUTPUT);
    pinMode(us_echo_pin, INPUT);
}

// ref: https://github.com/gamegine/HCSR04-ultrasonic-sensor-lib
float get_ultrasonic_dist(int us_trig_pin, int us_echo_pin) {
    digitalWrite(us_trig_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(us_trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(us_trig_pin, LOW);
    noInterrupts();
    float dist = pulseIn(us_echo_pin, HIGH, 23529.4); // max sensor dist ~4m
    interrupts();

    return dist / 58.0;
}

bool is_wall_present(int us_trig_pin, int us_echo_pin, float threshold) {
    float dist = get_ultrasonic_dist(us_trig_pin, us_echo_pin);

    return (dist < threshold);
}

// -------------------TEST / USAGE ------------------------- //
