#include <stdio.h>
#include <windows.h>
#include "common/color.h"
#include "ui.h"

int main() {
    initScreen();

    while (1) {
        clearScreen();

        writeScreen(0, 0, COLOR_RED "Hello " COLOR_MAGENTA "Double Buffer!" COLOR_RESET);
        writeScreen(0, 20, "Hello World");

        flipScreen();
    }
    return 0;
}
