#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "maze.h"

void print_maze(uint8_t cost[MAZE_WIDTH][MAZE_HEIGHT]) {
    // Print the top border of the maze
    for (int i = 0; i < MAZE_WIDTH; i++) {
        // Print top border of each row
        for (int j = 0; j < MAZE_WIDTH; j++) {
            printf("+-------");
        }
        printf("+\n");

        // Print maze cost values
        for (int j = 0; j < MAZE_WIDTH; j++) {
            printf("| %5d ", cost[i][j]); // Assume each cost is at most two digits
        }
        printf("|\n");
    }

    // Print the bottom border of the last row
    for (int j = 0; j < MAZE_WIDTH; j++) {
        printf("+-------");
    }
    printf("+\n");
}
