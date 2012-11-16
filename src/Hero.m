/**
 * Copyright 2009 David Couzelis
 * 
 * This file is part of "Kwest Kingdom".
 * 
 * "Kwest Kingdom" is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * "Kwest Kingdom" is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with "Kwest Kingdom".  If not, see <http://www.gnu.org/licenses/>.
 */
#import "Hero.h"


#define HERO_ATTACK_SPEED 12


typedef enum {
  HERO_STAND_STATE,
  HERO_MOVE_STATE,
  HERO_ATTACK_STATE,
  HERO_HURT_STATE,
  HERO_DEAD_STATE,
  HERO_PUSH_SWORD_STATE,
  HERO_PULL_SWORD_STATE,
  HERO_DRAW_BOW_STATE,
  HERO_SHOOT_ARROW_STATE
} HERO_STATE;


@implementation Hero


- init {
  
  self = [super init];
  
  if (self) {
    
    speed = getWalkSpeed(); // In FPS
    health = 3;
    maxHealth = MAX_HERO_HEALTH;
    team = HERO_TEAM;
    
    shield = [[Shield alloc] init];
    sword = [[Sword alloc] init];
    bow = [[Bow alloc] init];
    
    [shield setSpeed: speed];
    [sword setSpeed: speed];
    [bow setSpeed: speed];
    
    standAnimation = [[Animation alloc] init];
    [standAnimation addFrame: getImage(IMAGES_HERO_STAND_1)];
    [standAnimation addFrame: getImage(IMAGES_HERO_STAND_2)];
    [standAnimation addFrame: getImage(IMAGES_HERO_STAND_3)];
    [standAnimation addFrame: getImage(IMAGES_HERO_STAND_2)];
    [standAnimation setLoop: YES];
    [standAnimation setSpeed: 6];
    
    beginAttackAnimation = [[Animation alloc] init];
    [beginAttackAnimation addFrame: getImage(IMAGES_HERO_ATTACK_1)];
    [beginAttackAnimation addFrame: getImage(IMAGES_HERO_ATTACK_2)];
    [beginAttackAnimation addFrame: getImage(IMAGES_HERO_ATTACK_3)];
    [beginAttackAnimation addFrame: getImage(IMAGES_HERO_ATTACK_4)];
    [beginAttackAnimation setLoop: NO];
    [beginAttackAnimation setSpeed: HERO_ATTACK_SPEED];
    
    endAttackAnimation = [[Animation alloc] init];
    [endAttackAnimation addFrame: getImage(IMAGES_HERO_ATTACK_3)];
    [endAttackAnimation addFrame: getImage(IMAGES_HERO_ATTACK_2)];
    [endAttackAnimation addFrame: getImage(IMAGES_HERO_ATTACK_1)];
    [endAttackAnimation setLoop: NO];
    [endAttackAnimation setSpeed: HERO_ATTACK_SPEED];
    
    hurtAnimation = [[Animation alloc] init];
    [hurtAnimation addFrame: getImage(IMAGES_HERO_HURT_1)];
    [hurtAnimation addFrame: getImage(IMAGES_HERO_HURT_2)];
    [hurtAnimation addFrame: getImage(IMAGES_HERO_HURT_3)];
    [hurtAnimation addFrame: getImage(IMAGES_HERO_HURT_4)];
    [hurtAnimation addFrame: getImage(IMAGES_HERO_HURT_3)];
    [hurtAnimation addFrame: getImage(IMAGES_HERO_HURT_2)];
    [hurtAnimation addFrame: getImage(IMAGES_HERO_HURT_1)];
    [hurtAnimation setLoop: NO];
    [hurtAnimation setSpeed: 12];
    
    deadAnimation = [[Animation alloc] init];
    [deadAnimation addFrame: getImage(IMAGES_HERO_DIE_1)];
    [deadAnimation addFrame: getImage(IMAGES_HERO_DIE_2)];
    [deadAnimation addFrame: getImage(IMAGES_HERO_DIE_3)];
    [deadAnimation addFrame: getImage(IMAGES_HERO_DIE_4)];
    [deadAnimation addFrame: getImage(IMAGES_HERO_DIE_5)];
    [deadAnimation setLoop: NO];
    [deadAnimation setSpeed: 6];
    
    upKey = [[KeyControl alloc] initWithKey: KEY_UP];
    downKey = [[KeyControl alloc] initWithKey: KEY_DOWN];
    leftKey = [[KeyControl alloc] initWithKey: KEY_LEFT];
    rightKey = [[KeyControl alloc] initWithKey: KEY_RIGHT];
    waitKey = [[KeyControl alloc] initWithKey: KEY_SPACE];
    [waitKey setDelay: GAME_TICKER];
    attackKey = [[KeyControl alloc] initWithKey: KEY_LCONTROL];
    handKey = [[KeyControl alloc] initWithKey: KEY_0];
    [handKey setDelay: GAME_TICKER];
    shieldKey = [[KeyControl alloc] initWithKey: KEY_1];
    [shieldKey setDelay: GAME_TICKER];
    swordKey = [[KeyControl alloc] initWithKey: KEY_2];
    [swordKey setDelay: GAME_TICKER];
    bowKey = [[KeyControl alloc] initWithKey: KEY_3];
    [swordKey setDelay: GAME_TICKER];
    
    [self toStandState];
    [sword toHoldState];
    
    [self go]; // The hero doesn't wait! At least not when the game starts. ;-)
    
  }
  
  return self;
  
}


- (void) dealloc {
  [shield release];
  [sword release];
  [bow release];
  [standAnimation release];
  [beginAttackAnimation release];
  [endAttackAnimation release];
  [upKey release];
  [downKey release];
  [leftKey release];
  [rightKey release];
  [waitKey release];
  [attackKey release];
  [shieldKey release];
  [swordKey release];
  [bowKey release];
  [handKey release];
  [super dealloc];
}


- updateStandState {
  
  int toX;
  int toY;
  
  // Handle item key input.
  // Update the items.
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
  
  if ([attackKey isPressed]) {
    
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
    
  } else {
    
    // If you're not attacking with the attack key,
    // then maybe you are trying to walk...
    
    toX = x;
    toY = y;
    
    if ([upKey isPressed]) {
      toY--;
      if ([sword held] && [world isAttackableFromTeam: team atX: x andY: y - 1]) {
        direction = UP;
        [self toAttackState];
      }
    } else if ([downKey isPressed]) {
      toY++;
      if ([sword held] && [world isAttackableFromTeam: team atX: toX andY: toY]) {
        direction = DOWN;
        [self toAttackState];
      }
    } else if ([leftKey isPressed]) {
      toX--;
      if ([sword held] && [world isAttackableFromTeam: team atX: toX andY: toY]) {
        direction = LEFT;
        [self toAttackState];
      }
    } else if ([rightKey isPressed]) {
      toX++;
      if ([sword held] && [world isAttackableFromTeam: team atX: toX andY: toY]) {
        direction = RIGHT;
        [self toAttackState];
      }
    }
    
    if ([world isWalkableAtX: toX andY: toY] && ![world isInhabitedAtX: toX andY: toY]) {
      
      [self moveX: toX];
      [self moveY: toY];
      [self toMoveState];
      [self wait];
      
      // If the hero is holding the shield
      // then make him wait another turn.
      if ([shield held]) {
        [self wait];
      }
      
    }
    
  }
  
  return self;
  
}


- update {
  
  [super update];
  [shield update];
  [sword update];
  [bow update];
  
  if ([self waiting]) {
    return self;
  }
  
  if ([waitKey isPressed]) {
    [self wait];
  }
  
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
      [[bow getArrow] release];
      [bow setArrow: nil];
      [self toStandState];
      [self wait];
    }
    break;
    
  }
  
  return self;
  
}


- draw: (BITMAP *) buffer {
  [super draw: buffer];
  [shield draw: buffer];
  [sword draw: buffer];
  [bow draw: buffer];
  return self;
}


- emptyHands {
  [shield toAwayState];
  [sword toAwayState];
  [bow toAwayState];
  return self;
}


- toStandState {
  state = HERO_STAND_STATE;
  animation = standAnimation;
  return self;
}


- toMoveState {
  state = HERO_MOVE_STATE;
  animation = standAnimation;
  return self;
}


- toAttackState {
  state = HERO_ATTACK_STATE;
  animation = standAnimation;
  return self;
}


- toHurtState {
  
  state = HERO_HURT_STATE;
  animation = hurtAnimation;
  [animation reset];
  
  // You can't shoot an arrow if you get
  // hurt whil trying to do it.
  [[bow getArrow] release];
  [bow setArrow: nil];
  if ([bow held]) {
    [bow toHoldState];
  }
  
  playSound(SOUNDS_GASP);
  
  return self;
  
}


- toDeadState {
  state = HERO_DEAD_STATE;
  animation = deadAnimation;
  [animation reset];
  return self;
}


- toPushSwordState {
  state = HERO_PUSH_SWORD_STATE;
  animation = beginAttackAnimation;
  [animation reset];
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
  return self;
}


- toPullSwordState {
  state = HERO_PULL_SWORD_STATE;
  animation = endAttackAnimation;
  [animation reset];
  return self;
}


- toDrawBowState {
  
  state = HERO_DRAW_BOW_STATE;
  animation = beginAttackAnimation;
  [animation reset];
  
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
  
  return self;
  
}


- toShootArrowState {
  state = HERO_SHOOT_ARROW_STATE;
  animation = endAttackAnimation;
  [animation reset];
  [[bow getArrow] toFlyingState];
  [bow toHoldState];
  return self;
}


- hurt {
  if (![shield held]) {
    [self toHurtState];
    [super hurt];
  }
  return self;
}


- (BOOL) isDead {
  if (state == HERO_DEAD_STATE && [animation finished]) {
    return YES;
  }
  return NO;
}


- setX: (int) newX {
  [super setX: newX];
  [shield setX: newX];
  [sword setX: newX];
  [bow setX: newX];
  return self;
}


- setY: (int) newY {
  [super setY: newY];
  [shield setY: newY];
  [sword setY: newY];
  [bow setY: newY];
  return self;
}


- moveX: (int) newX {
  [super moveX: newX];
  [shield moveX: newX];
  [sword moveX: newX];
  [bow moveX: newX];
  return self;
}


- moveY: (int) newY {
  [super moveY: newY];
  [shield moveY: newY];
  [sword moveY: newY];
  [bow moveY: newY];
  return self;
}


@end
