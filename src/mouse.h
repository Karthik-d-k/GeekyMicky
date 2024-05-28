#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "config.h"
#include "maze.h"

void move(void);

bool right_turn_completed(float front_dist_prev, float right_dist_prev);

bool left_turn_completed(float front_dist_prev, float left_dist_prev);

void turn_right(void);

void turn_left(void);

void turn_to_face(ABSOLUTE_DIRECTION new_direction);

void search_to(CELL target);

void run_to(CELL target);

#endif
