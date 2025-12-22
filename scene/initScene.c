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
