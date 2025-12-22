//
// Created by 바키찬 on 2025-12-22.
//

#include "initScene.h"
#include "../common/color.h"
#include "../common/util.h"
#include "../common/key.h"

int initScene() {
    int selectMeniIndex = 0;

    while (1) {
        clearScreen();

        writeScreen(0, 0, "Welcome Tetris");
        writeScreen(0, 1, fs("%s1. Play Tetris%s", selectMeniIndex == 0 ? COLOR_YELLOW : COLOR_RESET, COLOR_RESET));
        writeScreen(0, 2, fs("%s2. Setting Game%s", selectMeniIndex == 1 ? COLOR_YELLOW : COLOR_RESET, COLOR_RESET));
        writeScreen(0, 3, fs("%s3. Exit%s", selectMeniIndex == 2 ? COLOR_YELLOW : COLOR_RESET, COLOR_RESET));

        int key = getKeyPress();

        switch (key) {
            case KEY_DOWN:
                if(selectMeniIndex + 1 <= 2) {
                    selectMeniIndex += 1;
                }
                break;
            case KEY_UP:
                if(selectMeniIndex - 1 >= 0) {
                    selectMeniIndex -= 1;
                }
                break;
            case KEY_ENTER:
                return selectMeniIndex;
        }

        flipScreen();
        Sleep(33);
    }
}
