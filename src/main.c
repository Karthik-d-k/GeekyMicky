#include <stdio.h>

#include "floodfill.h"
#include "maze.h"
#include "queue.h"

void init() {
    init_maze();
}

int main() {
    init();

    test_queue();
    printf("\n");
    test_floodfill();

    return 0;
}
