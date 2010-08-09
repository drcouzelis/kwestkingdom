#ifndef KK_GAME_H
#define KK_GAME_H


#include <allegro.h>


typedef struct GAME GAME;
struct ANIM;
struct WORLD;


struct GAME
{
  struct WORLD *world;
  
  /**
   * The title screen image
   */
  struct ANIM *titleAnim;
  
  /**
   * The game over image
   */
  struct ANIM *gameoverAnim;
};


GAME *create_game();
GAME *destroy_game();

void update_game(GAME *game);
void paint_game(GAME *game, BITMAP *canvas);


#endif
