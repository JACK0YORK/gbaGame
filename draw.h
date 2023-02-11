#include "gba.h"
#include "play.h"

void drawImageLineDMA(int row, int col, int width, const u16 *image);
void drawImageLineDMA_r(int row, int col, int width, const u16 *image);
void draw_coin(entity *c);
void draw_player_facing_left(entity *p);
void draw_player_facing_right(entity *p);