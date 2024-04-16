#include <stdio.h>

#include "floodfill.h"
#include "maze.h"
#include "queue.h"

uint8_t COST[MAZE_WIDTH][MAZE_HEIGHT];

bool is_cell_accessible(CELL cell, int direction) {
    // impl missing
    return true;
}

CELL neighbour_cell_at_direction(CELL cell, int direction) {
    // impl missing
    return cell;
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
        for (int direction = 0; direction < 3; direction++) {
            if (is_cell_accessible(current_cell, direction)) {
                CELL nextCell = neighbour_cell_at_direction(current_cell, direction);
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

    printf("BEFORE:\n\n");
    print_maze(COST);
    printf("\n\n");

    floodfill(goal);

    printf("AFTER:\n\n");
    print_maze(COST);
    printf("\n\n");

    return 0;
}
