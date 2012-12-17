#ifndef SCREEN_HEADER
#define SCREEN_HEADER


#include <allegro.h>


void set_win_size(int width, int height);

int init_screen(int width, int height, bool fullscreen);
void free_screen();

int get_win_w();
int get_win_h();

BITMAP *get_win();
bool show_screen();


#endif
