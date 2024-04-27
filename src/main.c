#include <stdio.h>
#include <stdlib.h>

#include "floodfill.h"
#include "maze.h"
#include "queue.h"

void init(void) {
    init_maze();
}

int main(void) {
    init();

    test_queue();
    printf("\n");
    test_floodfill();

    return EXIT_SUCCESS;
}
