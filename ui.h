//
// Created by 바키찬 on 2025-10-13.
//

#ifndef C_UI_H
#define C_UI_H

#include <Windows.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>

enum CURSOR_TYPE { HIDE, UNDERBAR, BLOCK };

int getWindowWidth();
int getWindowHeight();

int currentX();
int currentY();

void setCursor(enum CURSOR_TYPE curType);

void initScreen();
void clearScreen();
void writeScreen(int x, int y, char *text);
void flipScreen();
void releaseScreen();


#endif //C_UI_H
