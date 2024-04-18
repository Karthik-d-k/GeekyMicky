#ifndef MAZE_H
#define MAZE_H

#include <stdint.h>

// MAZE CONSTANTS
#define MAZE_SIZE 16
#define MAZE_CELL_COUNT (MAZE_SIZE * MAZE_SIZE)
#define MAX_COST (MAZE_CELL_COUNT - 1)

#define START \
    CELL { 0, 0 }
#define END \
    CELL { 7, 7 }

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
    WALL_ABSENT = 0b00,  // a wall that has been seen and confirmed absent
    WALL_PRESENT = 0b01, // a wall that has been seen and confirmed present
    WALL_UNSEEN = 0b10,  // a wall that has not yet been seen
    WALL_VIRTUAL = 0b11, // a wall that does not exist in the physical maze, used for special cases
} WallState;

typedef struct {
    WallState north : 2;
    WallState east : 2;
    WallState south : 2;
    WallState west : 2;
} WallInfo;

typedef enum {
    MASK_TREAT_UNSEEN_AS_ABSENT = 0x01,  // treat unseen walls as absent during search
    MASK_TREAT_UNSEEN_AS_PRESENT = 0x03, // treat unseen walls as present during speed run
} MazeMask;

void initialise_walls();

void set_wall_state(CELL loc, DIRECTION heading, WallState state);

bool is_cell_accessible(CELL cell, int direction);

CELL neighbour_cell(CELL cell, int direction);

void print_maze(uint8_t cost[MAZE_SIZE][MAZE_SIZE]);

#endif
