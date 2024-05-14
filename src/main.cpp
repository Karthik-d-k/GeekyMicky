#include <Arduino.h>

#include "config.h"
#include "floodfill.h"
#include "maze.h"
#include "motor.h"
#include "mouse.h"
#include "queue.h"
#include "sensor.h"
#include "systick.h"

const uint8_t ENABLE_PIN = 2; // Digital pin to enable the control loop
volatile bool robot_enabled = false;

extern CELL CURRENT_CELL;
extern ABSOLUTE_DIRECTION CURRENT_ABSOLUTE_DIRECTION;
extern uint8_t COST[MAZE_SIZE][MAZE_SIZE];
extern WallInfo WALLS[MAZE_SIZE][MAZE_SIZE];

ISR(TIMER2_COMPA_vect, ISR_NOBLOCK) {
    systick_update();
}

void setup() {
    Serial.begin(BAUDRATE);
    Serial.println("GeekyMicky");
    pinMode(ENABLE_PIN, INPUT);

    init_maze();
    init_motors();
    init_ultrasonic();
    /// do not begin systick until the hardware is setup
    systick_begin();
}

void loop() { // Check the state of the control loop enable pin
    if (digitalRead(ENABLE_PIN) == HIGH) {
        robot_enabled = true;
    } else {
        robot_enabled = false;
    }

    // Execute the control loop tasks if enabled
    if (robot_enabled) {
        Serial.println("Running...\n");

        CELL target = END;
        search_to(target);

        Serial.println("SUCCESS !!");
    } else {
        // Put the Arduino in idle mode when the control loop is disabled
    }
}
