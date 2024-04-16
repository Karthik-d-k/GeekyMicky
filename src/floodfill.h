#ifndef FLOODFILL_H
#define FLOODFILL_H

#include "maze.h"

#define START \
    CELL { 0, 0 }

typedef enum {
    EXIT = 0b00,    // a wall that has been seen and confirmed absent
    WALL = 0b01,    // a wall that has been seen and confirmed present
    UNKNOWN = 0b10, // a wall that has not yet been seen
    VIRTUAL = 0b11, // a wall that has not yet been seen
} WallState;

typedef struct {
    WallState north : 2;
    WallState east : 2;
    WallState south : 2;
    WallState west : 2;
} WallInfo;

typedef enum {
    MASK_OPEN = 0x01,   // open maze for search
    MASK_CLOSED = 0x03, // closed maze for fast run
} MazeMask;

void initialise_walls();

void set_wall_state(CELL loc, DIRECTION heading, WallState state);

bool is_cell_accessible(CELL cell, int direction);

CELL neighbour_cell(CELL cell, int direction);

void floodfill(const CELL target);

int test_floodfill();

#endif
