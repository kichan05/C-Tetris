#include <stdio.h>
#include "color.h"

char* getBlockColorCode(int blockType) {
    switch (blockType) {
        case 1:
            return COLOR_CYAN;
        case 2:
            return COLOR_MAGENTA;
        case 3:
            return COLOR_GREEN;
        case 4:
            return COLOR_RED;
        case 5:
            return COLOR_ORANGE;
        case 6:
            return COLOR_BLUE;
        case 7:
            return COLOR_YELLOW;
    }
    return COLOR_YELLOW;
}
