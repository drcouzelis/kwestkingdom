#ifndef TEXT_HEADER
#define TEXT_HEADER


#include <allegro.h>


void draw_text(BITMAP *dest, int x, int y, double multiplier, int color, char *text);
void draw_box(BITMAP *buffer, int x, int y, int w, int h);


#endif
