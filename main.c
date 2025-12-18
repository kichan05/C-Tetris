#include <stdio.h>
#include <windows.h>
#include "common/color.h"
#include "ui.h"
#include "common/util.h"

#define MAP_WIDTH 10
#define MAP_HEIGHT 20

#define BLOCK "█"
#define BLANK "."
// █▓▒░

int map[MAP_HEIGHT][MAP_WIDTH];

int main() {
    SetConsoleOutputCP(CP_UTF8);
    initScreen();

    while (1) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for(int x = 0; x < MAP_WIDTH; x++) {
                writeScreen(x, y, map[y][x] == 0 ? BLANK : BLOCK);
            }
        }

        flipScreen();
    }
    return 0;
}
