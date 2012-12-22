#include "KwestKingdom.h"
#include "text.h"


void draw_shadowed_text(IMAGE *canvas, char *text, int x, int y, int color, int shadow)
{
  if (shadow >= 0) {
    textout_ex(canvas, font, text, x + 1, y, shadow, -1);
    textout_ex(canvas, font, text, x - 1, y, shadow, -1);
    textout_ex(canvas, font, text, x, y + 1, shadow, -1);
    textout_ex(canvas, font, text, x, y - 1, shadow, -1);
  }

  textout_ex(canvas, font, text, x, y, color, -1);
}


void draw_text(IMAGE *canvas, int x, int y, double multiplier, int color, char *text)
{
  draw_shadowed_text(canvas, text, x, y, color, BLACK);
}


void draw_box(IMAGE *canvas, int x, int y, int w, int h)
{
  /*
  int leftOutside;
  int rightOutside;
  int topOutside;
  int bottomOutside;
  
  int leftInside;
  int rightInside;
  int topInside;
  int bottomInside;
  
  int offset;
  int depth;
  
  offset = 4;
  depth = 12;
  
  leftOutside = x - offset;
  rightOutside = x + w + offset;
  topOutside = y - offset;
  bottomOutside = y + h + offset;
  
  leftInside = leftOutside + depth;
  rightInside = rightOutside - depth;
  topInside = topOutside + depth;
  bottomInside = bottomOutside - depth;
  */
  
  //rectfill(canvas, leftInside, topInside, rightInside, bottomInside, RED);
  rectfill(canvas, x, y, x + w, y + h, RED);
  
  /*
  // Top
  hline(canvas, leftOutside + 2, topOutside + 0, rightOutside - 2, WHITE);
  hline(canvas, leftOutside + 2, topOutside + 1, rightOutside - 2, WHITE);
  hline(canvas, leftOutside, topOutside + 2, rightOutside - 4, WHITE);
  hline(canvas, leftOutside, topOutside + 3, rightOutside - 4, WHITE);
  hline(canvas, leftOutside, topOutside + 4, leftOutside + 5, WHITE);
  hline(canvas, leftOutside, topOutside + 5, leftOutside + 5, WHITE);
  hline(canvas, leftOutside, topOutside + 6, leftOutside + 3, WHITE);
  hline(canvas, leftOutside, topOutside + 7, leftOutside + 3, WHITE);
  hline(canvas, leftOutside, topOutside + 8, leftOutside + 3, WHITE);
  hline(canvas, leftOutside, topOutside + 9, leftOutside + 3, WHITE);
  hline(canvas, leftOutside, topOutside + 10, leftOutside + 3, WHITE);
  hline(canvas, leftOutside, topOutside + 11, leftOutside + 3, WHITE);
  hline(canvas, leftOutside, topOutside + 12, leftOutside + 3, WHITE);
  hline(canvas, leftOutside, topOutside + 13, leftOutside + 3, WHITE);
  hline(canvas, rightOutside - 9, topOutside + 10, rightOutside - 8, WHITE);
  hline(canvas, rightOutside - 9, topOutside + 11, rightOutside - 8, WHITE);
  hline(canvas, rightOutside - 11, topOutside + 12, rightOutside - 8, WHITE);
  hline(canvas, rightOutside - 11, topOutside + 13, rightOutside - 8, WHITE);
  
  hline(canvas, leftOutside + 6, topOutside + 4, rightOutside - 6, BLACK);
  hline(canvas, leftOutside + 6, topOutside + 5, rightOutside - 6, BLACK);
  hline(canvas, leftOutside + 4, topOutside + 6, rightOutside - 4, BLACK);
  hline(canvas, leftOutside + 4, topOutside + 7, rightOutside - 4, BLACK);
  hline(canvas, leftOutside + 4, topOutside + 8, leftOutside + 9, BLACK);
  hline(canvas, leftOutside + 4, topOutside + 9, leftOutside + 9, BLACK);
  hline(canvas, leftOutside + 4, topOutside + 10, leftOutside + 7, BLACK);
  hline(canvas, leftOutside + 4, topOutside + 11, leftOutside + 7, BLACK);
  hline(canvas, leftOutside + 4, topOutside + 12, leftOutside + 7, BLACK);
  hline(canvas, leftOutside + 4, topOutside + 13, leftOutside + 7, BLACK);
  hline(canvas, rightOutside - 7, topOutside + 8, rightOutside - 4, BLACK);
  hline(canvas, rightOutside - 7, topOutside + 9, rightOutside - 4, BLACK);
  hline(canvas, rightOutside - 7, topOutside + 10, rightOutside - 4, BLACK);
  hline(canvas, rightOutside - 7, topOutside + 11, rightOutside - 4, BLACK);
  hline(canvas, rightOutside - 7, topOutside + 12, rightOutside - 4, BLACK);
  hline(canvas, rightOutside - 7, topOutside + 13, rightOutside - 4, BLACK);
  
  hline(canvas, leftOutside + 10, topOutside + 8, rightOutside - 8, GRAY);
  hline(canvas, leftOutside + 10, topOutside + 9, rightOutside - 8, GRAY);
  hline(canvas, leftOutside + 8, topOutside + 10, rightOutside - 10, GRAY);
  hline(canvas, leftOutside + 8, topOutside + 11, rightOutside - 10, GRAY);
  hline(canvas, leftOutside + 8, topOutside + 12, leftOutside + 13, GRAY);
  hline(canvas, leftOutside + 8, topOutside + 13, leftOutside + 13, GRAY);
  hline(canvas, rightOutside - 13, topOutside + 12, rightOutside - 12, GRAY);
  hline(canvas, rightOutside - 13, topOutside + 13, rightOutside - 12, GRAY);
  hline(canvas, rightOutside - 3, topOutside + 2, rightOutside, GRAY);
  hline(canvas, rightOutside - 3, topOutside + 3, rightOutside, GRAY);
  hline(canvas, rightOutside - 5, topOutside + 4, rightOutside, GRAY);
  hline(canvas, rightOutside - 5, topOutside + 5, rightOutside, GRAY);
  hline(canvas, rightOutside - 3, topOutside + 6, rightOutside, GRAY);
  hline(canvas, rightOutside - 3, topOutside + 7, rightOutside, GRAY);
  hline(canvas, rightOutside - 3, topOutside + 8, rightOutside, GRAY);
  hline(canvas, rightOutside - 3, topOutside + 9, rightOutside, GRAY);
  hline(canvas, rightOutside - 3, topOutside + 10, rightOutside, GRAY);
  hline(canvas, rightOutside - 3, topOutside + 11, rightOutside, GRAY);
  hline(canvas, rightOutside - 3, topOutside + 12, rightOutside, GRAY);
  hline(canvas, rightOutside - 3, topOutside + 13, rightOutside, GRAY);
  
  // Bottom
  hline(canvas, leftOutside + 2, bottomOutside - 0, rightOutside - 2, GRAY);
  hline(canvas, leftOutside + 2, bottomOutside - 1, rightOutside - 2, GRAY);
  hline(canvas, leftOutside + 2, bottomOutside - 2, rightOutside, GRAY);
  hline(canvas, leftOutside + 2, bottomOutside - 3, rightOutside, GRAY);
  hline(canvas, rightOutside - 5, bottomOutside - 4, rightOutside, GRAY);
  hline(canvas, rightOutside - 5, bottomOutside - 5, rightOutside, GRAY);
  hline(canvas, rightOutside - 3, bottomOutside - 6, rightOutside, GRAY);
  hline(canvas, rightOutside - 3, bottomOutside - 7, rightOutside, GRAY);
  hline(canvas, rightOutside - 3, bottomOutside - 8, rightOutside, GRAY);
  hline(canvas, rightOutside - 3, bottomOutside - 9, rightOutside, GRAY);
  hline(canvas, rightOutside - 3, bottomOutside - 10, rightOutside, GRAY);
  hline(canvas, rightOutside - 3, bottomOutside - 11, rightOutside, GRAY);
  hline(canvas, rightOutside - 3, bottomOutside - 12, rightOutside, GRAY);
  hline(canvas, rightOutside - 3, bottomOutside - 13, rightOutside, GRAY);
  hline(canvas, leftOutside + 4, bottomOutside - 4, leftOutside + 5, GRAY);
  hline(canvas, leftOutside + 4, bottomOutside - 5, leftOutside + 5, GRAY);
  hline(canvas, leftOutside + 8, bottomOutside - 10, leftOutside + 11, GRAY);
  hline(canvas, leftOutside + 8, bottomOutside - 11, leftOutside + 11, GRAY);
  hline(canvas, leftOutside + 8, bottomOutside - 12, leftOutside + 11, GRAY);
  hline(canvas, leftOutside + 8, bottomOutside - 13, leftOutside + 11, GRAY);
  hline(canvas, leftOutside + 12, bottomOutside - 12, leftOutside + 13, GRAY);
  hline(canvas, leftOutside + 12, bottomOutside - 13, leftOutside + 13, GRAY);
  
  hline(canvas, leftOutside + 6, bottomOutside - 4, rightOutside - 6, BLACK);
  hline(canvas, leftOutside + 6, bottomOutside - 5, rightOutside - 6, BLACK);
  hline(canvas, leftOutside + 4, bottomOutside - 6, rightOutside - 4, BLACK);
  hline(canvas, leftOutside + 4, bottomOutside - 7, rightOutside - 4, BLACK);
  hline(canvas, rightOutside - 9, bottomOutside - 8, rightOutside - 4, BLACK);
  hline(canvas, rightOutside - 9, bottomOutside - 9, rightOutside - 4, BLACK);
  hline(canvas, rightOutside - 7, bottomOutside - 10, rightOutside - 4, BLACK);
  hline(canvas, rightOutside - 7, bottomOutside - 11, rightOutside - 4, BLACK);
  hline(canvas, rightOutside - 7, bottomOutside - 12, rightOutside - 4, BLACK);
  hline(canvas, rightOutside - 7, bottomOutside - 13, rightOutside - 4, BLACK);
  hline(canvas, leftOutside + 4, bottomOutside - 8, leftOutside + 7, BLACK);
  hline(canvas, leftOutside + 4, bottomOutside - 9, leftOutside + 7, BLACK);
  hline(canvas, leftOutside + 4, bottomOutside - 10, leftOutside + 7, BLACK);
  hline(canvas, leftOutside + 4, bottomOutside - 11, leftOutside + 7, BLACK);
  hline(canvas, leftOutside + 4, bottomOutside - 12, leftOutside + 7, BLACK);
  hline(canvas, leftOutside + 4, bottomOutside - 13, leftOutside + 7, BLACK);
  hline(canvas, leftOutside + 8, bottomOutside - 8, leftOutside + 9, BLACK);
  hline(canvas, leftOutside + 8, bottomOutside - 9, leftOutside + 9, BLACK);
  
  hline(canvas, leftOutside + 10, bottomOutside - 8, rightOutside - 10, WHITE);
  hline(canvas, leftOutside + 10, bottomOutside - 9, rightOutside - 10, WHITE);
  hline(canvas, leftOutside + 12, bottomOutside - 10, rightOutside - 8, WHITE);
  hline(canvas, leftOutside + 12, bottomOutside - 11, rightOutside - 8, WHITE);
  hline(canvas, rightOutside - 13, bottomOutside - 12, rightOutside - 8, WHITE);
  hline(canvas, rightOutside - 13, bottomOutside - 13, rightOutside - 8, WHITE);
  hline(canvas, leftOutside, bottomOutside - 2, leftOutside + 1, WHITE);
  hline(canvas, leftOutside, bottomOutside - 3, leftOutside + 1, WHITE);
  hline(canvas, leftOutside, bottomOutside - 4, leftOutside + 3, WHITE);
  hline(canvas, leftOutside, bottomOutside - 5, leftOutside + 3, WHITE);
  hline(canvas, leftOutside, bottomOutside - 6, leftOutside + 3, WHITE);
  hline(canvas, leftOutside, bottomOutside - 7, leftOutside + 3, WHITE);
  hline(canvas, leftOutside, bottomOutside - 8, leftOutside + 3, WHITE);
  hline(canvas, leftOutside, bottomOutside - 9, leftOutside + 3, WHITE);
  hline(canvas, leftOutside, bottomOutside - 10, leftOutside + 3, WHITE);
  hline(canvas, leftOutside, bottomOutside - 11, leftOutside + 3, WHITE);
  hline(canvas, leftOutside, bottomOutside - 12, leftOutside + 3, WHITE);
  hline(canvas, leftOutside, bottomOutside - 13, leftOutside + 3, WHITE);
  
  // Left
  vline(canvas, leftOutside + 0, topOutside + 14, bottomOutside - 14, WHITE);
  vline(canvas, leftOutside + 1, topOutside + 14, bottomOutside - 14, WHITE);
  vline(canvas, leftOutside + 2, topOutside + 14, bottomOutside - 14, WHITE);
  vline(canvas, leftOutside + 3, topOutside + 14, bottomOutside - 14, WHITE);
  vline(canvas, leftOutside + 4, topOutside + 14, bottomOutside - 14, BLACK);
  vline(canvas, leftOutside + 5, topOutside + 14, bottomOutside - 14, BLACK);
  vline(canvas, leftOutside + 6, topOutside + 14, bottomOutside - 14, BLACK);
  vline(canvas, leftOutside + 7, topOutside + 14, bottomOutside - 14, BLACK);
  vline(canvas, leftOutside + 8, topOutside + 14, bottomOutside - 14, GRAY);
  vline(canvas, leftOutside + 9, topOutside + 14, bottomOutside - 14, GRAY);
  vline(canvas, leftOutside + 10, topOutside + 14, bottomOutside - 14, GRAY);
  vline(canvas, leftOutside + 11, topOutside + 14, bottomOutside - 14, GRAY);
  
  // Right
  vline(canvas, rightOutside - 0, topOutside + 14, bottomOutside - 14, GRAY);
  vline(canvas, rightOutside - 1, topOutside + 14, bottomOutside - 14, GRAY);
  vline(canvas, rightOutside - 2, topOutside + 14, bottomOutside - 14, GRAY);
  vline(canvas, rightOutside - 3, topOutside + 14, bottomOutside - 14, GRAY);
  vline(canvas, rightOutside - 4, topOutside + 14, bottomOutside - 14, BLACK);
  vline(canvas, rightOutside - 5, topOutside + 14, bottomOutside - 14, BLACK);
  vline(canvas, rightOutside - 6, topOutside + 14, bottomOutside - 14, BLACK);
  vline(canvas, rightOutside - 7, topOutside + 14, bottomOutside - 14, BLACK);
  vline(canvas, rightOutside - 8, topOutside + 14, bottomOutside - 14, WHITE);
  vline(canvas, rightOutside - 9, topOutside + 14, bottomOutside - 14, WHITE);
  vline(canvas, rightOutside - 10, topOutside + 14, bottomOutside - 14, WHITE);
  vline(canvas, rightOutside - 11, topOutside + 14, bottomOutside - 14, WHITE);
  */
}

