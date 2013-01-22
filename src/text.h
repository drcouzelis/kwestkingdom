#ifndef TEXT_HEADER
#define TEXT_HEADER


#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include "resources.h"


#ifdef __cplusplus
    extern "C" {
#endif 


void draw_text(IMAGE *canvas, int x, int y, double multiplier, int color, char *text);
void draw_box(IMAGE *canvas, int x, int y, int w, int h);


#ifdef __cplusplus
    }
#endif 

#endif
