//
// Created by 바키찬 on 2025-12-22.
//

#ifndef C_TETRIS_MAINSCENE_H
#define C_TETRIS_MAINSCENE_H
#include <windows.h>
#include "../common/color.h"
#include "../ui.h"
#include "../common/util.h"
#include "../common/key.h"
#include "../block.h"
#include "./gameResultScene.h"
#include "./../uiConfig.h"
#include "./../CircularQueue.h"

void initMap();

int isMoveAble(int x, int y, int blockType, int blockRotate);
int isMoveAbleWrap(int x, int y, int blockType, int blockRotate);

void printMap(UiConfig *uiConfig);
void printPlayerBlock(COORD *position, Block *b, UiConfig *uiConfig);
void printPhaseBlock(COORD *position, int phaseY, Block *b, UiConfig *uiConfig);
void printHoldBlock(int holdBlockType, UiConfig* uiConfig);
void printNextBlockList(CircularQueue* nextBlockQueue, UiConfig* uiConfig);
void printMapBoard(UiConfig* uiConfig);

int isFullLine(int line);
int isAnyBlockInLine(int line);


void lineCopyPasse(int copyLine, int pastLine);
void lineFillBlank(int line);
void playerBlockToMapBlock(int x, int y, Block b);

void readNextBlock(COORD* position, int* blockType, int* blockRotate, int* downDump, int* bottomDump);

void mainScene();


#endif //C_TETRIS_MAINSCENE_H
