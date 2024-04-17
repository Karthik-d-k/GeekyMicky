#ifndef MAZE_H
#define MAZE_H

#include <stdint.h>

// MAZE CONSTANTS
#define MAZE_WIDTH 16
#define MAZE_HEIGHT 16
#define MAZE_CELL_COUNT (MAZE_WIDTH * MAZE_HEIGHT)
#define MAX_COST (MAZE_CELL_COUNT - 1)

typedef struct {
    uint8_t x;
    uint8_t y;
} CELL;

typedef enum { NORTH,
               EAST,
               SOUTH,
               WEST,
               HEADING_COUNT,
               BLOCKED = 99 } DIRECTION;

void print_maze(uint8_t cost[MAZE_WIDTH][MAZE_HEIGHT]);

#endif
