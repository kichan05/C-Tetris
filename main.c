#include <stdio.h>
#include <windows.h>
#include "common/color.h"
#include "ui.h"
#include "common/util.h"
#include "common/key.h"

#define MAP_WIDTH 10
#define MAP_HEIGHT 20

#define BLOCK "█"
#define BLANK "."
// █▓▒░

int map[MAP_HEIGHT][MAP_WIDTH];

typedef struct Block {
    int width;
    int height;
    int shape[4][4];
} Block;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    initScreen();

    COORD position = {0, 0};
    Block b = {
            2, 2,
            {
                    {1, 1},
                    {1, 1},
            }
    };


    while (1) {
        clearScreen();

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
            if (position.X - 1 >= 0) {
                position.X -= 1;
            }
        }

        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            if (position.X + b.width < MAP_WIDTH) {
                position.X += 1;
            }
        }

        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            if(position.Y + b.height < MAP_HEIGHT) {
                position.Y += 1;
            }
        }

        flipScreen();
        Sleep(33);
    }
    return 0;
}
