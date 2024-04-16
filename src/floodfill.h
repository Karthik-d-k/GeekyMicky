#ifndef FLOODFILL_H
#define FLOODFILL_H

#include "maze.h"

bool is_cell_accessible(CELL cell, int direction);

CELL neighbour_cell_at_direction(CELL cell, int direction);

void floodfill(const CELL target);

int test_floodfill();

#endif
