#include <Arduino.h>

#include "sensor.h"
#include <stdio.h>

// ref: https://github.com/guillaume-rico/SharpIR
IRInfo get_ir_sensor_values(uint8_t pin) {
    // Read analog value from sensor
    uint16_t adc_value = analogRead(pin);

    // Constrain sensor values to remain within set min-max range
    adc_value = constrain(adc_value, 0, 1023);

    // Calculate distance from power fit function
    uint8_t distance = (uint8_t)(POWER_COEFF_C * pow(map(adc_value, 0, 1023, 0, VCC) / 1000.0, POWER_COEFF_P));

    IRInfo ir_info = {adc_value, distance};
    return ir_info;
}

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

bool is_wall_present(uint8_t pin, uint8_t threshold) {
    IRInfo ir_info = get_ir_sensor_values(pin);

    return (ir_info.distance < threshold);
}

// -------------------TEST / USAGE ------------------------- //
int test_ir_sensors(void) {
    IRInfo front_ir = get_ir_sensor_values(FRONT_IR_PIN);
    IRInfo right_ir = get_ir_sensor_values(RIGHT_IR_PIN);
    IRInfo left_ir = get_ir_sensor_values(LEFT_IR_PIN);

    printf("[FRONT_IR] adc_value: [%d] \t distance : [%d] \n", front_ir.adc_value, front_ir.distance);
    printf("[RIGHT_IR] adc_value: [%d] \t distance : [%d] \n", right_ir.adc_value, right_ir.distance);
    printf("[LEFT_IR ] adc_value: [%d] \t distance : [%d] \n", left_ir.adc_value, left_ir.distance);

    return 0;
}
