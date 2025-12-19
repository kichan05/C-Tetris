#include <stdio.h>
#include <windows.h>
#include "common/color.h"
#include "ui.h"
#include "common/util.h"
#include "common/key.h"

#define MAP_WIDTH 10
#define MAP_HEIGHT 20
#define BLOCK_TYPE_COUNT 3

#define BLOCK "█"
#define BLANK "."
// █▓▒░

int map[MAP_HEIGHT][MAP_WIDTH];

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
                        {1, 0} ,
                        {1, 1} ,
                        {1, 0} ,
                }},
                {3, 2, {
                        {1, 1, 1},
                        {0, 1, 0}
                }},
                {2, 3, {
                        {0, 1} ,
                        {1, 1} ,
                        {0, 1} ,
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

int isMoveAble(int x, int y, int blockType, int blockRotate) {
    Block block = BLOCK_TEMPLATE[blockType][blockRotate];

    if(x < 0)
        return 0;

    if(x + block.width > MAP_WIDTH)
        return 0;

    if(y + block.height > MAP_HEIGHT)
        return 0;

    return 1;
}

int isMoveAbleWrap(int x, int y, int blockType, int blockRotate) {
    int res = isMoveAble(x, y, blockType, blockRotate);

    if(res){
        writeScreen(0, MAP_HEIGHT + 1, COLOR_GREEN "move able" COLOR_RESET);
    }
    else {
        writeScreen(0, MAP_HEIGHT + 1, COLOR_RED "move unable" COLOR_RESET);
    }

    return res;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    initScreen();

    COORD position = {0, 0};
    int block_rotate = 0;
    int blockType = 1;

    while (1) {
        clearScreen();

        Block b = BLOCK_TEMPLATE[blockType][block_rotate];

        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                writeScreen(x, y, map[y][x] == 0 ? BLANK : BLOCK);
            }
        }

        for (int y = 0; y < b.height; y++) {
            for (int x = 0; x < b.width; x++) {
                writeScreen(position.X + x, position.Y + y, b.shape[y][x] == 0 ? BLANK : BLOCK);
            }
        }

        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            if (isMoveAbleWrap(position.X - 1, position.Y, blockType, block_rotate)) {
                position.X -= 1;
            }
        }

        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            if (isMoveAbleWrap(position.X + 1, position.Y, blockType, block_rotate)) {
                position.X += 1;
            }
        }

        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            if (isMoveAbleWrap(position.X, position.Y + 1, blockType, block_rotate)) {
                position.Y += 1;
            }
        }
        if(GetAsyncKeyState(VK_UP) & 0x8000) {
            if(isMoveAbleWrap(position.X, position.Y, blockType, (block_rotate + 1) % 4)){
                block_rotate = (block_rotate + 1) % 4;
            }
        }

        flipScreen();
        Sleep(50);
    }
    return 0;
}
