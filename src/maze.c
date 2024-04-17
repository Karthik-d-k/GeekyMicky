#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "maze.h"

void print_maze(uint8_t cost[MAZE_SIZE][MAZE_SIZE]) {
    // Print the top border of the maze
    for (int col = MAZE_SIZE - 1; col >= 0; col--) {
        // Print top border of each row
        for (int i = 0; i < MAZE_SIZE; i++) {
            printf("+-------");
        }
        printf("+\n");

        // Print maze cost values
        for (int row = 0; row < MAZE_SIZE; row++) {
            // int linear_index = col * MAZE_SIZE + row;
            printf("| %5d ", cost[col][row]);
        }
        printf("|\n");
    }

    // Print the bottom border of the last row
    for (int i = 0; i < MAZE_SIZE; i++) {
        printf("+-------");
    }
    printf("+\n");
}
