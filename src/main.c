#include <stdio.h>

#include "floodfill.h"
#include "maze.h"
#include "queue.h"

void init() {
    init_maze();
}

int main() {
    init();

    int out1 = test_queue();
    printf("\n");
    int out2 = test_floodfill();

    return 0;
}
