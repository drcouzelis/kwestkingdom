#include "anim.h"
#include "character.h"
#include "game.h"
#include "input.h"
#include "memory.h"
#include "resources.h"
#include "room.h"
#include "sound.h"
#include "sprite.h"
#include "player.h"
#include "world.h"




/**
 * Private
 */




/**
 * The different animations
 */
enum
{
  PLAYER_ANIM_WALKING = 0,
  PLAYER_ANIM_BEGIN_ATTACK,
  PLAYER_ANIM_END_ATTACK,
  PLAYER_ANIM_HURT,
  PLAYER_ANIM_DEAD,
  
  MAX_PLAYER_ANIMS
};




void change_player_state(PLAYER *player, PLAYER_STATE state)
{
  SPRITE *sprite = player->character->sprite;
  
  player->state = state;
  
  switch (state) {
  
  case PLAYER_STATE_STANDING:
    change_anim(sprite, PLAYER_ANIM_WALKING);
    break;
  case PLAYER_STATE_MOVING:
    change_anim(sprite, PLAYER_ANIM_WALKING);
    break;
  case PLAYER_STATE_ATTACKING:
    change_anim(sprite, PLAYER_ANIM_WALKING);
    break;
  case PLAYER_STATE_HURT:
    change_anim(sprite, PLAYER_ANIM_HURT);
    reset_anim(grab_anim(sprite, -1));
    
    /*
    // You can't shoot an arrow if you get
    // hurt whil trying to do it.
    [[bow getArrow] free];
    [bow setArrow: nil];
    if ([bow held]) {
      [bow toHoldState];
    }
    */
    
    play_sound(grab_sound(SND_GASP));
    break;
  case PLAYER_STATE_DEAD:
    change_anim(sprite, PLAYER_ANIM_DEAD);
    reset_anim(grab_anim(sprite, -1));
    break;
  case PLAYER_STATE_PUSHING_SWORD:
    change_anim(sprite, PLAYER_ANIM_BEGIN_ATTACK);
    reset_anim(grab_anim(sprite, -1));
    
    /*
    switch (direction) {
    case UP:
      [sword toAttackUpState];
      break;
    case DOWN:
      [sword toAttackDownState];
      break;
    case LEFT:
      [sword toAttackLeftState];
      break;
    case RIGHT:
      [sword toAttackRightState];
      break;
    }
    */
    break;
  case PLAYER_STATE_PULLING_SWORD:
    change_anim(sprite, PLAYER_ANIM_END_ATTACK);
    reset_anim(grab_anim(sprite, -1));
    break;
  case PLAYER_STATE_DRAWING_BOW:
    change_anim(sprite, PLAYER_ANIM_BEGIN_ATTACK);
    reset_anim(grab_anim(sprite, -1));
    
    /*
    switch (direction) {
    case UP:
      [bow toAttackUpState];
      break;
    case DOWN:
      [bow toAttackDownState];
      break;
    case LEFT:
      [bow toAttackLeftState];
      break;
    case RIGHT:
      [bow toAttackRightState];
      break;
    }
    
    [bow setArrowWithX: x andY: y andDirection: direction andTeam: team andWorld: world];
    */
    break;
  case PLAYER_STATE_SHOOTING_ARROW:
    change_anim(sprite, PLAYER_ANIM_END_ATTACK);
    reset_anim(grab_anim(sprite, -1));
    /*
    [[bow getArrow] toFlyingState];
    [bow toHoldState];
    */
    break;
  }
}




void update_player_state_standing(PLAYER *player, WORLD *world)
{
  SPRITE *sprite = player->character->sprite;
  
  int to_row;
  int to_col;
  
  /**
   * Handle item key input.
   * Update the items.
   */
  /*
  if ([shieldKey isPressed]) {
    [shield toHoldState];
    [sword toAwayState];
    [bow toAwayState];
  } else if ([swordKey isPressed]) {
    [shield toAwayState];
    [sword toHoldState];
    [bow toAwayState];
  } else if ([bowKey isPressed]) {
    [shield toAwayState];
    [sword toAwayState];
    [bow toHoldState];
  } else if ([handKey isPressed]) {
    [shield toAwayState];
    [sword toAwayState];
    [bow toAwayState];
  }
  */
  
  if (is_key_held(player->keys[PLAYER_KEY_USE])) {
    
    /*
    if ([upKey isPressed]) {
      direction = UP;
      [self toAttackState];
    } else if ([downKey isPressed]) {
      direction = DOWN;
      [self toAttackState];
    } else if ([leftKey isPressed]) {
      direction = LEFT;
      [self toAttackState];
    } else if ([rightKey isPressed]) {
      direction = RIGHT;
      [self toAttackState];
    }
    */
    
  } else {
    
    /**
     * If you're not attacking with the attack key,
     * then maybe you are trying to walk...
     */
    
    to_row = sprite->row;
    to_col = sprite->col;
    
    if (is_key_held(player->keys[PLAYER_KEY_UP])) {
      to_row--;
      /*
      if ([sword held] && [world isAttackableFromTeam: team atX: x andY: y - 1]) {
        direction = UP;
        [self toAttackState];
      }
      */
    } else if (is_key_held(player->keys[PLAYER_KEY_DOWN])) {
      to_row++;
      /*
      if ([sword held] && [world isAttackableFromTeam: team atX: toX andY: toY]) {
        direction = DOWN;
        [self toAttackState];
      }
      */
    } else if (is_key_held(player->keys[PLAYER_KEY_LEFT])) {
      to_col--;
      /*
      if ([sword held] && [world isAttackableFromTeam: team atX: toX andY: toY]) {
        direction = LEFT;
        [self toAttackState];
      }
      */
    } else if (is_key_held(player->keys[PLAYER_KEY_RIGHT])) {
      to_col++;
      /*
      if ([sword held] && [world isAttackableFromTeam: team atX: toX andY: toY]) {
        direction = RIGHT;
        [self toAttackState];
      }
      */
    }
    
    if (sprite->row != to_row || sprite->col != to_col) {
      
      if (is_walkable(grab_room(world), to_row, to_col)) {
      /*if ([world isWalkableAtX: toX andY: toY] && ![world isInhabitedAtX: toX andY: toY]) {*/
        
        move_sprite(sprite, to_row, to_col);
        
        change_player_state(player, PLAYER_STATE_MOVING);
        
        wait_turn(player->character);
        
        /**
         * If the hero is holding the shield
         * then make him wait another turn.
         */
        /*
        if ([shield held]) {
          [self wait];
        }
        */
      }
    }
  }
}




/**
 * Public
 */




PLAYER *create_player()
{
  PLAYER *player;
  SPRITE *sprite;
  ANIM *anim;
  
  player = alloc_memory("PLAYER", sizeof(PLAYER));
  
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
  add_frame(anim, grab_image(IMG_HERO_STAND_1, NORMAL));
  add_frame(anim, grab_image(IMG_HERO_STAND_2, NORMAL));
  add_frame(anim, grab_image(IMG_HERO_STAND_3, NORMAL));
  add_frame(anim, grab_image(IMG_HERO_STAND_2, NORMAL));
  add_anim(sprite, anim, PLAYER_ANIM_WALKING);
  
  /* Begin attack animation */
  anim = create_anim(12, OFF);
  add_frame(anim, grab_image(IMG_HERO_ATTACK_1, NORMAL));
  add_frame(anim, grab_image(IMG_HERO_ATTACK_2, NORMAL));
  add_frame(anim, grab_image(IMG_HERO_ATTACK_3, NORMAL));
  add_frame(anim, grab_image(IMG_HERO_ATTACK_4, NORMAL));
  add_anim(sprite, anim, PLAYER_ANIM_BEGIN_ATTACK);
  
  /* End attack animation */
  anim = create_anim(12, OFF);
  add_frame(anim, grab_image(IMG_HERO_ATTACK_3, NORMAL));
  add_frame(anim, grab_image(IMG_HERO_ATTACK_2, NORMAL));
  add_frame(anim, grab_image(IMG_HERO_ATTACK_1, NORMAL));
  add_anim(sprite, anim, PLAYER_ANIM_END_ATTACK);
  
  /* Hurt animation */
  anim = create_anim(12, OFF);
  add_frame(anim, grab_image(IMG_HERO_HURT_1, NORMAL));
  add_frame(anim, grab_image(IMG_HERO_HURT_2, NORMAL));
  add_frame(anim, grab_image(IMG_HERO_HURT_3, NORMAL));
  add_frame(anim, grab_image(IMG_HERO_HURT_4, NORMAL));
  add_frame(anim, grab_image(IMG_HERO_HURT_3, NORMAL));
  add_frame(anim, grab_image(IMG_HERO_HURT_2, NORMAL));
  add_frame(anim, grab_image(IMG_HERO_HURT_1, NORMAL));
  add_anim(sprite, anim, PLAYER_ANIM_HURT);
  
  /* Dead animation */
  anim = create_anim(6, OFF);
  add_frame(anim, grab_image(IMG_HERO_DIE_1, NORMAL));
  add_frame(anim, grab_image(IMG_HERO_DIE_2, NORMAL));
  add_frame(anim, grab_image(IMG_HERO_DIE_3, NORMAL));
  add_frame(anim, grab_image(IMG_HERO_DIE_4, NORMAL));
  add_frame(anim, grab_image(IMG_HERO_DIE_5, NORMAL));
  add_anim(sprite, anim, PLAYER_ANIM_DEAD);
  
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
  
  free_memory("PLAYER", player);
}




void update_player(PLAYER *player, WORLD *world)
{
  SPRITE *sprite = player->character->sprite;
  
  update_sprite(sprite);
  
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
    update_player_state_standing(player, world);
    break;
    
  case PLAYER_STATE_MOVING:
    if (!is_moving(sprite)) {
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
}
