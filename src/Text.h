#ifndef TEXT_HEADER
#define TEXT_HEADER


#include <allegro.h>
#include "KwestKingdom.h"


void resizedTextOut(BITMAP *dest, int x, int y, double multiplier, int color, char *text);
void drawBox(BITMAP *buffer, int x, int y, int w, int h);


#endif
