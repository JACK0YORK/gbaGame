#include "menu.h"
#include "draw.h"
#include "state.h"
#include <string.h>

struct menustate main_menu, pause_menu, about_menu, gameover_menu;
void draw_button(struct button *b);

int startGame = 0;

void start_game(gba_state *state) { *state = STARTGAME; }

void about_game(gba_state *state) { *state = ABOUTGAME; }

void resume_game(gba_state *state) {
    undrawImageDMA(HEIGHT / 4, WIDTH / 4, WIDTH / 2, HEIGHT / 2, background);
    *state = PLAY;
}

void restart(gba_state *state) { *state = STARTMENU; }

void init_btn(struct button *b, char *text, int offx, int offy,
              void (*onclick)(enum gba_state *)) {
    strcpy(b->text, text);
    b->h = 10;
    b->w = strlen(text) * 7 + 1;
    b->x = (WIDTH - b->w) / 2 + offx;
    b->y = (HEIGHT - b->h) / 2 + offy;
    b->onclick = onclick;
    b->focus = 0;
    b->neighbors[0] = 0;
    b->neighbors[1] = 0;
    b->neighbors[2] = 0;
    b->neighbors[3] = 0;
}

void menu_init(void) {
    startGame = 0;

    strcpy(main_menu.name, "Go for Gold\0");
    main_menu.selected = &main_menu.buttons[0];
    init_btn(&main_menu.buttons[0], "Play\0", 0, 0, &start_game);
    init_btn(&main_menu.buttons[1], "About\0", 0, 15, &about_game);
    main_menu.buttons[0].focus = 1;
    main_menu.buttons[0].neighbors[MENU_DOWN] = &main_menu.buttons[1];
    main_menu.buttons[1].neighbors[MENU_UP] = &main_menu.buttons[0];
    main_menu.active = 0;

    strcpy(pause_menu.name, "Paused\0");
    pause_menu.selected = &pause_menu.buttons[0];
    init_btn(&pause_menu.buttons[0], "Resume\0", 0, 0, &resume_game);
    init_btn(&pause_menu.buttons[1], "Menu\0", 0, 15, &restart);
    pause_menu.buttons[0].focus = 1;
    pause_menu.buttons[0].neighbors[MENU_DOWN] = &pause_menu.buttons[1];
    pause_menu.buttons[1].neighbors[MENU_UP] = &pause_menu.buttons[0];
    pause_menu.active = 0;

    strcpy(about_menu.name, "About\0");
    about_menu.selected = &about_menu.buttons[0];
    init_btn(&about_menu.buttons[0], "Menu\0", 0, 30, &restart);
    about_menu.buttons[0].focus = 1;
    about_menu.active = 0;

    strcpy(gameover_menu.name, "Game Over\0");
    gameover_menu.selected = &gameover_menu.buttons[0];
    init_btn(&gameover_menu.buttons[0], "Retry\0", 0, 0, &start_game);
    init_btn(&gameover_menu.buttons[1], "Menu\0", 0, 15, &restart);
    gameover_menu.buttons[0].focus = 1;
    gameover_menu.buttons[0].neighbors[MENU_DOWN] = &gameover_menu.buttons[1];
    gameover_menu.buttons[1].neighbors[MENU_UP] = &gameover_menu.buttons[0];
    gameover_menu.active = 0;
}

void menu_select(struct menustate *state, int direction) {
    if (state->selected->neighbors[direction]) {
        state->selected->focus = 0;
        state->selected = state->selected->neighbors[direction];
        state->selected->focus = 1;
    }
}

void draw_menu(struct menustate *mstate) {
    drawRectDMA(HEIGHT / 4, WIDTH / 4 + 15, WIDTH / 2 - 30, HEIGHT / 2 - 13, MENU_BG_COLOR);
    drawCenteredString(HEIGHT / 4 - 30, WIDTH / 4, WIDTH / 2, HEIGHT / 2, mstate->name, MENU_TXT_COLOR);
}

void draw_buttons(struct menustate *mstate) {
    for (int i = 0; i < MAX_BUTTONS; i++) {
        struct button *b = &mstate->buttons[i];
        if (b->focus)
            drawRectDMA(b->y, b->x, b->w, b->h, MENU_BTN_S_COLOR);
        else
            drawRectDMA(b->y, b->x, b->w, b->h, MENU_BTN_COLOR);
        drawCenteredString(b->y, b->x, b->w, b->h, b->text, MENU_TXT_COLOR);
    }
}