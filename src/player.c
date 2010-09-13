#include <malloc.h>
#include "anim.h"
#include "character.h"
#include "input.h"
#include "resources.h"
#include "room.h"
#include "sprite.h"
#include "player.h"
#include "world.h"




PLAYER *create_player()
{
  PLAYER *player;
  SPRITE *sprite;
  ANIM *anim;
  
  player = malloc(sizeof(PLAYER));
  
  sprite = create_sprite();
  
  anim = create_anim(6, ON);
  add_frame(anim, get_image(IMG_HERO_STAND_1, NORMAL));
  add_frame(anim, get_image(IMG_HERO_STAND_2, NORMAL));
  add_frame(anim, get_image(IMG_HERO_STAND_3, NORMAL));
  add_frame(anim, get_image(IMG_HERO_STAND_2, NORMAL));
  add_animation(sprite, anim);
  
  player->character = create_character(sprite, 3);
  
  player->character->max_health = 3;
  player->character->health = 3;
  
  player->keys[PLAYER_KEY_UP] = KEY_UP;
  player->keys[PLAYER_KEY_DOWN] = KEY_DOWN;
  player->keys[PLAYER_KEY_LEFT] = KEY_LEFT;
  player->keys[PLAYER_KEY_RIGHT] = KEY_RIGHT;
  player->keys[PLAYER_KEY_WAIT] = KEY_SPACE;
  player->keys[PLAYER_KEY_USE] = KEY_LCONTROL;
  player->keys[PLAYER_KEY_SHIELD] = KEY_1;
  player->keys[PLAYER_KEY_SWORD] = KEY_2;
  player->keys[PLAYER_KEY_BOW] = KEY_3;
  
  return player;
}




void destroy_player(PLAYER *player)
{
  if (player == NULL) {
    return;
  }
  
  destroy_character(player->character);
  
  free(player);
}




void update_player(PLAYER *player, WORLD *world)
{
  if (player == NULL) {
    return;
  }
  
  world = world; /* TEMP */
  
  update_character(player->character, world);
}
