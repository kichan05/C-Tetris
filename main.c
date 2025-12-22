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

    int selectMeniIndex = initScene();

    switch (selectMeniIndex) {
        case 0:
            mainScene();
        case 1:
            break;
        case 2:
            break;
    }

    return 0;
}
