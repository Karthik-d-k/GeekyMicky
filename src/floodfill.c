#include <stdio.h>

#include "floodfill.h"
#include "maze.h"
#include "queue.h"

uint8_t COST[MAZE_WIDTH][MAZE_HEIGHT];
WallInfo WALLS[MAZE_WIDTH][MAZE_HEIGHT];

void initialise_walls() {
    for (int x = 0; x < MAZE_WIDTH; x++) {
        for (int y = 0; y < MAZE_HEIGHT; y++) {
            WALLS[x][y].north = UNKNOWN;
            WALLS[x][y].east = UNKNOWN;
            WALLS[x][y].south = UNKNOWN;
            WALLS[x][y].west = UNKNOWN;
        }
    }
    for (int x = 0; x < MAZE_WIDTH; x++) {
        WALLS[x][0].south = WALL;
        WALLS[x][MAZE_HEIGHT - 1].north = WALL;
    }
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        WALLS[0][y].west = WALL;
        WALLS[MAZE_WIDTH - 1][y].east = WALL;
    }
    // set_wall_state(START, EAST, WALL);
    WALLS[0][0].east = WALL;
    // set_wall_state(START, NORTH, EXIT);
    WALLS[0][0].north = EXIT;
}

bool is_cell_accessible(CELL cell, int direction) {
    bool result = false;
    WallInfo walls = WALLS[cell.x][cell.y];
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
        uint8_t new_y = cell.y + 1;
        if (new_y >= MAZE_HEIGHT) {
            return cell;
        }
        CELL neighbour_cell = {cell.x, new_y};
        return neighbour_cell;
    }
    case 1: { // East
        uint8_t new_x = cell.x + 1;
        if (new_x >= MAZE_WIDTH) {
            return cell;
        }
        CELL neighbour_cell = {new_x, cell.y};
        return neighbour_cell;
    }
    case 2: { // South
        uint8_t new_y = cell.y - 1;
        if (new_y < 0) {
            return cell;
        }
        CELL neighbour_cell = {cell.x, new_y};
        return neighbour_cell;
    }
    case 3: { // West
        uint8_t new_x = cell.x - 1;
        if (new_x < 0) {
            return cell;
        }
        CELL neighbour_cell = {new_x, cell.y};
        return neighbour_cell;
    }
    default:
        // Invalid direction, return current cell
        return cell;
    }
}

void floodfill(const CELL target) {
    // 1. Set all cells cost to "blank state" (255)
    for (int x = 0; x < MAZE_WIDTH; x++) {
        for (int y = 0; y < MAZE_HEIGHT; y++) {
            COST[x][y] = (uint8_t)MAX_COST;
        }
    }

    // 2. Set target cell cost value to 0 and add target cell to queue
    QUEUE queue;
    queue_init(&queue);
    COST[target.x][target.y] = 0;
    queue_push_rear(&queue, target);

    // 3. While queue is not empty
    while (!queue_is_empty(&queue)) {
        // 3a. Take first pushed cell from queue
        CELL current_cell = queue_pop_front(&queue);
        // 3b. Calculate new cell cost value based on current cell
        uint16_t newCost = COST[current_cell.x][current_cell.y] + 1;

        // 3c. Set all "blank" and "accessible(no wall)" cells cost to new cost
        for (int direction = 0; direction <= 3; direction++) {
            if (is_cell_accessible(current_cell, direction)) {
                CELL nextCell = neighbour_cell(current_cell, direction);
                if (COST[nextCell.x][nextCell.y] > newCost) {
                    COST[nextCell.x][nextCell.y] = newCost;
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
