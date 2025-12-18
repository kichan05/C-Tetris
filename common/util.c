//
// Created by 바키찬 on 2025-10-13.
//

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include "util.h"

void chomp(char *s) {
    s[strcspn(s, "\r\n")] = '\0';
}

void waiting() {
    printf("\nPress any key to go back to menu...");
    _getch();
}

char* fs(char *fmp, ...) {
    static char buffer[512];
    va_list args;
    va_start(args, fmp);
    vsnprintf(buffer, sizeof(buffer), fmp, args);
    va_end(args);

    return buffer;
}
