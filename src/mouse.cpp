#include "mouse.h"
#include "floodfill.h"
#include "maze.h"
#include "motor.h"
#include "sensor.h"

extern ABSOLUTE_DIRECTION CURRENT_ABSOLUTE_DIRECTION;
extern CELL CURRENT_CELL;

void move(void) {
    float front_dist = get_ultrasonic_dist(FRONT_US_TRIG, FRONT_US_ECHO);
    float target_dist = front_dist - CELL_LENGTH + FRONT_DIST_OFFSET;

    if (target_dist > 0.0) {
        forward_motors(FORWARD_MOTOR_SPEED);
        while (get_ultrasonic_dist(FRONT_US_TRIG, FRONT_US_ECHO) <= target_dist) {
            continue;
        }
        stop_motors();
    }
}

void turn_to_face(ABSOLUTE_DIRECTION new_direction) {
    RELATIVE_DIRECTION direction_change = (RELATIVE_DIRECTION)((new_direction + ABS_DIR_COUNT - CURRENT_ABSOLUTE_DIRECTION) % REL_DIR_COUNT);

    switch (direction_change) {
    case AHEAD:
        break;
    case RIGHT:
        // API_turnRight();
        break;
    case BACK:
        // API_turnRight();
        // API_turnRight();
        break;
    case LEFT:
        // API_turnLeft();
        break;
    default:
        // Ignore any other directions
        break;
    }
    CURRENT_ABSOLUTE_DIRECTION = new_direction;
}

void search_to(CELL target) {
    while ((CURRENT_CELL.r != target.r) || (CURRENT_CELL.c != target.c)) {
        WallState front_wall = is_wall_present(FRONT_US_TRIG, FRONT_US_ECHO, FRONT_WALL_THRESHOLD) ? WALL_PRESENT : WALL_ABSENT;
        WallState right_wall = is_wall_present(RIGHT_US_TRIG, RIGHT_US_ECHO, RIGHT_WALL_THRESHOLD) ? WALL_PRESENT : WALL_ABSENT;
        WallState left_wall = is_wall_present(LEFT_US_TRIG, LEFT_US_ECHO, LEFT_WALL_THRESHOLD) ? WALL_PRESENT : WALL_ABSENT;

        update_walls(front_wall, right_wall, left_wall);
        floodfill(target);

        ABSOLUTE_DIRECTION new_direction = smallest_neighbour_direction(CURRENT_CELL, CURRENT_ABSOLUTE_DIRECTION);
        RELATIVE_DIRECTION direction_change = (RELATIVE_DIRECTION)((new_direction - CURRENT_ABSOLUTE_DIRECTION) & 0x3);

        switch (direction_change) {
        case AHEAD:
            move();
            break;
        case RIGHT:
            // turn_to_face(RIGHT);
            move();
            break;
        case BACK:
            // turn_to_face(BACK);
            break;
        case LEFT:
            // turn_to_face(LEFT);
            move();
            break;
        default:
            // Ignore any other directions
            break;
        }

        // update to new direction and new cell
        CURRENT_ABSOLUTE_DIRECTION = new_direction;
        CURRENT_CELL = neighbour_cell(CURRENT_CELL, CURRENT_ABSOLUTE_DIRECTION);
    }
}

void run_to(CELL target) {
    set_mask(MASK_UNSEEN_WALLS_AS_PRESENT);
    floodfill(target);

    while ((CURRENT_CELL.r != target.r) || (CURRENT_CELL.c != target.c)) {
        ABSOLUTE_DIRECTION new_direction = smallest_neighbour_direction(CURRENT_CELL, CURRENT_ABSOLUTE_DIRECTION);
        RELATIVE_DIRECTION direction_change = (RELATIVE_DIRECTION)((new_direction - CURRENT_ABSOLUTE_DIRECTION) & 0x3);

        switch (direction_change) {
        case AHEAD:
            // API_moveAhead();
            break;
        case RIGHT:
            // API_turnRight();
            // API_moveAhead();
            break;
        case BACK:
            // API_turnRight();
            // API_turnRight();
            // API_moveAhead();
            break;
        case LEFT:
            // API_turnLeft();
            // API_moveAhead();
            break;
        default:
            // Ignore any other directions
            break;
        }

        // update to new direction and new cell
        CURRENT_ABSOLUTE_DIRECTION = new_direction;
        CURRENT_CELL = neighbour_cell(CURRENT_CELL, CURRENT_ABSOLUTE_DIRECTION);
    }
}
