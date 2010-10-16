#ifndef ENEMY_HEADER
#define ENEMY_HEADER


#include "direction.h"


/**
 * A list of the different types of enemies.
 */
typedef enum
{
  ENEMY_TYPE_CHOMPER = 0,
  ENEMY_TYPE_ARCHER,
  ENEMY_TYPE_NINJA,
  ENEMY_TYPE_GIANT,
  
  NUM_ENEMY_TYPES
} ENEMY_TYPE;


typedef union ENEMY ENEMY;
struct WORLD;

/**
 * The different enemy structs
 */
struct CHOMPER;
struct ARCHER;
struct NINJA;
struct GIANT;


union ENEMY
{
  /**
   * NOTE: Every enemy type must have "int type" as
   * the first entry in its struct.
   */
  int type;
  
  struct CHOMPER *chomper;
  struct ARCHER *archer;
  struct NINJA *ninja;
  struct GIANT *giant;
};


ENEMY *create_enemy();
void destroy_enemy(ENEMY *enemy);

void update_enemy(ENEMY *enemy, struct WORLD *world);


#endif
