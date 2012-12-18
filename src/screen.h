#ifndef SCREEN_HEADER
#define SCREEN_HEADER

#ifdef __cplusplus
    extern "C" {
#endif 


#include <allegro.h>
#include "utilities.h"


void set_win_size(int width, int height);

FLAG init_screen(int width, int height, int fullscreen);
void free_screen();

int get_win_w();
int get_win_h();

BITMAP *get_win();
FLAG show_screen();


#ifdef __cplusplus
    }
#endif 

#endif
