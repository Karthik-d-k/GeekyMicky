#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define QUEUE_SIZE 64 // Maximum number of elements of the circular buffer

typedef struct {
    uint8_t data[QUEUE_SIZE];
    uint8_t front;
    uint8_t rear;
    uint8_t size;
} QUEUE;

void queue_init(QUEUE* queue) {
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
}

bool queue_is_empty(QUEUE* queue) {
    return queue->size == 0;
}

void queue_push_rear(QUEUE* queue, uint8_t item) {
    queue->data[queue->rear] = item;
    queue->rear = (queue->rear + 1) % QUEUE_SIZE;
    queue->size++;
}

uint8_t queue_pop_front(QUEUE* queue) {
    uint8_t item = queue->data[queue->front];
    queue->front = (queue->front + 1) % QUEUE_SIZE;
    queue->size--;

    return item;
}

// -------------------TEST / USAGE ------------------------- //
int test_queue() {
    QUEUE queue;
    queue_init(&queue);

    int value = 100;
    for (int i = 0; i < 10; i++) {
        queue_push_rear(&queue, value++);
    }
    for (int i = 0; i < 10; i++) {
        uint8_t pop_value = queue_pop_front(&queue);
        printf("Read %d\n", pop_value);
    }
}
