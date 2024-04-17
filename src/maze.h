#ifndef MAZE_H
#define MAZE_H

#include <stdint.h>

// MAZE CONSTANTS
#define MAZE_SIZE 16
#define MAZE_CELL_COUNT (MAZE_SIZE * MAZE_SIZE)
#define MAX_COST (MAZE_CELL_COUNT - 1)

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

void print_maze(uint8_t cost[MAZE_SIZE][MAZE_SIZE]);

#endif
