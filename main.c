#include <stdio.h>
#include <windows.h>
#include "common/color.h"
#include "ui.h"
#include "common/util.h"

#define MAP_WIDTH 10
#define MAP_HEIGHT 20

int map[MAP_HEIGHT][MAP_WIDTH];

int main() {
    initScreen();

    map[10][5] = 1;

    while (1) {
        clearScreen();

        for (int y = 0; y < MAP_HEIGHT; y++) {
            for(int x = 0; x < MAP_WIDTH; x++) {
                writeScreen(x, y, fs("%d", map[y][x]));
            }
        }

        flipScreen();
    }
    return 0;
}
