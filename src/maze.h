#ifndef MAZE_H
#define MAZE_H

#include <stdint.h>

// MAZE CONSTANTS
#define MAZE_SIZE 16
#define MAZE_CELL_COUNT (MAZE_SIZE * MAZE_SIZE)
#define MAX_COST (MAZE_CELL_COUNT - 1)

#define START \
    CELL { 0, 0 }

typedef struct {
    uint8_t r;
    uint8_t c;
} CELL;

typedef enum { NORTH,
               EAST,
               SOUTH,
               WEST,
               HEADING_COUNT,
               BLOCKED = 99 } DIRECTION;

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

void print_maze(uint8_t cost[MAZE_SIZE][MAZE_SIZE]);

#endif
