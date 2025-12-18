//
// Created by 바키찬 on 2025-10-13.
//

#include <conio.h>

int getKeyPress() {
    int key = _getch();
    if (key == 0 || key == 224) {
        key = _getch();
    }

    return key;
}
