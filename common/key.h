#ifndef C_PLAYLIST_KEY_H
#define C_PLAYLIST_KEY_H

typedef enum {
    KEY_UNKNOWN = -1,

    KEY_UP = 72,
    KEY_DOWN = 80,
    KEY_LEFT = 75,
    KEY_RIGHT = 77,

    KEY_HOME = 71,
    KEY_END = 79,
    KEY_PAGE_UP = 73,
    KEY_PAGE_DOWN = 81,

    KEY_ENTER = '\r',
    KEY_BACKSPACE = 8,

    KEY_SAVE = 19,   // Ctrl+S
    KEY_QUIT = 17    // Ctrl+Q
} KeyCode;

int getKeyPress();

#endif //C_PLAYLIST_KEY_H
