#ifndef ENTITIES_H
#define ENTITIES_H

#include "gba.h"
#include "images/background.h"
#include "images/player.h"
#include "images/red_coin.h"
#include "images/yellow_coin.h"

#define N_COINS 5

typedef struct entity {
    int x_pos, y_pos, x_vel, y_vel, x_axl, y_axl;
    int width, height;
    const u16 *image;
} entity;

struct entitystate {
    entity player;
    entity coins[N_COINS];
    entity evilcoin;
};

void reset_game(void);
void control_player(u32 previousButtons, u32 currentButtons);
void update_entities(void);
void do_collisions(void);
void draw_entities(void);
void draw_str(void);
void draw_score(void);

extern struct entitystate cs, ps;
extern int score;
extern int lost;

#endif