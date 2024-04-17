#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "maze.h"

uint8_t COST[MAZE_SIZE][MAZE_SIZE];
WallInfo WALLS[MAZE_SIZE][MAZE_SIZE];

void initialise_walls() {
    for (int r = 0; r < MAZE_SIZE; r++) {
        for (int c = 0; c < MAZE_SIZE; c++) {
            WALLS[r][c].north = UNKNOWN;
            WALLS[r][c].east = UNKNOWN;
            WALLS[r][c].south = UNKNOWN;
            WALLS[r][c].west = UNKNOWN;
        }
    }
    for (int r = 0; r < MAZE_SIZE; r++) {
        WALLS[r][0].south = WALL;
        WALLS[r][MAZE_SIZE - 1].north = WALL;
    }
    for (int c = 0; c < MAZE_SIZE; c++) {
        WALLS[0][c].west = WALL;
        WALLS[MAZE_SIZE - 1][c].east = WALL;
    }
    // set_wall_state(START, EAST, WALL);
    WALLS[0][0].east = WALL;
    // set_wall_state(START, NORTH, EXIT);
    WALLS[0][0].north = EXIT;
}

bool is_cell_accessible(CELL cell, int direction) {
    bool result = false;
    WallInfo walls = WALLS[cell.r][cell.c];
    switch (direction) {
    case 0:
        result = (walls.north & MASK_OPEN) == EXIT;
        break;
    case 1:
        result = (walls.east & MASK_OPEN) == EXIT;
        break;
    case 2:
        result = (walls.south & MASK_OPEN) == EXIT;
        break;
    case 3:
        result = (walls.west & MASK_OPEN) == EXIT;
        break;
    default:
        result = false;
        break;
    }

    return result;
}

CELL neighbour_cell(CELL cell, int direction) {
    switch (direction) {
    case 0: { // North
        uint8_t new_y = cell.c + 1;
        if (new_y >= MAZE_SIZE) {
            return cell;
        }
        CELL neighbour_cell = {cell.r, new_y};
        return neighbour_cell;
    }
    case 1: { // East
        uint8_t new_x = cell.r + 1;
        if (new_x >= MAZE_SIZE) {
            return cell;
        }
        CELL neighbour_cell = {new_x, cell.c};
        return neighbour_cell;
    }
    case 2: { // South
        uint8_t new_y = cell.c - 1;
        if (new_y < 0) {
            return cell;
        }
        CELL neighbour_cell = {cell.r, new_y};
        return neighbour_cell;
    }
    case 3: { // West
        uint8_t new_x = cell.r - 1;
        if (new_x < 0) {
            return cell;
        }
        CELL neighbour_cell = {new_x, cell.c};
        return neighbour_cell;
    }
    default:
        // Invalid direction, return current cell
        return cell;
    }
}

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
