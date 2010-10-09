#include <malloc.h>
#include "anim.h"
#include "character.h"
#include "input.h"
#include "resources.h"
#include "room.h"
#include "sprite.h"
#include "player.h"
#include "world.h"




/**
 * The different animations
 */
enum
{
  PLAYER_ANIM_WALKING = 0,
  PLAYER_ANIM_BEGIN_ATTACK,
  PLAYER_ANIM_END_ATTACK,
  PLAYER_ANIM_HURT,
  PLAYER_ANIM_DEAD
};




PLAYER *create_player()
{
  PLAYER *player;
  SPRITE *sprite;
  ANIM *anim;
  
  player = malloc(sizeof(PLAYER));
  
  /*
  speed = getWalkSpeed(); // In FPS
  team = HERO_TEAM;
  
  shield = [[Shield alloc] init];
  sword = [[Sword alloc] init];
  bow = [[Bow alloc] init];
  
  [shield setSpeed: speed];
  [sword setSpeed: speed];
  [bow setSpeed: speed];
  */
  
  sprite = create_sprite();
  
  /* Walking animation */
  anim = create_anim(6, ON);
  add_frame(anim, get_image(IMG_HERO_STAND_1, NORMAL));
  add_frame(anim, get_image(IMG_HERO_STAND_2, NORMAL));
  add_frame(anim, get_image(IMG_HERO_STAND_3, NORMAL));
  add_frame(anim, get_image(IMG_HERO_STAND_2, NORMAL));
  add_animation(sprite, anim, PLAYER_ANIM_WALKING);
  
  /* Begin attack animation */
  anim = create_anim(12, OFF);
  add_frame(anim, get_image(IMG_HERO_ATTACK_1, NORMAL));
  add_frame(anim, get_image(IMG_HERO_ATTACK_2, NORMAL));
  add_frame(anim, get_image(IMG_HERO_ATTACK_3, NORMAL));
  add_frame(anim, get_image(IMG_HERO_ATTACK_4, NORMAL));
  add_animation(sprite, anim, PLAYER_ANIM_BEGIN_ATTACK);
  
  /* End attack animation */
  anim = create_anim(12, OFF);
  add_frame(anim, get_image(IMG_HERO_ATTACK_3, NORMAL));
  add_frame(anim, get_image(IMG_HERO_ATTACK_2, NORMAL));
  add_frame(anim, get_image(IMG_HERO_ATTACK_1, NORMAL));
  add_animation(sprite, anim, PLAYER_ANIM_END_ATTACK);
  
  /* Hurt animation */
  anim = create_anim(12, OFF);
  add_frame(anim, get_image(IMG_HERO_HURT_1, NORMAL));
  add_frame(anim, get_image(IMG_HERO_HURT_2, NORMAL));
  add_frame(anim, get_image(IMG_HERO_HURT_3, NORMAL));
  add_frame(anim, get_image(IMG_HERO_HURT_4, NORMAL));
  add_frame(anim, get_image(IMG_HERO_HURT_3, NORMAL));
  add_frame(anim, get_image(IMG_HERO_HURT_2, NORMAL));
  add_frame(anim, get_image(IMG_HERO_HURT_1, NORMAL));
  add_animation(sprite, anim, PLAYER_ANIM_HURT);
  
  /* Dead animation */
  anim = create_anim(6, OFF);
  add_frame(anim, get_image(IMG_HERO_DIE_1, NORMAL));
  add_frame(anim, get_image(IMG_HERO_DIE_2, NORMAL));
  add_frame(anim, get_image(IMG_HERO_DIE_3, NORMAL));
  add_frame(anim, get_image(IMG_HERO_DIE_4, NORMAL));
  add_frame(anim, get_image(IMG_HERO_DIE_5, NORMAL));
  add_animation(sprite, anim, PLAYER_ANIM_DEAD);
  
  /* Setup character */
  player->character = create_character(sprite, 3);
  
  player->character->max_health = 3;
  player->character->health = 3;
  
  /* Setup keys */
  player->keys[PLAYER_KEY_UP] = KEY_UP;
  player->keys[PLAYER_KEY_DOWN] = KEY_DOWN;
  player->keys[PLAYER_KEY_LEFT] = KEY_LEFT;
  player->keys[PLAYER_KEY_RIGHT] = KEY_RIGHT;
  player->keys[PLAYER_KEY_WAIT] = KEY_SPACE;
  player->keys[PLAYER_KEY_USE] = KEY_LCONTROL;
  player->keys[PLAYER_KEY_SHIELD] = KEY_1;
  player->keys[PLAYER_KEY_SWORD] = KEY_2;
  player->keys[PLAYER_KEY_BOW] = KEY_3;
  
  /**
   * Finally, change the state of the player.
   */
  change_player_state(player, PLAYER_STATE_STANDING);
  /*[sword toHoldState];*/
  
  /**
   * The player gets to move first.
   */
  take_turn(player->character);
  
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
  /* YOU LEFT OFF HERE!! */

  /*
  [shield update];
  [sword update];
  [bow update];
  */
  
  if (is_waiting(player->character)) {
    return;
  }
  
  if (is_key_pressed(player->keys[PLAYER_KEY_WAIT])) {
    wait_turn(player->character);
  }
  
  switch (player->state) {
  
  case PLAYER_STATE_STANDING:
    /*[self updateStandState];*/
    break;
    
  case PLAYER_STATE_MOVING:
    if (is_moving(player->character->sprite)) {
      change_player_state(player, PLAYER_STATE_STANDING);
    }
    break;
    
  case PLAYER_STATE_ATTACKING:
    /*
    if ([sword held]) {
      [self toPushSwordState];
    } else if ([bow held]) {
      [self toDrawBowState];
      [self wait];
    }else {
      [self toStandState];
    }
    */
    break;
  
  case PLAYER_STATE_HURT:
    /*
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
    */
    break;
  
  case PLAYER_STATE_DEAD:
    /**
     * You are not going to do anything once you enter
     * the state of being dead.
     */
    break;
      
  case PLAYER_STATE_PUSHING_SWORD:
    /*
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
    */
    break;
    
  case PLAYER_STATE_PULLING_SWORD:
    /*
    if ([animation finished]) {
      [self toStandState];
      [sword toHoldState];
      [self wait];
    }
    */
    break;
    
  case PLAYER_STATE_DRAWING_BOW:
    /*
    if ([animation finished]) {
      [self toShootArrowState];
    }
    */
    break;
    
  case PLAYER_STATE_SHOOTING_ARROW:
    /*
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
    */
    break;
  }
  
  update_character(player->character, world);
}




void change_player_state(PLAYER *player, PLAYER_STATE state)
{
  player->state = state;
}

