#include "mouse.h"
#include "floodfill.h"
#include "maze.h"
#include "motor.h"
#include "sensor.h"

extern ABSOLUTE_DIRECTION CURRENT_ABSOLUTE_DIRECTION;
extern CELL CURRENT_CELL;

void move(void) {
    float front_dist = get_ultrasonic_dist(FRONT_US_TRIG, FRONT_US_ECHO);
    float target_dist = front_dist - CELL_LENGTH + FORWARD_DIST_OFFSET;
    unsigned long start_time = millis();

    if (target_dist > 0.0) {
        forward_motors(FORWARD_MOTOR_SPEED);
        while (get_ultrasonic_dist(FRONT_US_TRIG, FRONT_US_ECHO) > target_dist) {
            if (millis() - start_time > MOVEMENT_TIMEOUT) {
                break; // Timeout to avoid infinite loop
            }
        }
        stop_motors();
    }
}

bool turn_completed(float front_dist_prev, float side_dist_prev, bool is_right_turn) {
    float front_dist_now = get_ultrasonic_dist(FRONT_US_TRIG, FRONT_US_ECHO);
    float side_dist_now = is_right_turn ? get_ultrasonic_dist(LEFT_US_TRIG, LEFT_US_ECHO) : get_ultrasonic_dist(RIGHT_US_TRIG, RIGHT_US_ECHO);
    bool cond1 = (fabs(front_dist_now - side_dist_prev) <= DELTA_TURN_COMPLETE);
    bool cond2 = (fabs(side_dist_now - front_dist_prev) <= DELTA_TURN_COMPLETE);

    return cond1 && cond2;
}

void turn_right(void) {
    float front_dist = get_ultrasonic_dist(FRONT_US_TRIG, FRONT_US_ECHO) + TURNING_DIST_OFFSET;
    float right_dist = get_ultrasonic_dist(RIGHT_US_TRIG, RIGHT_US_ECHO) + TURNING_DIST_OFFSET;
    unsigned long start_time = millis();

    right_motors(TURNING_MOTOR_SPEED);
    delay(TURNING_DELAY); // delay before checking for turning complete, so that motors turn a little

    while (!turn_completed(front_dist, right_dist, true)) {
        if (millis() - start_time > MOVEMENT_TIMEOUT) {
            break; // Timeout to avoid infinite loop
        }
    }
    stop_motors();
}

void turn_left(void) {
    float front_dist = get_ultrasonic_dist(FRONT_US_TRIG, FRONT_US_ECHO) + TURNING_DIST_OFFSET;
    float left_dist = get_ultrasonic_dist(LEFT_US_TRIG, LEFT_US_ECHO) + TURNING_DIST_OFFSET;
    unsigned long start_time = millis();

    left_motors(TURNING_MOTOR_SPEED);
    delay(TURNING_DELAY); // delay before checking for turning complete, so that motors turn a little
    while (!turn_completed(front_dist, left_dist, false)) {
        if (millis() - start_time > MOVEMENT_TIMEOUT) {
            break; // Timeout to avoid infinite loop
        }
    }
    stop_motors();
}

void turn_to_face(ABSOLUTE_DIRECTION new_direction) {
    RELATIVE_DIRECTION direction_change = (RELATIVE_DIRECTION)((new_direction + ABS_DIR_COUNT - CURRENT_ABSOLUTE_DIRECTION) % REL_DIR_COUNT);

    switch (direction_change) {
    case AHEAD:
        break;
    case RIGHT:
        turn_right();
        move();
        break;
    case BACK:
        turn_right();
        turn_right();
        break;
    case LEFT:
        turn_left();
        move();
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
            turn_right();
            move();
            break;
        case BACK:
            turn_right();
            turn_right();
            break;
        case LEFT:
            turn_left();
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
            move();
            break;
        case RIGHT:
            turn_right();
            move();
            break;
        case BACK:
            turn_right();
            turn_right();
            break;
        case LEFT:
            turn_left();
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
