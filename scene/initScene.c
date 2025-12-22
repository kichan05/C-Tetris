//
// Created by 바키찬 on 2025-12-22.
//

#include "initScene.h"
#include "../common/color.h"
#include "../common/util.h"
#include "../common/key.h"

const char* RAINBOW_COLORS[] = {
        COLOR_RED, COLOR_ORANGE, COLOR_YELLOW, COLOR_GREEN, COLOR_CYAN, COLOR_BLUE, COLOR_MAGENTA
};
#define COLOR_COUNT 7

void writeRainbowCenter(int y, const char* str) {
    int len = (int)strlen(str);
    int padding = (getWindowWidth() - len) / 2;

    int colorIdx = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] != ' ') {
            writeScreen(padding + i, y, fs("%s%c", RAINBOW_COLORS[colorIdx % COLOR_COUNT], str[i]));
            colorIdx++;
        }
    }
}

int initScene() {
    int selectMeniIndex = 0;

    while (1) {
        clearScreen();

        int titleY = 5;
        writeRainbowCenter(titleY++, " ____  ____  ____  ____   __   ____ ");
        writeRainbowCenter(titleY++, "(_  _)(  __)(_  _)(  _ \\ (  ) / ___\\");
        writeRainbowCenter(titleY++, "  )(   ) _)   )(   )   /  )(  \\___ \\");
        writeRainbowCenter(titleY++, " (__) (____) (__) (__\\_) (__) (____/");

        titleY += 3;
        writeHorizontalCenter(titleY++, COLOR_CYAN "==== Menu ====" COLOR_RESET);
        titleY += 1;

        writeHorizontalCenter(titleY++, fs("%s1. Play Tetris%s", selectMeniIndex == 0 ? COLOR_YELLOW : COLOR_RESET, COLOR_RESET));
        writeHorizontalCenter(titleY++, fs("%s2. Setting Game%s", selectMeniIndex == 1 ? COLOR_YELLOW : COLOR_RESET, COLOR_RESET));
        writeHorizontalCenter(titleY++, fs("%s3. Exit%s", selectMeniIndex == 2 ? COLOR_YELLOW : COLOR_RESET, COLOR_RESET));

        if(isKeyDowned(VK_UP) && selectMeniIndex - 1 >= 0) {
            selectMeniIndex -= 1;
        }
        else if(isKeyDowned(VK_DOWN) && selectMeniIndex + 1 <= 2) {
            selectMeniIndex += 1;
        }
        else if(isKeyDowned(VK_RETURN)) {
            return selectMeniIndex;
        }

        flipScreen();
        Sleep(33);
    }
}
