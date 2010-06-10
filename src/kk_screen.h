#ifndef KK_SCREEN_H
#define KK_SCREEN_H


#include <allegro.h>

#include "al_screen.h"
#include "kk_kwestkingdom.h"
#include "kk_utilities.h"


void KK_set_window_size(int width, int height);

FLAG KK_init_screen(int width, int height, FLAG fullscreen);
void KK_free_screen();

int KK_window_width();
int KK_window_height();

BITMAP *KK_get_window();
FLAG KK_refresh_screen();


#endif

