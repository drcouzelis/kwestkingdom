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
  /*
  [shield update];
  [sword update];
  [bow update];
  */
  
  if (is_waiting(player->character) {
    return;
  }
  
  if (is_key_pressed(player->keys[PLAYER_KEY_WAIT]) {
    wait_turn(player->character);
  }
  
  /* YOU LEFT OFF HERE!! */
  switch (state) {
  
  case HERO_STAND_STATE:
    [self updateStandState];
    break;
    
  case HERO_MOVE_STATE:
    if (![self moving]) {
      [self toStandState];
    }
    break;
    
  case HERO_ATTACK_STATE:
    if ([sword held]) {
      [self toPushSwordState];
    } else if ([bow held]) {
      [self toDrawBowState];
      [self wait];
    }else {
      [self toStandState];
    }
    break;
  
  case HERO_HURT_STATE:
    if ([animation finished]) {
      if (health == 0) {
        [shield toAwayState];
        [sword toAwayState];
        [bow toAwayState];
        [self toDeadState];
      } else {
        [self toStandState];
      }
    }
    break;
  
  case HERO_DEAD_STATE:
    // You are not going to do anything once you enter
    // the state of being dead.
    break;
      
  case HERO_PUSH_SWORD_STATE:
    if ([animation finished]) {
      switch (direction) {
      case UP:
        [world attackFromTeam: team atX: x andY: y - 1];
        break;
      case DOWN:
        [world attackFromTeam: team atX: x andY: y + 1];
        break;
      case LEFT:
        [world attackFromTeam: team atX: x - 1 andY: y ];
        break;
      case RIGHT:
        [world attackFromTeam: team atX: x + 1 andY: y];
        break;
      }
      [self toPullSwordState];
    }
    break;
    
  case HERO_PULL_SWORD_STATE:
    if ([animation finished]) {
      [self toStandState];
      [sword toHoldState];
      [self wait];
    }
    break;
    
  case HERO_DRAW_BOW_STATE:
    if ([animation finished]) {
      [self toShootArrowState];
    }
    break;
    
  case HERO_SHOOT_ARROW_STATE:
    if ([animation finished]) {
      animation = standAnimation;
      [bow toHoldState];
    }
    if ([[bow getArrow] stopped]) {
      [[bow getArrow] free];
      [bow setArrow: nil];
      [self toStandState];
      [self wait];
    }
    break;
    
  }
  
  update_character(player->character, world);
}
