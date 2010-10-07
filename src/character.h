#ifndef CHARACTER_HEADER
#define CHARACTER_HEADER


#include <allegro.h>

#include "utilities.h"


typedef struct CHARACTER CHARACTER;
struct INVENTORY;
struct SPRITE;
struct WORLD;


struct CHARACTER
{
  /**
   * Represents the character on screen.
   */
  struct SPRITE *sprite;
  
  /**
   * The equipment that the character can use.
   */
  struct INVENTORY *inventory;
  
  /**
   * The character health.
   * When health becomes zeno, the character is dead.
   */
  int max_health;
  int health;
  
  /**
   * Used to allow the characters in the game to take turns.
   *
   * Every time the character is told to wait, this number
   * is increased by one.
   *
   * Every time the character has the opportunity to take a turn,
   * this value is decreased by one. If the this number is zero
   * then the character takes a turn.
   */
  int turns;
};


CHARACTER *create_character(struct SPRITE *sprite, int health);
void destroy_character(CHARACTER *character);

void update_character(CHARACTER *character, struct WORLD *world);

/**
 * For taking turns
 */
FLAG is_waiting(CHARACTER *character);
void take_turn(CHARACTER *character);
void wait_turn(CHARACTER *character);


#endif
