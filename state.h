#ifndef STATE_H
#define STATE_H
typedef enum gba_state {
    STARTMENU,
    MENU,
    ABOUTGAME,
    STARTGAME,
    PLAY,
    PAUSE,
    WIN,
    LOSE,
} gba_state;
#endif