#ifndef SCREEN_HEADER
#define SCREEN_HEADER


#include <allegro.h>
#include "utilities.h"


#define SCREEN_UPDATE_STR_LEN 20


FLAG init_screen(int width, int height, FLAG fullscreen);
void stop_screen();

/**
 * After you initialize the screen and load your resources,
 * use this function to set the color palette.
 */
void change_colors(PALETTE *palette);

/**
 * Get the name of the current screen updating method.
 */
void find_screen_update_method(char *method);

int grab_screen_width();
int grab_screen_height();

void change_canvas_size(int width, int height);

/**
 * The canvas is the important part.
 * This is what you'll be drawing to.
 */
int grab_canvas_width();
int grab_canvas_height();

BITMAP *grab_canvas();

/**
 * Draw the contents of the the canvas to the screen.
 */
void refresh_screen();


#endif
