#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    REG_DISPCNT = MODE3 | BG2_ENABLE;

    u32 previousButtons = BUTTONS;
    u32 currentButtons = BUTTONS;

    enum gba_state state = STARTMENU;

    while (1) {
        currentButtons = BUTTONS;

        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
            state = STARTMENU;
        }

        switch (state) {
        case STARTMENU:
            menu_init();
            waitForVBlank();
            drawFullScreenImageDMA(menu_background);
            draw_buttons(&main_menu);
            main_menu.active = 1;
            state = MENU;
            break;
        case MENU:
            if (KEY_JUST_PRESSED(BUTTON_UP, currentButtons, previousButtons)) {
                menu_select(&main_menu, MENU_UP);
            }
            if (KEY_JUST_PRESSED(BUTTON_DOWN, currentButtons, previousButtons)) {
                menu_select(&main_menu, MENU_DOWN);
            }
            if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
                (*main_menu.selected->onclick)(&state);
            }
            volatile int dummy = randint(0, 5); // makes rand more random.
            UNUSED(dummy);
            waitForVBlank();
            draw_buttons(&main_menu);
            break;
        case ABOUTGAME:
            if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
                (*about_menu.selected->onclick)(&state);
            }
            waitForVBlank();
            drawImageDMA(HEIGHT / 4, WIDTH / 4, ABOUT_WIDTH, ABOUT_HEIGHT, about);
            draw_buttons(&about_menu);
            break;
        case STARTGAME:
            reset_game();
            waitForVBlank();
            drawFullScreenImageDMA(background);
            draw_str();
            draw_entities();
            state = PLAY;
            break;
        case PLAY:
            control_player(previousButtons, currentButtons);
            update_entities();
            do_collisions();

            waitForVBlank();
            draw_entities();

            if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons))
                state = PAUSE;
            if (score == N_COINS)
                state = WIN;
            if (lost)
                state = LOSE;
            break;
        case PAUSE:
            if (KEY_JUST_PRESSED(BUTTON_UP, currentButtons, previousButtons)) {
                menu_select(&pause_menu, MENU_UP);
            }
            if (KEY_JUST_PRESSED(BUTTON_DOWN, currentButtons, previousButtons)) {
                menu_select(&pause_menu, MENU_DOWN);
            }
            if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
                (*pause_menu.selected->onclick)(&state);
            }

            waitForVBlank();
            if (state == PLAY) {
                undrawImageDMA(HEIGHT / 4, WIDTH / 4, WIDTH / 2, HEIGHT / 2, background);
            } else {
                draw_menu(&pause_menu);
                draw_buttons(&pause_menu);
            }
            break;

        case WIN:
            if (KEY_JUST_PRESSED(BUTTON_UP, currentButtons, previousButtons)) {
                menu_select(&gameover_menu, MENU_UP);
            }
            if (KEY_JUST_PRESSED(BUTTON_DOWN, currentButtons, previousButtons)) {
                menu_select(&gameover_menu, MENU_DOWN);
            }
            if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
                (*gameover_menu.selected->onclick)(&state);
            }
            strcpy(gameover_menu.name, "You Win\0");

            waitForVBlank();
            draw_menu(&gameover_menu);
            draw_buttons(&gameover_menu);
            break;
        case LOSE:
            if (KEY_JUST_PRESSED(BUTTON_UP, currentButtons, previousButtons)) {
                menu_select(&gameover_menu, MENU_UP);
            }
            if (KEY_JUST_PRESSED(BUTTON_DOWN, currentButtons, previousButtons)) {
                menu_select(&gameover_menu, MENU_DOWN);
            }
            if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
                (*gameover_menu.selected->onclick)(&state);
            }
            strcpy(gameover_menu.name, "You Lose\0");

            waitForVBlank();
            draw_menu(&gameover_menu);
            draw_buttons(&gameover_menu);
            break;
        }

        ps = cs;
        previousButtons = currentButtons; 
    }

    return 0;
}
