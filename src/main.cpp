#include <Arduino.h>

#include "config.h"
#include "floodfill.h"
#include "maze.h"
#include "motor.h"
#include "mouse.h"
#include "queue.h"
#include "sensor.h"
#include "systick.h"

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
    Serial.println("----------");

    init_maze();
    init_motors();
    init_ultrasonic();
    delay(500);
    /// do not begin systick until the hardware is setup
    systick_begin();
}

void loop() {
    Serial.println("Running...\n");

    CELL target = END;
    search_to(target);

    Serial.println("SUCCESS !!");
}
