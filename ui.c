//
// Created by 바키찬 on 2025-10-13.
//

#include "common/color.h"
#include <windows.h>
#include <stdio.h>
#include "ui.h"
#include <stdarg.h>

static HANDLE hBuffer[2];
static int nScreenIndex = 0;

int getWindowWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return -1;
    return (csbi.srWindow.Right - csbi.srWindow.Left + 1);
}

int getWindowHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return -1;
    return (csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
}

void setCursor(enum CURSOR_TYPE curType) {
    static CONSOLE_CURSOR_INFO CurInfo = {0,};

    switch (curType) {
        case HIDE:
            CurInfo.dwSize = 1;
            CurInfo.bVisible = FALSE;
            break;
        case UNDERBAR:
            CurInfo.dwSize = 1;
            CurInfo.bVisible = TRUE;
            break;
        case BLOCK:
            CurInfo.dwSize = 100;
            CurInfo.bVisible = TRUE;
            break;
    }

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

int currentX() {
    static CONSOLE_SCREEN_BUFFER_INFO curInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    return curInfo.dwCursorPosition.X;
}

int currentY() {
    static CONSOLE_SCREEN_BUFFER_INFO curInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    return curInfo.dwCursorPosition.Y;
}

void initScreen() {
    for (int i = 0; i < 2; i++) {
        hBuffer[i] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

        DWORD dwMode = 0;
        GetConsoleMode(hBuffer[i], &dwMode);

        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hBuffer[i], dwMode);

        CONSOLE_CURSOR_INFO cursorInfo = {1, FALSE};
        SetConsoleCursorInfo(hBuffer[i], &cursorInfo);
    }
}

void clearScreen() {
    COORD coord = {0, 0};
    DWORD dw;
    FillConsoleOutputCharacter(hBuffer[nScreenIndex], ' ', 80 * 25, coord, &dw);
}

void writeScreen(int x, int y, char *text) {
    COORD coord = {x, y};
    DWORD dw;

    SetConsoleCursorPosition(hBuffer[nScreenIndex], coord);
    WriteConsole(hBuffer[nScreenIndex], text, strlen(text), &dw, NULL);
}

void flipScreen() {
    SetConsoleActiveScreenBuffer(hBuffer[nScreenIndex]);
    nScreenIndex = !nScreenIndex;
}

void releaseScreen() {
    CloseHandle(hBuffer[0]);
    CloseHandle(hBuffer[1]);
}