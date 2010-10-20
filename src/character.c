#include "character.h"
#include "memory.h"
#include "sprite.h"




/**
 * Public
 */




CHARACTER *create_character(SPRITE *sprite, int health)
{
  CHARACTER *character;
  
  character = alloc_memory(sizeof(CHARACTER));
  
  character->sprite = sprite;
  
  character->max_health = health;
  character->health = health;
  
  character->turns = 0;
  
  return character;
}




void destroy_character(CHARACTER *character)
{
  if (character == NULL) {
    return;
  }
  
  destroy_sprite(character->sprite);
  
  free_memory(character);
}




FLAG is_waiting(CHARACTER *character)
{
  if (character->turns > 0) {
    return ON;
  }
  
  return OFF;
}




void take_turn(CHARACTER *character)
{
  character->turns--;
  
  if (character->turns < 0) {
    character->turns = 0;
  }
}




void wait_turn(CHARACTER *character)
{
  character->turns++;
}
