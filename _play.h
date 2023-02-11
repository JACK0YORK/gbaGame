#ifndef _PLAY_H
#define _PLAY_H
#include "play.h"
#include "draw.h"

#define FLOOR_Y (2 * (HEIGHT)-20)
static void draw_player(entity *p);
static void update_entity(entity *e);
static void collide_evil(void);
static void collide_player(void);
static int collides_with(entity *o);
static void on_collide(entity *e);
static void smart_undraw(entity *old, entity *new);

#endif