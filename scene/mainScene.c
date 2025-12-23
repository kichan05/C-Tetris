//
// Created by 바키찬 on 2025-12-22.
//

#include "mainScene.h"

int map[MAP_HEIGHT][MAP_WIDTH];
static int IS_DEBUG = 0;

void initMap() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map[y][x] = 0;
        }
    }
}

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

void printMap(UiConfig *uiConfig) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            writeScreen(
                    x + uiConfig->leftPadding, y,
                    map[y][x] == 0 ? BLANK : fs("%s%s%s", getBlockColorCode(map[y][x]), BLOCK, COLOR_RESET)
            );
        }
    }
}

void printPlayerBlock(COORD *position, Block *b, UiConfig *uiConfig) {

    for (int y = 0; y < b->height; y++) {
        for (int x = 0; x < b->width; x++) {
            if (b->shape[y][x]) {
                writeScreen(position->X + x + uiConfig->leftPadding, position->Y + y,
                            fs("%s%s%s", getBlockColorCode(b->shape[y][x]), BLOCK, COLOR_RESET));
            }
        }
    }
}

void printPhaseBlock(COORD *position, int phaseY, Block *b, UiConfig *uiConfig) {
    for (int y = 0; y < b->height; y++) {
        for (int x = 0; x < b->width; x++) {
            if (b->shape[y][x]) {
                writeScreen(position->X + x + uiConfig->leftPadding, phaseY + y,
                            fs("%s%s%s", COLOR_WHITE, PHASE_BLOCK, COLOR_RESET));
            }
        }
    }
}

void printHoldBlock(int holdBlockType, UiConfig *uiConfig) {
    int anchorX = uiConfig->leftPadding - 1 - 15;

    char *title = "Hold Block";
    int titleLen = strlen(title);
    writeScreen(anchorX, 0, fs("%s%s%s", COLOR_GREEN, title, COLOR_RESET));

    if (holdBlockType == -1) {
        char* message = "Press C, hold block";
        int messageLen = strlen(message);

        writeScreen(anchorX + titleLen - messageLen, 2, fs("%s%s%s", COLOR_ORANGE, message, COLOR_RESET));
        return;
    }

    Block b = BLOCK_TEMPLATE[holdBlockType][0];
    int blockPadding = (titleLen - b.width) / 2;

    for (int y = 0; y < b.height; y++) {
        for (int x = 0; x < b.width; x++) {
            if (b.shape[y][x]) {
                writeScreen(
                        anchorX + blockPadding + x,
                        2 + y,
                        fs("%s%s%s", getBlockColorCode(b.shape[y][x]), BLOCK, COLOR_RESET)
                );
            }
        }
    }
}

void printNextBlockList(CircularQueue* nextBlockQueue, UiConfig* uiConfig) {
    int anchorX = uiConfig->leftPadding + MAP_WIDTH + 1;
    writeScreen(anchorX, 0, "Next Block");
    for (int i = 0; i < NEXT_BLOCK_QUEUE_SIZE; ++i) {
        Block b = BLOCK_TEMPLATE[getValueOfIndex(nextBlockQueue, i)][0];

        for (int y = 0; y < b.height; y++) {
            for (int x = 0; x < b.width; x++) {
                if (b.shape[y][x]) {
                    writeScreen(anchorX + x, 2 + 5 * i + y,
                                fs("%s%s%s", getBlockColorCode(b.shape[y][x]), BLOCK, COLOR_RESET));
                }
            }
        }
    }
}

void printMapBoard(UiConfig *uiConfig) {
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        writeScreen(uiConfig->leftPadding - 1, y, BLOCK);
        writeScreen(uiConfig->leftPadding + MAP_WIDTH, y, BLOCK);
    }

    for (int x = -1; x < MAP_WIDTH + 1; ++x) {
        writeScreen(uiConfig->leftPadding + x, MAP_HEIGHT, BLOCK);
    }
}

int isFullLine(int line) {
    for (int x = 0; x < MAP_WIDTH; x++) {
        if (!map[line][x]) {
            return 0;
        }
    }
    return 1;
}

int isAnyBlockInLine(int line) {
    for (int x = 0; x < MAP_WIDTH; x++) {
        if (map[line][x]) {
            return 1;
        }
    }
    return 0;
}

void playerBlockToMapBlock(int x, int y, Block b) {
    for (int by = 0; by < b.height; by++) {
        for (int bx = 0; bx < b.width; bx++) {
            if (b.shape[by][bx]) {
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

void readNextBlock(COORD *position, int *blockType, int *blockRotate, int *downDump, int *bottomDump) {
    position->X = MAP_WIDTH / 2;
    position->Y = 0;

    *blockType = randomInt(0, BLOCK_TYPE_COUNT);
    *blockRotate = 0;
    *downDump = 0;
    *bottomDump = 0;
}

void mainScene() {
    initMap();

    UiConfig uiConfig = {
            (getWindowWidth() - MAP_WIDTH) / 2,
    };

    COORD position = {0, 0};

    CircularQueue nextBlockQueue = {
            0,
            0,
            0,
    };

    for (int i = 0; i < NEXT_BLOCK_QUEUE_SIZE; ++i) {
        enqueue(&nextBlockQueue, randomInt(0, BLOCK_TYPE_COUNT));
    }

    int score = 0;
    int blockRotate = 0;
    int blockType = 0;
    int downDump = 0;
    int bottomDump = 0;
    int holdBlockType = -1;

    readNextBlock(&position, &blockType, &blockRotate, &downDump, &bottomDump);

    while (1) {
        clearScreen();

        if (isAnyBlockInLine(0)) {
            gameResultScene(score);
            return;
        }

        Block b = BLOCK_TEMPLATE[blockType][blockRotate];

        writeHorizontalCenter(MAP_HEIGHT + 1, fs("X : %d   \tY : %d", position.X, position.Y));
        writeHorizontalCenter(MAP_HEIGHT + 2, fs("BlockType: %d\tBlockRotate : %d", blockType, blockRotate));
        writeHorizontalCenter(MAP_HEIGHT + 3, fs("%sScore: %d%s", COLOR_YELLOW, score, COLOR_RESET));

        int phaseY = position.Y;
        while (isMoveAbleWrap(position.X, phaseY + 1, blockType, blockRotate)) {
            phaseY += 1;
        }

        printMapBoard(&uiConfig);
        printMap(&uiConfig);
        printPhaseBlock(&position, phaseY, &b, &uiConfig);
        printHoldBlock(holdBlockType, &uiConfig);
        printNextBlockList(&nextBlockQueue, &uiConfig);
        printPlayerBlock(&position, &b, &uiConfig);

        if (isKeyDown(VK_LEFT)) {
            if (isMoveAbleWrap(position.X - 1, position.Y, blockType, blockRotate)) {
                position.X -= 1;
                downDump = 0;
                bottomDump = 0;
            }
        } else {
            downDump += 1;
        }

        if (isKeyDown(VK_RIGHT)) {
            if (isMoveAbleWrap(position.X + 1, position.Y, blockType, blockRotate)) {
                position.X += 1;
                downDump = 0;
                bottomDump = 0;
            }
        } else {
            downDump += 1;
        }

        if (isKeyDown(VK_DOWN)) {
            if (isMoveAbleWrap(position.X, position.Y + 1, blockType, blockRotate)) {
                position.Y += 1;
                downDump = 0;
                bottomDump = 0;
            }
        } else {
            downDump += 1;
        }

        if (isKeyDowned(VK_UP)) {
            if (isMoveAbleWrap(position.X, position.Y, blockType, (blockRotate + 1) % 4)) {
                blockRotate = (blockRotate + 1) % 4;
                downDump = 0;
                bottomDump = 0;
            }
        } else {
            downDump += 1;
        }

        if (isKeyDowned(VK_SPACE)) {
            playerBlockToMapBlock(position.X, phaseY, b);
            readNextBlock(&position, &blockType, &blockRotate, &downDump, &bottomDump);
        }

        if (isKeyDowned('C')) {
            position.X = MAP_WIDTH / 2;
            position.Y = 0;

            if (holdBlockType == -1) {
                holdBlockType = blockType;
                blockType = randomInt(0, BLOCK_TYPE_COUNT);
            } else {
                int temp = blockType;
                blockType = holdBlockType;
                holdBlockType = temp;
            }

            blockRotate = 0;
            downDump = 0;
            bottomDump = 0;
        }


        if (downDump >= 5) {
            if (isMoveAbleWrap(position.X, position.Y + 1, blockType, blockRotate)) {
                position.Y += 1;
                downDump = 0;
            } else {
                bottomDump += 1;
            }

            if (bottomDump > 2) {
                playerBlockToMapBlock(position.X, position.Y, b);
                readNextBlock(&position, &blockType, &blockRotate, &downDump, &bottomDump);
            }
        }

        for (int y = 0; y < MAP_HEIGHT; ++y) {
            if (isFullLine(y)) {
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
