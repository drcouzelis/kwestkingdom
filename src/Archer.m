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
#import "Archer.h"


typedef enum {
  ARCHER_STAND_STATE,
  ARCHER_ATTACK_STATE,
  ARCHER_MOVE_STATE,
  ARCHER_DRAW_BOW_STATE,
  ARCHER_SHOOT_ARROW_STATE
} ARCHER_STATE;


@implementation Archer


- init {
  
  self = [super init];
  
  if (self) {
    
    x = 0;
    y = 0;
    
    speed = 120;
    team = ENEMY_TEAM;
    
    bow = [[Bow alloc] init];
    [bow setSpeed: speed];
    [bow toHoldState];
    
    standAnimation = [[Animation alloc] init];
    [standAnimation addFrame: getImage(ARCHER_01_BMP)];
    [standAnimation addFrame: getImage(ARCHER_02_BMP)];
    [standAnimation addFrame: getImage(ARCHER_03_BMP)];
    [standAnimation addFrame: getImage(ARCHER_02_BMP)];
    [standAnimation setLoop: YES];
    [standAnimation setSpeed: 3];
    
    beginAttackAnimation = [[Animation alloc] init];
    [beginAttackAnimation addFrame: getImage(ARCHER_01_BMP)];
    [beginAttackAnimation addFrame: getImage(ARCHER_02_BMP)];
    [beginAttackAnimation addFrame: getImage(ARCHER_02_BMP)];
    [beginAttackAnimation addFrame: getImage(ARCHER_03_BMP)];
    [beginAttackAnimation setLoop: NO];
    [beginAttackAnimation setSpeed: 12];
    
    endAttackAnimation = [[Animation alloc] init];
    [endAttackAnimation addFrame: getImage(ARCHER_03_BMP)];
    [endAttackAnimation addFrame: getImage(ARCHER_02_BMP)];
    [endAttackAnimation addFrame: getImage(ARCHER_02_BMP)];
    [endAttackAnimation setLoop: NO];
    [endAttackAnimation setSpeed: 12];
    
    animation = standAnimation;
    state = ARCHER_STAND_STATE;
    direction = UP;
    [self wait];
    
  }
  
  return self;
  
}


- free {
  [bow free];
  [standAnimation free];
  [beginAttackAnimation free];
  [endAttackAnimation free];
  return [super free];
}


- update {
  
  int dir;
  int toX;
  int toY;
  id<Positionable> target;
  
  [super update];
  [bow update];
  
  if ([self waiting]) {
    return self;
  }
  
  if (health == 0) {
    return self;
  }
  
  target = [world getTarget];
  
  switch (state) {
  
  case ARCHER_STAND_STATE:
    
    if (x == [target getX]) {
      
      if (y > [target getY]) { // Hero is up.
        direction = UP;
      } else { // Hero is down.
        direction = DOWN;
      }
      
      [self toDrawBowState];
      [self wait];
      
    } else if (y == [target getY]) {
      
      if (x > [target getX]) { // Hero is left.
        direction = LEFT;
      } else { // Hero is right.
        direction = RIGHT;
      }
      
      [self toDrawBowState];
      [self wait];
      
    } else if ((x == [target getX] - 1 || x == [target getX] + 1) && random_number(0, 1) == 1) {
      
      if (y > [target getY]) { // Hero is up.
        direction = UP;
      } else { // Hero is down.
        direction = DOWN;
      }
      
      [self toDrawBowState];
      [self wait];
      
    } else if ((y == [target getY] - 1 || y == [target getY] + 1) && random_number(0, 1) == 1) {
      
      if (x > [target getX]) { // Hero is left.
        direction = LEFT;
      } else { // Hero is right.
        direction = RIGHT;
      }
      
      [self toDrawBowState];
      [self wait];
      
    } else {
      
      // Wander aimlessly
      dir = random_number(UP, /*DOWN, LEFT,*/ RIGHT);
      
      toX = x;
      toY = y;
      
      if (dir == UP) {
        toY--;
      } else if (dir == DOWN) {
        toY++;
      } else if (dir == RIGHT) {
        toX++;
      } else if (dir == LEFT) {
        toX--;
      }
      
      if ([world isWalkableAtX: toX andY: toY] && ![world isInhabitedAtX: toX andY: toY]) {
        [self moveX: toX];
        [self moveY: toY];
        [self toMoveState];
      }
      
      [self wait];
      
    }
    
    // Bound him so he doesn't wander right out of the screen!
    [self boundAtTop: 1 andBottom: ROWS - 2 andLeft: 1 andRight: COLS - 2];
    
    break;
    
  case ARCHER_MOVE_STATE:
    if (![self moving]) {
      [self toStandState];
    }
    break;
    
  case ARCHER_DRAW_BOW_STATE:
    if ([animation finished]) {
      [self toShootArrowState];
    }
    break;
    
  case ARCHER_SHOOT_ARROW_STATE:
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
  
  return self;
  
}


- draw: (BITMAP *) buffer {
  [super draw: buffer];
  [bow draw: buffer];
  return self;
}


- toStandState {
  state = ARCHER_STAND_STATE;
  animation = standAnimation;
  return self;
}


- toMoveState {
  state = ARCHER_MOVE_STATE;
  animation = standAnimation;
  return self;
}


- toDrawBowState {
  
  state = ARCHER_DRAW_BOW_STATE;
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
  state = ARCHER_SHOOT_ARROW_STATE;
  animation = endAttackAnimation;
  [animation reset];
  [[bow getArrow] toFlyingState];
  [bow toHoldState];
  return self;
}


- setX: (int) newX {
  [super setX: newX];
  [bow setX: newX];
  return self;
}


- setY: (int) newY {
  [super setY: newY];
  [bow setY: newY];
  return self;
}


- moveX: (int) newX {
  [super moveX: newX];
  [bow moveX: newX];
  return self;
}


- moveY: (int) newY {
  [super moveY: newY];
  [bow moveY: newY];
  return self;
}


@end
