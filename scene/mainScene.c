//
// Created by 바키찬 on 2025-12-22.
//

#include "mainScene.h"

int map[MAP_HEIGHT][MAP_WIDTH];
static int IS_DEBUG = 0;

int isMoveAble(int x, int y, int blockType, int blockRotate) {
    Block block = BLOCK_TEMPLATE[blockType][blockRotate];

    if (x < 0)
        return 0;

    if (x + block.width > MAP_WIDTH)
        return 0;

    if (y + block.height > MAP_HEIGHT)
        return 0;

    for (int by = 0; by < block.height; by++) {
        for (int bx = 0; bx < block.width; bx++) {
            if (block.shape[by][bx] == 0)
                continue;

            if (map[y + by][x + bx])
                return 0;
        }
    }

    return 1;
}

int isMoveAbleWrap(int x, int y, int blockType, int blockRotate) {
    int res = isMoveAble(x, y, blockType, blockRotate);

    if (IS_DEBUG) {
        if (res) {
            writeScreen(0, MAP_HEIGHT + 1, COLOR_GREEN "move able" COLOR_RESET);
        } else {
            writeScreen(0, MAP_HEIGHT + 1, COLOR_RED "move unable" COLOR_RESET);
        }
    }

    return res;
}

void printMap() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            writeScreen(
                    x, y,
                    map[y][x] == 0 ? BLANK : fs("%s%s%s", getBlockColorCode(map[y][x]), BLOCK, COLOR_RESET)
            );
        }
    }
}

void printPlayerBlock(COORD *position, Block *b) {
    for (int y = 0; y < b->height; y++) {
        for (int x = 0; x < b->width; x++) {
            if (b->shape[y][x]) {
                writeScreen(position->X + x, position->Y + y,
                            fs("%s%s%s", getBlockColorCode(b->shape[y][x]), BLOCK, COLOR_RESET));
            }
        }
    }
}

void printPhaseBlock(COORD *position, int phaseY, Block *b) {
    for (int y = 0; y < b->height; y++) {
        for (int x = 0; x < b->width; x++) {
            if (b->shape[y][x]) {
                writeScreen(position->X + x, phaseY + y,
                            fs("%s%s%s", COLOR_WHITE, PHASE_BLOCK, COLOR_RESET));
            }
        }
    }
}

int isFullLine(int line) {
    for (int x = 0; x < MAP_WIDTH; x++) {
        if(!map[line][x]){
            return 0;
        }
    }
    return 1;
}

void playerBlockToMapBlock(int x, int y, Block b) {
    for (int by = 0; by < b.height; by++) {
        for (int bx = 0; bx < b.width; bx++) {
            if(b.shape[by][bx]) {
                map[y + by][x + bx] = b.shape[by][bx];
            }
        }
    }
}

void lineCopyPasse(int copyLine, int pastLine) {
    for (int x = 0; x < MAP_WIDTH; x++) {
        map[pastLine][x] = map[copyLine][x];
    }
}

void lineFillBlank(int line) {
    for (int x = 0; x < MAP_WIDTH; x++) {
        map[line][x] = 0;
    }
}

void readNextBlock(COORD* position, int* blockType, int* blockRotate, int* downDump, int* bottomDump) {
    position->X = MAP_WIDTH / 2;
    position->Y = 0;

    *blockType = randomInt(0, BLOCK_TYPE_COUNT);
    *blockRotate = 0;
    *downDump = 0;
    *bottomDump = 0;
}

void mainScene() {
    COORD position = {0, 0};
    int score = 0;
    int blockRotate = 0;
    int blockType = 0;
    int downDump = 0;
    int bottomDump = 0;

    readNextBlock(&position, &blockType, &blockRotate, &downDump, &bottomDump);

    while (1) {
        clearScreen();

        Block b = BLOCK_TEMPLATE[blockType][blockRotate];

        writeScreen(0, MAP_HEIGHT + 1, fs("X : %d   \tY : %d", position.X, position.Y));
        writeScreen(0, MAP_HEIGHT + 2, fs("BlockType: %d\tBlockRotate : %d", blockType, blockRotate));
        writeScreen(0, MAP_HEIGHT + 3, fs("%sScore: %d%s", COLOR_YELLOW, score, COLOR_RESET));

        int phaseY = position.Y;
        while (isMoveAbleWrap(position.X, phaseY + 1, blockType, blockRotate)) {
            phaseY += 1;
        }

        printMap();
        printPhaseBlock(&position, phaseY, &b);
        printPlayerBlock(&position, &b);

        if (isKeyDown(VK_LEFT)) {
            if (isMoveAbleWrap(position.X - 1, position.Y, blockType, blockRotate)) {
                position.X -= 1;
                downDump = 0;
                bottomDump = 0;
            }
        }
        else {
            downDump += 1;
        }

        if (isKeyDown(VK_RIGHT)) {
            if (isMoveAbleWrap(position.X + 1, position.Y, blockType, blockRotate)) {
                position.X += 1;
                downDump = 0;
                bottomDump = 0;
            }
        }
        else {
            downDump += 1;
        }

        if (isKeyDown(VK_DOWN)) {
            if (isMoveAbleWrap(position.X, position.Y + 1, blockType, blockRotate)) {
                position.Y += 1;
                downDump = 0;
                bottomDump = 0;
            }
        }
        else {
            downDump += 1;
        }

        if (isKeyDowned(VK_UP)) {
            if (isMoveAbleWrap(position.X, position.Y, blockType, (blockRotate + 1) % 4)) {
                blockRotate = (blockRotate + 1) % 4;
                downDump = 0;
                bottomDump = 0;
            }
        }
        else {
            downDump += 1;
        }

        if (isKeyDowned(VK_SPACE)) {
            playerBlockToMapBlock(position.X, phaseY, b);
            readNextBlock(&position, &blockType, &blockRotate, &downDump, &bottomDump);
        }

        if(downDump >= 5){
            if(isMoveAbleWrap(position.X, position.Y + 1, blockType, blockRotate)) {
                position.Y += 1;
                downDump = 0;
            }
            else {
                bottomDump += 1;
            }

            if(bottomDump > 2) {
                playerBlockToMapBlock(position.X, position.Y, b);
                readNextBlock(&position, &blockType, &blockRotate, &downDump, &bottomDump);
            }
        }

        for (int y = 0; y < MAP_HEIGHT; ++y) {
            if(isFullLine(y)) {
                for (int i = y; i >= 1; i--) {
                    lineCopyPasse(i - 1, i);
                }

                lineFillBlank(0);
                score += 1;
            }
        }

        flipScreen();
        Sleep(60);
    }
}
