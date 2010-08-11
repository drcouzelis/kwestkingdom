#ifndef CHARACTER_HEADER
#define CHARACTER_HEADER


#include <allegro.h>


typedef struct CHARACTER CHARACTER;
struct INVENTORY;
struct SPRITE;


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
CHARACTER *destroy_character(CHARACTER *chara);

void update_character(CHARACTER *chara, struct WORLD *world);


#endif
