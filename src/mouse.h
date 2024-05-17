#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "maze.h"

// Mouse constants
#define CELL_LENGTH 18.0
#define MOUSE_LENGTH 11.0
#define FORWARD_DIST_OFFSET 0.0 // To calibrate if ultrasonic is not precise
#define TURNING_DIST_OFFSET 0.0 // To calibrate if ultrasonic is not precise
#define TURNING_DELAY 10        // Delay before checking for turning completeness
#define DELTA_TURN_COMPLETE 0.1 // Delta b/w ultrasonic sensors for complete turn
#define MOVEMENT_TIMEOUT 5000   // Delay in ms to avoid infinite movement/turnings bcz of sensor errors

void move(void);

bool right_turn_completed(float front_dist_prev, float right_dist_prev);

bool left_turn_completed(float front_dist_prev, float left_dist_prev);

void turn_right(void);

void turn_left(void);

void turn_to_face(ABSOLUTE_DIRECTION new_direction);

void search_to(CELL target);

void run_to(CELL target);

#endif
