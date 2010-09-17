#ifndef GAME_HEADER
#define GAME_HEADER


#include <allegro.h>

#include "utilities.h"


typedef struct GAME GAME;
struct ANIM;
struct WORLD;


struct GAME
{
  struct WORLD *world;
  
  /**
   * The title screen image
   */
  struct ANIM *title_anim;
  
  /**
   * The game over image
   */
  struct ANIM *gameover_anim;
  
  /**
   * The selection icon
   */
  struct ANIM *pointer_anim;
  
  /**
   * The title screen background
   */
  BITMAP *title_background;
  
  /**
   * Which line the menu pointer is on
   */
  int selection;
  
  int state;
};


GAME *create_game();
void destroy_game(GAME *game);

FLAG is_game_over(GAME *game);
FLAG is_game_won(GAME *game);

void update_game(GAME *game);
void paint_game(GAME *game, BITMAP *canvas);


#endif
