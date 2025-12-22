#include <stdio.h>
#include <windows.h>
#include "ui.h"
#include <stdlib.h>
#include <time.h>
#include "common/key.h"
#include "block.h"
#include "scene/mainScene.h"
#include "scene/initScene.h"

int main() {
    srand(time(NULL));
    SetConsoleOutputCP(CP_UTF8);
    initScreen();

    while (1) {
        int selectMeniIndex = initScene();

        switch (selectMeniIndex) {
            case 0:
                mainScene();
                clearKeyState();
                break;
            case 1:
                break;
            case 2:
                return 1;
        }
    }

    return 0;
}
