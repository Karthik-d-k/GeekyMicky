#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "maze.h"

WallInfo WALLS[MAZE_SIZE][MAZE_SIZE];
MazeMask MAZE_MASK;

void init_walls() {
    for (int r = 0; r < MAZE_SIZE; r++) {
        for (int c = 0; c < MAZE_SIZE; c++) {
            WALLS[r][c].north = WALL_UNSEEN;
            WALLS[r][c].east = WALL_UNSEEN;
            WALLS[r][c].south = WALL_UNSEEN;
            WALLS[r][c].west = WALL_UNSEEN;
        }
    }
    for (int r = 0; r < MAZE_SIZE; r++) {
        WALLS[r][0].south = WALL_PRESENT;
        WALLS[r][MAZE_SIZE - 1].north = WALL_PRESENT;
    }
    for (int c = 0; c < MAZE_SIZE; c++) {
        WALLS[0][c].west = WALL_PRESENT;
        WALLS[MAZE_SIZE - 1][c].east = WALL_PRESENT;
    }
    // set_wall_state(START, EAST, WALL_PRESENT);
    WALLS[0][0].east = WALL_PRESENT;
    // set_wall_state(START, NORTH, WALL_ABSENT);
    WALLS[0][0].north = WALL_ABSENT;
}

bool is_cell_accessible(CELL cell, int direction) {
    bool result = false;
    WallInfo walls = WALLS[cell.r][cell.c];
    switch (direction) {
    case 0:
        result = (walls.north & MAZE_MASK) == WALL_ABSENT;
        break;
    case 1:
        result = (walls.east & MAZE_MASK) == WALL_ABSENT;
        break;
    case 2:
        result = (walls.south & MAZE_MASK) == WALL_ABSENT;
        break;
    case 3:
        result = (walls.west & MAZE_MASK) == WALL_ABSENT;
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

void set_mask(const MazeMask mask) {
    MAZE_MASK = mask;
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

void init_maze() {
    init_walls();
    set_mask(MASK_TREAT_UNSEEN_AS_ABSENT);
}
