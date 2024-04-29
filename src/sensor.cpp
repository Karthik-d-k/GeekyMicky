#include <Arduino.h>

#include "sensor.h"
#include <stdio.h>

IRInfo get_ir_sensor_values(uint8_t pin) {
    // Read analog value from sensor
    uint16_t adc_value = analogRead(pin);

    // Constrain sensor values to remain within set min-max range
    adc_value = constrain(adc_value, 0, 1023);

    // Calculate distance from power fit function
    uint8_t distance = (uint8_t)(POWER_COEFF_C * pow(adc_value, POWER_COEFF_P));

    IRInfo ir_info = {adc_value, distance};
    return ir_info;
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
