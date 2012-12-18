#ifndef TEXT_HEADER
#define TEXT_HEADER

#ifdef __cplusplus
    extern "C" {
#endif 


#include <allegro.h>


void draw_text(BITMAP *dest, int x, int y, double multiplier, int color, char *text);
void draw_box(BITMAP *buffer, int x, int y, int w, int h);


#ifdef __cplusplus
    }
#endif 

#endif
