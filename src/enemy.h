#ifndef ENEMY_HEADER
#define ENEMY_HEADER


#include "direction.h"


typedef struct ENEMY ENEMY;
struct CHARACTER;
struct WORLD;


struct ENEMY
{
  struct CHARACTER *character;
  
  DIRECTION prev_dir;
  
  /**
   * This command allows different character to behave differently
   * from each other.
   */
  void (*command)(ENEMY *enemy, struct WORLD *world);
};


ENEMY *create_enemy();
ENEMY *destroy_enemy();

void update_enemy(ENEMY *enemy, struct WORLD *world);


#endif