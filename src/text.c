#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include "KwestKingdom.h"
#include "text.h"


void draw_text(float x, float y, char *text)
{
  // Draw the shadow
  //textout_ex(canvas, font, text, x + 1, y, BLACK, -1);
  //textout_ex(canvas, font, text, x - 1, y, BLACK, -1);
  //textout_ex(canvas, font, text, x, y + 1, BLACK, -1);
  //textout_ex(canvas, font, text, x, y - 1, BLACK, -1);

  //textout_ex(canvas, font, text, x, y, WHITE, -1); // NEW_ALLEGRO
}


void draw_box(float x, float y, int w, int h)
{
  al_draw_filled_rectangle(x, y, x + w, y + w, RED);
}

