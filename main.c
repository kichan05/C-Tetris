#include <stdio.h>
#include <windows.h>
#include "common/color.h"
#include "ui.h"
#include <stdlib.h>
#include <time.h>
#include "common/util.h"
#include "common/key.h"
#include "block.h"
#include "config.h"

int map[MAP_HEIGHT][MAP_WIDTH];
static int IS_DEBUG = 0;

int isMoveAble(int x, int y, int blockType, int blockRotate) {
    Block block = BLOCK_TEMPLATE[blockType][blockRotate];

    if (x < 0)
        return 0;

    if (x + block.width > MAP_WIDTH)
        return 0;

    if (y + block.height > MAP_HEIGHT)
        return 0;

    for (int by = 0; by < block.height; by++) {
        for (int bx = 0; bx < block.width; bx++) {
            if (block.shape[by][bx] == 0)
                continue;

            if (map[y + by][x + bx])
                return 0;
        }
    }

    return 1;
}

int isMoveAbleWrap(int x, int y, int blockType, int blockRotate) {
    int res = isMoveAble(x, y, blockType, blockRotate);

    if(IS_DEBUG) {
        if (res) {
            writeScreen(0, MAP_HEIGHT + 1, COLOR_GREEN "move able" COLOR_RESET);
        } else {
            writeScreen(0, MAP_HEIGHT + 1, COLOR_RED "move unable" COLOR_RESET);
        }
    }

    return res;
}

int main() {
    srand(time(NULL));
    SetConsoleOutputCP(CP_UTF8);
    initScreen();

    COORD position = {0, 0};
    int block_rotate = 0;
    int blockType = 0;

    while (1) {
        clearScreen();

        Block b = BLOCK_TEMPLATE[blockType][block_rotate];

        writeScreen(0, MAP_HEIGHT + 1, fs("X : %d   \tY : %d", position.X, position.Y));
        writeScreen(0, MAP_HEIGHT + 2, fs("BlockType: %d\tBlockRotate : %d", blockType, block_rotate));

        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                writeScreen(x, y, map[y][x] == 0 ? BLANK : BLOCK);
            }
        }

        for (int y = 0; y < b.height; y++) {
            for (int x = 0; x < b.width; x++) {
                if (b.shape[y][x]) {
                    writeScreen(position.X + x, position.Y + y, COLOR_MAGENTA BLOCK COLOR_RESET);
                }
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
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            if (isMoveAbleWrap(position.X, position.Y, blockType, (block_rotate + 1) % 4)) {
                block_rotate = (block_rotate + 1) % 4;
            }
        }
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
            while (isMoveAbleWrap(position.X, position.Y + 1, blockType, block_rotate)) {
                position.Y += 1;
            }

            for (int by = 0; by < b.height; by++) {
                for (int bx = 0; bx < b.width; bx++) {
                    if(b.shape[by][bx]){
                        map[position.Y + by][position.X + bx] = b.shape[by][bx];
                    }
                }
            }

            position.X = 0;
            position.Y = 0;
            blockType = randomInt(0, BLOCK_TYPE_COUNT);
            block_rotate = 0;
        }

        flipScreen();
        Sleep(60);
    }
    return 0;
}
