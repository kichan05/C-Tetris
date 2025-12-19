//
// Created by 바키찬 on 2025-12-20.
//

#include "config.h"

#ifndef C_TETRIS_BLOCK_H
#define C_TETRIS_BLOCK_H

typedef struct Block {
    int width;
    int height;
    int shape[4][4];
} Block;

static Block BLOCK_TEMPLATE[BLOCK_TYPE_COUNT][4] = {
        {
                {1, 4, {
                               {1},
                               {1},
                               {1},
                               {1},
                       }},
                {4, 1, {
                               {1, 1, 1, 1},
                       }},
                {1, 4, {
                               {1},
                               {1},
                               {1},
                               {1},
                       }},
                {4, 1, {
                               {1, 1, 1, 1},
                       }},
        },
        {
                {3, 3, {
                               {0, 0, 0},
                               {0, 1, 0},
                               {1, 1, 1}
                       }},
                {2, 3, {
                               {1, 0},
                               {1, 1},
                               {1, 0},
                       }},
                {3, 2, {
                               {1, 1, 1},
                               {0, 1, 0}
                       }},
                {2, 3, {
                               {0, 1},
                               {1, 1},
                               {0, 1},
                       }},
        },
        {
                {2, 2, {
                               {1, 1},
                               {1, 1},
                       }},
                {2, 2, {
                               {1, 1},
                               {1, 1},
                       }},
                {2, 2, {
                               {1, 1},
                               {1, 1},
                       }},
                {2, 2, {
                               {1, 1},
                               {1, 1},
                       }},
        },
};

#endif //C_TETRIS_BLOCK_H
