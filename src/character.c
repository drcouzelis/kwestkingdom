#include "character.h"
#include "sprite.h"




CHARACTER *create_character(SPRITE *sprite, int health)
{
  CHARACTER *character;
  
  character = malloc(sizeof(CHARACTER));
  
  character->sprite = sprite;
  
  character->inventory = NULL;
  
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
  /*destroy_inventory(character->inventory);*/
  
  free(character);
}




void update_character(CHARACTER *character, struct WORLD *world)
{
  if (character == NULL) {
    return;
  }
  
  world = world; /* TEMP */
  
  update_sprite(character->sprite);
}
