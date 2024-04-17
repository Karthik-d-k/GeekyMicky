#include <stdio.h>

#include "floodfill.h"
#include "maze.h"
#include "queue.h"

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

void floodfill(const CELL target) {
    // 1. Set all cells cost to "blank state" (255)
    for (int r = 0; r < MAZE_SIZE; r++) {
        for (int c = 0; c < MAZE_SIZE; c++) {
            COST[r][c] = (uint8_t)MAX_COST;
        }
    }

    // 2. Set target cell cost value to 0 and add target cell to queue
    QUEUE queue;
    queue_init(&queue);
    COST[target.r][target.c] = 0;
    queue_push_rear(&queue, target);

    // 3. While queue is not empty
    while (!queue_is_empty(&queue)) {
        // 3a. Take first pushed cell from queue
        CELL current_cell = queue_pop_front(&queue);
        // 3b. Calculate new cell cost value based on current cell
        uint16_t newCost = COST[current_cell.r][current_cell.c] + 1;

        // 3c. Set all "blank" and "accessible(no wall)" cells cost to new cost
        for (int direction = 0; direction <= 3; direction++) {
            if (is_cell_accessible(current_cell, direction)) {
                CELL nextCell = neighbour_cell(current_cell, direction);
                if (COST[nextCell.r][nextCell.c] > newCost) {
                    COST[nextCell.r][nextCell.c] = newCost;
                    // 3d. Add cells we just processed to queue
                    queue_push_rear(&queue, nextCell);
                }
            }
        }
    }
}

// -------------------TEST / USAGE ------------------------- //
int test_floodfill() {
    CELL goal = {7, 7};
    initialise_walls();
    floodfill(goal);
    print_maze(COST);

    return 0;
}
