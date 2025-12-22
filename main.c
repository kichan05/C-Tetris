#include <stdio.h>
#include <windows.h>
#include "ui.h"
#include <stdlib.h>
#include <time.h>
#include "common/key.h"
#include "block.h"
#include "scene/mainScene.h"

int main() {
    srand(time(NULL));
    SetConsoleOutputCP(CP_UTF8);
    initScreen();

    mainScene();


    return 0;
}
