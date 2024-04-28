#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

// Power coefficients and Pins for Sharp IR sensor (GP2Y0A21YK0F)
#define FRONT_IR_PIN A0
#define RIGHT_IR_PIN A1
#define LEFT_IR_PIN A2
#define POWER_COEFF_C 116483.399834958
#define POWER_COEFF_P -1.132373887917551

typedef struct {
    uint16_t adc_value;
    uint8_t distance;
}IRInfo;

// ref: https://github.com/DrGFreeman/SharpDistSensor
IRInfo get_ir_sensor_values(uint8_t pin);

bool is_wall_present(uint8_t pin, uint8_t threshold);

#endif
