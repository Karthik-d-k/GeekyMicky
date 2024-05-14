#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "maze.h"

// Mouse constants
#define CELL_LENGTH 18.0
#define MOUSE_LENGTH 11.0
#define FRONT_DIST_OFFSET 1.0 // To calibrate if ultrasonic is not precise

void move(void);

void turn_to_face(ABSOLUTE_DIRECTION new_direction);

void search_to(CELL target);

void run_to(CELL target);

#endif
