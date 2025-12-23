//
// Created by 바키찬 on 2025-12-23.
//

#ifndef C_TETRIS_CIRCULARQUEUE_H
#define C_TETRIS_CIRCULARQUEUE_H

#include "config.h"

typedef struct {
    int size;
    int front;
    int rear;
    int data[NEXT_BLOCK_QUEUE_SIZE];
} CircularQueue;

void enqueue(CircularQueue* queue, int value);
int dequeue(CircularQueue* queue);
int getValueOfIndex(CircularQueue* queue, int index);

#endif //C_TETRIS_CIRCULARQUEUE_H
