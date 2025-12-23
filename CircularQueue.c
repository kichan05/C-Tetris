//
// Created by 바키찬 on 2025-12-23.
//

#include "CircularQueue.h"


void enqueue(CircularQueue* queue, int value) {
    if (queue->size >= NEXT_BLOCK_QUEUE_SIZE) {
        return;
    }

    queue->data[queue->rear] = value;
    queue->rear = (queue->rear + 1) % NEXT_BLOCK_QUEUE_SIZE;
    queue->size++;
}

int dequeue(CircularQueue* queue) {
    if (queue->size <= 0) {
        return -1;
    }

    int value = queue->data[queue->front];
    queue->front = (queue->front + 1) % NEXT_BLOCK_QUEUE_SIZE;
    queue->size--;

    return value;
}

int getValueOfIndex(CircularQueue* queue, int index) {
    if (index < 0 || index >= queue->size) {
        return -1;
    }

    int targetPos = (queue->front + index) % NEXT_BLOCK_QUEUE_SIZE;
    int value = queue->data[targetPos];

    return value;
}
