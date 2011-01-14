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
   * The game over image
   */
  struct ANIM *gameover_anim;
  
  /**
   * Player health icons
   */
  struct ANIM *full_heart_anim;
  struct ANIM *empty_heart_anim;
  
  int state;
};


GAME *create_story_game();
GAME *create_endless_game();
void destroy_game(GAME *game);

FLAG is_game_over(GAME *game);
FLAG is_game_won(GAME *game);

void update_game(GAME *game);
void paint_game(GAME *game, BITMAP *canvas);

struct WORLD *grab_world();

/**
 * The room that the player is currently in.
 */
struct ROOM *grab_room();

struct PLAYER *grab_player();

#endif
