#ifndef UTILITIES_HEADER
#define UTILITIES_HEADER


#include <allegro.h>


typedef enum
{
  OFF = 0,
  ON
} FLAG;


/**
 * Generate a random number between low and high, inclusively.
 * The lower bound is "low".
 * The upper bound is "high".
 */
int random_number(int low, int high);

/**
 * Draw a line of text on the canvas.
 * The text will be drawn with a sincle line border.
 * The shadow won't be drawn if it's -1.
 */
void show_text(BITMAP *canvas, char *text, int x, int y, int color, int shadow);


#endif
