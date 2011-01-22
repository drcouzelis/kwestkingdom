#include <stdlib.h>
#include <time.h>
#include "utilities.h"


static FLAG init_random_numbers = OFF;


int random_number(int low, int high)
{
  if (!init_random_numbers) {
    srand(time(NULL));
    init_random_numbers = ON;
  }
  
  return (rand() % (high - low + 1)) + low;
}




void show_text(BITMAP *canvas, char *text, int x, int y, int color, int shadow)
{
  if (shadow >= 0) {
    textprintf_ex(canvas, font, x + 1, y, shadow, -1, text);
    textprintf_ex(canvas, font, x - 1, y, shadow, -1, text);
    textprintf_ex(canvas, font, x, y + 1, shadow, -1, text);
    textprintf_ex(canvas, font, x, y - 1, shadow, -1, text);
  }
  
  textprintf_ex(canvas, font, x, y, color, -1, text);
}
