#ifndef KK_SCREEN_H
#define KK_SCREEN_H


#include <allegro.h>
#include <stdbool.h>


#define KK_SCREEN_UPDATE_STR_LEN 20


bool kk_init_screen(int width, int height, bool fullscreen);
void kk_free_screen();

void kk_set_colors(PALETTE *palette);

void kk_get_screen_update_method(char *empty_string);

inline int kk_screen_width();
inline int kk_screen_height();

void kk_set_canvas_size(int width, int height);

inline int kk_canvas_width();
inline int kk_canvas_height();

inline BITMAP *kk_get_canvas();

bool kk_update_screen();


#endif

