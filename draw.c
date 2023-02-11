#include "draw.h"



void drawImageLineDMA(int row, int col, int width, const u16 *image){
  DMA[3].src = image;
  DMA[3].dst = &videoBuffer[OFFSET(row, col, WIDTH)];
  DMA[3].cnt = width | DMA_ON | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT;
}

void drawImageLineDMA_r(int row, int col, int width, const u16 *image){
  DMA[3].src = image;
  DMA[3].dst = &videoBuffer[OFFSET(row, col + width-1, WIDTH)];
  DMA[3].cnt = width | DMA_ON | DMA_SOURCE_INCREMENT | DMA_DESTINATION_DECREMENT;
}

void draw_coin(entity *c) {
    drawImageLineDMA(c->y_pos / 2, c->x_pos / 2 + 2, 4, c->image + OFFSET(0, 2, 8));
    drawImageLineDMA(c->y_pos / 2 + 1, c->x_pos / 2 + 1, 6, c->image + OFFSET(1, 1, 8));
    drawImageDMA(c->y_pos / 2 + 2, c->x_pos / 2, 8, 4, c->image + OFFSET(2, 0, 8));
    drawImageLineDMA(c->y_pos / 2 + 6, c->x_pos / 2 + 1, 6, c->image + OFFSET(6, 1, 8));
    drawImageLineDMA(c->y_pos / 2 + 7, c->x_pos / 2 + 2, 4, c->image + OFFSET(7, 2, 8));
}

void draw_player_facing_right(entity *p) {
    drawImageLineDMA(p->y_pos / 2, p->x_pos / 2 + 1, 7, p->image + OFFSET(0, 1, 8));
    setPixel(p->y_pos / 2, p->x_pos / 2 + 4, background[OFFSET(p->y_pos / 2, p->x_pos / 2 + 4, WIDTH)]);
    // setPixel(p->y_pos / 2, p->x_pos / 2+5, background[OFFSET(p->y_pos / 2,p->x_pos / 2+5,WIDTH)]);
    drawImageLineDMA(p->y_pos / 2 + 1, p->x_pos / 2, 7, p->image + OFFSET(1, 0, 8));
    drawImageLineDMA(p->y_pos / 2 + 2, p->x_pos / 2, 6, p->image + OFFSET(2, 0, 8));
    drawImageLineDMA(p->y_pos / 2 + 3, p->x_pos / 2, 7, p->image + OFFSET(3, 0, 8));
    drawImageLineDMA(p->y_pos / 2 + 4, p->x_pos / 2, 8, p->image + OFFSET(4, 0, 8));
    drawImageLineDMA(p->y_pos / 2 + 5, p->x_pos / 2, 8, p->image + OFFSET(5, 0, 8));
    drawImageLineDMA(p->y_pos / 2 + 6, p->x_pos / 2, 8, p->image + OFFSET(6, 0, 8));
    drawImageLineDMA(p->y_pos / 2 + 7, p->x_pos / 2, 8, p->image + OFFSET(7, 0, 8));
    drawImageLineDMA(p->y_pos / 2 + 8, p->x_pos / 2, 8, p->image + OFFSET(8, 0, 8));
    drawImageLineDMA(p->y_pos / 2 + 9, p->x_pos / 2, 7, p->image + OFFSET(9, 0, 8));
    drawImageLineDMA(p->y_pos / 2 + 10, p->x_pos / 2, 7, p->image + OFFSET(10, 0, 8));
    drawImageLineDMA(p->y_pos / 2 + 11, p->x_pos / 2, 7, p->image + OFFSET(11, 0, 8));
    drawImageLineDMA(p->y_pos / 2 + 12, p->x_pos / 2 + 1, 5, p->image + OFFSET(12, 1, 8));
    drawImageLineDMA(p->y_pos / 2 + 13, p->x_pos / 2 + 1, 5, p->image + OFFSET(13, 1, 8));
    drawImageLineDMA(p->y_pos / 2 + 14, p->x_pos / 2 + 1, 5, p->image + OFFSET(14, 1, 8));
    setPixel(p->y_pos / 2 + 13, p->x_pos / 2 + 3, background[OFFSET(p->y_pos / 2 + 13, p->x_pos / 2 + 3, WIDTH)]);
    setPixel(p->y_pos / 2 + 14, p->x_pos / 2 + 3, background[OFFSET(p->y_pos / 2 + 14, p->x_pos / 2 + 3, WIDTH)]);
    drawImageLineDMA(p->y_pos / 2 + 15, p->x_pos / 2, 8, p->image + OFFSET(15, 0, 8));
    setPixel(p->y_pos / 2 + 15, p->x_pos / 2 + 3, background[OFFSET(p->y_pos / 2 + 15, p->x_pos / 2 + 3, WIDTH)]);
    // drawImageLineDMA(p->y_pos / 2+3, p->x_pos / 2, 7, p->image + OFFSET(3,0,8));
}
void draw_player_facing_left(entity *p) {
    drawImageLineDMA_r(p->y_pos / 2, p->x_pos / 2, 7, p->image + OFFSET(0, 1, 8));
    setPixel(p->y_pos / 2, p->x_pos / 2 + 3, background[OFFSET(p->y_pos / 2, p->x_pos / 2 + 3, WIDTH)]);
    // setPixel(p->y_pos / 2, p->x_pos / 2+5, background[OFFSET(p->y_pos / 2,p->x_pos / 2+5,WIDTH)]);
    drawImageLineDMA_r(p->y_pos / 2 + 1, p->x_pos / 2 + 1, 7, p->image + OFFSET(1, 0, 8));
    drawImageLineDMA_r(p->y_pos / 2 + 2, p->x_pos / 2 + 2, 6, p->image + OFFSET(2, 0, 8));
    drawImageLineDMA_r(p->y_pos / 2 + 3, p->x_pos / 2 + 1, 7, p->image + OFFSET(3, 0, 8));
    drawImageLineDMA_r(p->y_pos / 2 + 4, p->x_pos / 2, 8, p->image + OFFSET(4, 0, 8));
    drawImageLineDMA_r(p->y_pos / 2 + 5, p->x_pos / 2, 8, p->image + OFFSET(5, 0, 8));
    drawImageLineDMA_r(p->y_pos / 2 + 6, p->x_pos / 2, 8, p->image + OFFSET(6, 0, 8));
    drawImageLineDMA_r(p->y_pos / 2 + 7, p->x_pos / 2, 8, p->image + OFFSET(7, 0, 8));
    drawImageLineDMA_r(p->y_pos / 2 + 8, p->x_pos / 2, 8, p->image + OFFSET(8, 0, 8));
    drawImageLineDMA_r(p->y_pos / 2 + 9, p->x_pos / 2 + 1, 7, p->image + OFFSET(9, 0, 8));
    drawImageLineDMA_r(p->y_pos / 2 + 10, p->x_pos / 2 + 1, 7, p->image + OFFSET(10, 0, 8));
    drawImageLineDMA_r(p->y_pos / 2 + 11, p->x_pos / 2 + 1, 7, p->image + OFFSET(11, 0, 8));
    drawImageLineDMA_r(p->y_pos / 2 + 12, p->x_pos / 2 + 2, 5, p->image + OFFSET(12, 1, 8));
    drawImageLineDMA_r(p->y_pos / 2 + 13, p->x_pos / 2 + 2, 5, p->image + OFFSET(13, 1, 8));
    setPixel(p->y_pos / 2 + 13, p->x_pos / 2 + 4, background[OFFSET(p->y_pos / 2 + 13, p->x_pos / 2 + 3, WIDTH)]);
    drawImageLineDMA_r(p->y_pos / 2 + 14, p->x_pos / 2 + 2, 5, p->image + OFFSET(14, 1, 8));
    setPixel(p->y_pos / 2 + 14, p->x_pos / 2 + 4, background[OFFSET(p->y_pos / 2 + 14, p->x_pos / 2 + 3, WIDTH)]);
    drawImageLineDMA_r(p->y_pos / 2 + 15, p->x_pos / 2, 8, p->image + OFFSET(15, 0, 8));
    setPixel(p->y_pos / 2 + 15, p->x_pos / 2 + 4, background[OFFSET(p->y_pos / 2 + 15, p->x_pos / 2 + 3, WIDTH)]);
    // drawImageLineDMA(p->y_pos / 2+3, p->x_pos / 2, 7, p->image + OFFSET(3,0,8));
}


