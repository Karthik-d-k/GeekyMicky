#include <Arduino.h>

#include "config.h"
#include "floodfill.h"
#include "maze.h"
#include "motor.h"
#include "queue.h"
#include "sensor.h"

void setup() {
    Serial.begin(BAUDRATE);
    Serial.println("GeekyMicky");

    init_motors();
    init_ultrasonic(FRONT_US_TRIG, FRONT_US_ECHO);
}

void loop() {
    delay(1000);
    Serial.println("RUNNING MOTORS");
    test_motors(255);
    Serial.println("STOPPING MOTORS");

    delay(1000);
    Serial.println("RUNNING US SENSORS");
    float dist = get_ultrasonic_dist(FRONT_US_TRIG, FRONT_US_ECHO);
    Serial.println(dist);
    delay(60); // we suggest to use over 60ms measurement cycle, in order to prevent trigger signal to the echo signal.
    Serial.println("STOPPING US SENSORS");
}
