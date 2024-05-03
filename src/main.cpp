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
}

void loop() {
    Serial.println("RUNNING IR SENSORS");
    IRInfo front_ir = get_ir_sensor_values(FRONT_IR_PIN);
    IRInfo right_ir = get_ir_sensor_values(RIGHT_IR_PIN);
    IRInfo left_ir = get_ir_sensor_values(LEFT_IR_PIN);

    Serial.println(front_ir.adc_value);
    Serial.println(front_ir.distance);
    Serial.println(right_ir.adc_value);
    Serial.println(right_ir.distance);
    Serial.println(left_ir.adc_value);
    Serial.println(left_ir.distance);
    Serial.println("STOPPING IR SENSORS");

    delay(1000);
    Serial.println("RUNNING MOTORS");
    test_right_motors();
    test_left_motors();
    Serial.println("STOPPING MOTORS");

    delay(100);
}
