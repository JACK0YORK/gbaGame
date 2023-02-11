#ifndef MENU_H
#define MENU_H

#include "state.h"
#include "main.h"

#define MENU_BG_COLOR COLOR(28,28,28)
#define MENU_TXT_COLOR BLACK
#define MENU_BTN_COLOR COLOR(20,20,20)
#define MENU_BTN_S_COLOR COLOR(31,31,20)

#define MENU_LEFT 0
#define MENU_RIGHT 1
#define MENU_UP 2
#define MENU_DOWN 3

#define MAX_BUTTONS 2

struct button {
    int x, y, w, h;
    int focus;
    struct button *neighbors[4];
    void (*onclick)(gba_state *state);
    char text[25];
};

struct menustate
{
    struct button *selected;
    struct button buttons[3];
    char name[28];
    int active;
};


extern struct menustate main_menu, pause_menu, about_menu, gameover_menu;
extern int startGame;

void menu_select(struct menustate *state, int direction);
void menu_init(void);
void draw_menu(struct menustate *mstate);
void draw_buttons(struct menustate *mstate);

#endif 