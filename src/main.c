#include <stdio.h>

#include "floodfill.h"
#include "maze.h"
#include "queue.h"

int main() {
    int out1 = test_queue();
    printf("\n");
    int out2 = test_floodfill();

    return 0;
}
