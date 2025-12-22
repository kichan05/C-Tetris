//
// Created by 바키찬 on 2025-12-22.
//


#include "gameResultScene.h"
#include "../common/util.h"
#include "../common/key.h"
#include "../ui.h"

void gameResultScene(int score) {
    while (1) {
        clearScreen();
        writeHorizontalCenter(10, COLOR_CYAN "=== GAME OVER ===" COLOR_RESET);
        writeHorizontalCenter(11, fs("%s Score: %d %s", COLOR_GREEN, score, COLOR_RESET));
        writeHorizontalCenter(13, fs("%s Enter Enter key for Restart %s", COLOR_YELLOW, COLOR_RESET));

        if(isKeyDowned(VK_RETURN)){
            return;
        }

        flipScreen();
        Sleep(66);
    }
}
