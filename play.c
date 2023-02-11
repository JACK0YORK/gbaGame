#include "play.h"
#include "_play.h"

struct entitystate ps, cs;

char str[] = "Coins: 0/5\0";
int jumps = 2;
int score = 0;
int lost = 0;
int player_direction = 1;

int evil_x_vel[] = {-3, -3, -1, -1, 1, 1, 3, 3};
int evil_y_vel[] = {-1, 1, -3, 3, -3, 3, -1, 1};

void reset_game(void) {
    player_direction = 1;
    jumps = 2;
    score = 0;
    lost = 0;
    str[7] = '0';

    cs.player.x_pos = WIDTH - (PLAYER_WIDTH * 2);
    cs.player.y_pos = FLOOR_Y - (PLAYER_HEIGHT * 2);
    cs.player.x_vel = 0;
    cs.player.y_vel = 0;
    cs.player.x_axl = 0;
    cs.player.y_axl = 1;
    cs.player.width = (PLAYER_WIDTH * 2);
    cs.player.height = (PLAYER_HEIGHT * 2);
    cs.player.image = player;

    for (int i = 0; i < N_COINS; i++) {
        cs.coins[i].x_pos = randint(0, 2 * (WIDTH - (PLAYER_WIDTH * 2)));
        cs.coins[i].y_pos = randint(35, FLOOR_Y - 2 * PLAYER_HEIGHT);
        cs.coins[i].x_vel = 0;
        cs.coins[i].y_vel = 0;
        cs.coins[i].x_axl = 0;
        cs.coins[i].y_axl = 0;
        cs.coins[i].height = (PLAYER_WIDTH * 2);
        cs.coins[i].width = (PLAYER_WIDTH * 2);
        cs.coins[i].image = yellow_coin;
    }

    cs.evilcoin.x_pos = randint(0, 2 * (WIDTH - (PLAYER_WIDTH * 2)));
    cs.evilcoin.y_pos = randint(0, FLOOR_Y / 2);
    int evilvel = randint(0, 7);
    cs.evilcoin.x_vel = evil_x_vel[evilvel];
    cs.evilcoin.y_vel = evil_y_vel[evilvel];
    cs.evilcoin.x_axl = 0;
    cs.evilcoin.y_axl = 0;
    cs.evilcoin.height = (PLAYER_WIDTH * 2);
    cs.evilcoin.width = (PLAYER_WIDTH * 2);
    cs.evilcoin.image = red_coin;

    ps = cs;
}

static void draw_player(entity *p) {
    if (player_direction)
        draw_player_facing_right(p);
    else
        draw_player_facing_left(p);
}

void update_entities(void) {
    if (cs.player.x_vel >= 5 && cs.player.x_axl > 0)
        cs.player.x_axl = 0;
    if (cs.player.x_vel <= -5 && cs.player.x_axl < 0)
        cs.player.x_axl = 0;
    update_entity(&cs.player);
    // coins dont move.
    update_entity(&cs.evilcoin);
}

static void update_entity(entity *e) {
    e->x_pos = e->x_pos + e->x_vel;
    e->y_pos = e->y_pos + e->y_vel;
    e->x_vel = e->x_vel + e->x_axl;
    e->y_vel = e->y_vel + e->y_axl;
}

void control_player(u32 previousButtons, u32 currentButtons) {
    int moving_x = 0;
    int moving_y = 0;

    if (KEY_DOWN(BUTTON_LEFT, currentButtons)) {
        if (cs.player.x_vel > -5)
            cs.player.x_axl = -1;
        else
            cs.player.x_axl = 0;
        if (cs.player.x_pos <= 0) {
            cs.player.y_vel = 1;
        }
        moving_x--;
    }
    if (KEY_DOWN(BUTTON_RIGHT, currentButtons)) {
        if (cs.player.x_vel < 5)
            cs.player.x_axl = 1;
        else
            cs.player.x_axl = 0;
        if (cs.player.x_pos >= WIDTH * 2 - cs.player.width) {
            cs.player.y_vel = 1;
        }
        moving_x++;
    }
    if (KEY_JUST_PRESSED(BUTTON_UP, currentButtons, previousButtons)) {
        if (cs.player.y_pos == FLOOR_Y - (2 * PLAYER_HEIGHT))
            jumps = 2;
        else if (cs.player.x_pos >= WIDTH * 2 - cs.player.width ||
                 cs.player.x_pos <= 0)
            jumps = 1;
        if (jumps > 0) {
            cs.player.y_vel = -12;
            if (cs.player.x_pos >= WIDTH * 2 - cs.player.width) {
                cs.player.x_vel = -4;
            } else if (cs.player.x_pos <= 0) {
                cs.player.x_vel = 4;
            } else {
                jumps--;
            }
        }
        moving_y--;
    }
    if (!moving_x) {
        if (cs.player.y_pos == FLOOR_Y - (2 * PLAYER_HEIGHT)) {
            cs.player.x_axl = 0;
            cs.player.x_vel = cs.player.x_vel / 2;
        }
    } else {
        if (moving_x > 0)
            player_direction = 1;
        else
            player_direction = 0;
    }

    if (cs.player.x_vel < -5)
        cs.player.x_vel = -5;
    if (cs.player.x_vel > 5)
        cs.player.x_vel = 5;
}

void do_collisions(void) {
    collide_player();
    collide_evil();
}

static void collide_evil(void) {
    if (cs.evilcoin.y_pos > FLOOR_Y - (2 * RED_COIN_HEIGHT)) {
        cs.evilcoin.y_pos = FLOOR_Y - (2 * RED_COIN_HEIGHT);
        cs.evilcoin.y_vel = -cs.evilcoin.y_vel;
        cs.evilcoin.x_vel = cs.evilcoin.x_vel + randint(-2, 2);
    }
    if (cs.evilcoin.y_pos < 0) {
        cs.evilcoin.y_pos = 0;
        cs.evilcoin.y_vel = -cs.evilcoin.y_vel;
        cs.evilcoin.x_vel = cs.evilcoin.x_vel + randint(-2, 2);
    }
    if (cs.evilcoin.x_pos > WIDTH * 2 - cs.evilcoin.width) {
        cs.evilcoin.x_pos = WIDTH * 2 - cs.evilcoin.width;
        cs.evilcoin.x_vel = -cs.evilcoin.x_vel;
        cs.evilcoin.y_vel = cs.evilcoin.y_vel + randint(-2, 2);
    }
    if (cs.evilcoin.x_pos < 0) {
        cs.evilcoin.x_pos = 0;
        cs.evilcoin.x_vel = -cs.evilcoin.x_vel;
        cs.evilcoin.y_vel = cs.evilcoin.y_vel + randint(-2, 2);
    }
    if (cs.evilcoin.x_vel > 5)
        cs.evilcoin.x_vel = 5;
    if (cs.evilcoin.x_vel < -5)
        cs.evilcoin.x_vel = -5;
    if (cs.evilcoin.y_vel > 5)
        cs.evilcoin.y_vel = 5;
    if (cs.evilcoin.y_vel < -5)
        cs.evilcoin.y_vel = -5;
}

static void collide_player(void) {
    // walls and Floor
    if (cs.player.y_pos > FLOOR_Y - (2 * PLAYER_HEIGHT)) {
        cs.player.y_pos = FLOOR_Y - (2 * PLAYER_HEIGHT);
        cs.player.y_vel = 1;
    }
    if (cs.player.y_pos < 0) {
        cs.player.y_pos = 0;
        cs.player.y_vel = -cs.player.y_vel / 4;
    }
    if (cs.player.x_pos > WIDTH * 2 - cs.player.width) {
        cs.player.x_pos = WIDTH * 2 - cs.player.width;
    }
    if (cs.player.x_pos < 0) {
        cs.player.x_pos = 0;
    }
    // yellow coins
    for (int i = 0; i < N_COINS; i++) {
        entity *o = &cs.coins[i];
        if (collides_with(o)) {
            on_collide(o);
        }
    }

    // red coin(s)
    if (collides_with(&cs.evilcoin)) {
        lost = 1;
    }
}

static int collides_with(entity *o) {
    int left_collide = (o->x_pos > cs.player.x_pos) &&
                       (o->x_pos < cs.player.x_pos + cs.player.width);
    int right_collide =
        (o->x_pos + o->width > cs.player.x_pos) &&
        (o->x_pos + o->width < cs.player.x_pos + cs.player.width);
    int up_collide = (o->y_pos > cs.player.y_pos) &&
                     (o->y_pos < cs.player.y_pos + cs.player.height);
    int down_collide =
        (o->y_pos + o->height > cs.player.y_pos) &&
        (o->y_pos + o->height < cs.player.y_pos + cs.player.height);
    return (left_collide || right_collide) && (up_collide || down_collide);
}

static void on_collide(entity *e) {
    e->y_pos = -10 - e->height; // place off-screen
    score++;
    str[7] = (score) + '0';
}

void draw_entities(void) {
    for (int i = 0; i < N_COINS; i++) {
        smart_undraw(&ps.coins[i], &cs.coins[i]);
    }
    smart_undraw(&ps.evilcoin, &cs.evilcoin);
    smart_undraw(&ps.player, &cs.player);
    undrawImageDMA(HEIGHT - 10, 132, 6, 8, background);


    for (int i = 0; i < N_COINS; i++) {
        draw_coin(&cs.coins[i]);
    }
    draw_player(&cs.player);
    draw_coin(&cs.evilcoin);
    draw_score();
}

static void smart_undraw(entity *old, entity *new) {
    int dx = new->x_pos - old->x_pos;
    int dy = new->y_pos - old->y_pos;
    if (dx == 0 && dy == 0)
        return;
    undrawImageDMA(old->y_pos / 2, old->x_pos / 2, old->width / 2, old->height / 2, background);
}

void draw_score(void) {
    drawChar(HEIGHT - 9, 132, str[7], WHITE);
}

void draw_str(void) {
    drawCenteredString(HEIGHT - 10, 0, WIDTH, 10, str, WHITE);
}