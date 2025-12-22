//
// Created by 바키찬 on 2025-10-13.
//

#include "key.h"
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>

static int keyState[256] = {0};

int getKeyPress() {
    if(!_kbhit()) {
        return -1;
    }

    int key = _getch();
    if (key == 0 || key == 224) {
        key = _getch();
    }

    return key;
}

int isKeyDowned(int vk) {
    int current = GetAsyncKeyState(vk) & 0x8000;

    if(current && !keyState[vk]) {
        keyState[vk] = 1;
        return 1;
    }

    if(!current) {
        keyState[vk] = 0;
    }

    return 0;
}

void clearKeyState() {
    for (int i = 0; i < 256; i++) {
        keyState[i] = 0;
    }
}

int isKeyDown(int vk) {
    int current = GetAsyncKeyState(vk) & 0x8000;

    return current;
}