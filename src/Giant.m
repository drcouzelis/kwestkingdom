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
#import "Giant.h"


typedef enum {
  GIANT_STAND_STATE,
  GIANT_ATTACK_STATE,
  GIANT_MOVE_STATE
} GIANT_STATE;


@implementation Giant


- init {
  
  self = [super init];
  
  if (self) {
    
    x = 0;
    y = 0;
    
    w = 2;
    h = 2;
    
    speed = 120;
    maxHealth = 5;
    health = 5;
    team = ENEMY_TEAM;
    
    hammer = [[Hammer alloc] init];
    [hammer setSpeed: speed];
    [hammer setState: HAMMER_HOLD_STATE];
    
    standAnimation = [[Animation alloc] init];
    [standAnimation addFrame: getImage(GIANT_01_BMP)];
    [standAnimation addFrame: getImage(GIANT_02_BMP)];
    [standAnimation addFrame: getImage(GIANT_03_BMP)];
    [standAnimation addFrame: getImage(GIANT_02_BMP)];
    [standAnimation setLoop: YES];
    [standAnimation setSpeed: 3];
    
    attackAnimation = [[Animation alloc] init];
    [attackAnimation addFrame: getImage(GIANT_01_BMP)];
    [attackAnimation addFrame: getImage(GIANT_02_BMP)];
    [attackAnimation addFrame: getImage(GIANT_02_BMP)];
    [attackAnimation addFrame: getImage(GIANT_03_BMP)];
    [attackAnimation addFrame: getImage(GIANT_03_BMP)];
    [attackAnimation addFrame: getImage(GIANT_03_BMP)];
    [attackAnimation addFrame: getImage(GIANT_03_BMP)];
    [attackAnimation addFrame: getImage(GIANT_03_BMP)];
    [attackAnimation addFrame: getImage(GIANT_02_BMP)];
    [attackAnimation addFrame: getImage(GIANT_02_BMP)];
    [attackAnimation setLoop: NO];
    [attackAnimation setSpeed: 24];
    
    animation = standAnimation;
    state = GIANT_STAND_STATE;
    [self setMoney: 5];
    [self wait];
    
  }
  
  return self;
  
}


- free {
  [hammer free];
  [standAnimation free];
  [attackAnimation free];
  return [super free];
}


- (BOOL) target: (id<Positionable>) target isInRange: (int) range {
  
  if (
    abs(x - [target getX]) + abs(y - [target getY]) <= range ||
    abs(x + 1 - [target getX]) + abs(y - [target getY]) <= range ||
    abs(x - [target getX]) + abs(y + 1 - [target getY]) <= range ||
    abs(x + 1 - [target getX]) + abs(y + 1 - [target getY]) <= range
  ) {
    
    return YES;
    
  }
  
  return NO;
      
}


- (int) directionToTarget: (id<Positionable>) target {
  
  if ( // Up
    (x == [target getX] && y == [target getY] + 1) ||
    (x + 1 == [target getX] && y == [target getY] + 1)
  ) {
    
    return UP;
    
  } else if ( // Down
    (x == [target getX] && y == [target getY] - 2) ||
    (x + 1 == [target getX] && y == [target getY] - 2)
  ) {
    
    return DOWN;
    
  } else if ( // Left
    (x == [target getX] + 1 && y == [target getY]) ||
    (x == [target getX] + 1 && y + 1 == [target getY])
  ) {
    
    return LEFT;
    
  } else if ( // Right
    (x == [target getX] - 2 && y == [target getY]) ||
    (x == [target getX] - 2 && y + 1 == [target getY])
  ) {
    
    return RIGHT;
    
  }
  
  return UP;
  
}


- (BOOL) isMeAtX: (int) atX andY: (int) atY {
  if (
    (x == atX && y == atY) ||
    (x + 1 == atX && y == atY) ||
    (x == atX && y + 1 == atY) ||
    (x + 1 == atX && y + 1 == atY)
  ) {
    
    return YES;
    
  }
  
  return NO;
  
}


- (BOOL) canWalkToX: (int) toX andY: (int) toY {
  
  if (
    ![world isWalkableAtX: toX andY: toY] ||
    ![world isWalkableAtX: toX + 1 andY: toY] ||
    ![world isWalkableAtX: toX andY: toY + 1] ||
    ![world isWalkableAtX: toX + 1 andY: toY + 1] ||
    ([world isInhabitedAtX: toX andY: toY] && ![self isMeAtX: toX andY: toY]) ||
    ([world isInhabitedAtX: toX + 1 andY: toY] && ![self isMeAtX: toX + 1 andY: toY]) ||
    ([world isInhabitedAtX: toX andY: toY + 1] && ![self isMeAtX: toX andY: toY + 1]) ||
    ([world isInhabitedAtX: toX + 1 andY: toY + 1] && ![self isMeAtX: toX + 1 andY: toY + 1])
  ) {
    
    return NO;
    
  }
  
  return YES;
  
}


- update {
  
  int dir;
  int toX;
  int toY;
  id<Positionable> target;
  
  [super update];
  [hammer update];
  
  if ([self waiting]) {
    return self;
  }
  
  if (health == 0) {
    return self;
  }
  
  target = [world getTarget];
  
  switch (state) {
  
  case GIANT_STAND_STATE:
    
    // If the target has a walking distance of one...
    if ([self target: target isInRange: 1]) {
      
      state = GIANT_ATTACK_STATE;
      animation = attackAnimation;
      [animation reset];
      
      // Change the state of the hammer.
      if ([self directionToTarget: target] == UP) {
        [hammer setState: HAMMER_ATTACK_UP_STATE];
      } else if ([self directionToTarget: target] == DOWN) {
        [hammer setState: HAMMER_ATTACK_DOWN_STATE];
      } else if ([self directionToTarget: target] == LEFT) {
        [hammer setState: HAMMER_ATTACK_LEFT_STATE];
      } else if ([self directionToTarget: target] == RIGHT) {
        [hammer setState: HAMMER_ATTACK_RIGHT_STATE];
      }
      
    } else if (/* Hero is nearby */ NO) {
      
      // Then chase the hero!
      
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
      
      if ([self canWalkToX: toX andY: toY]) {
        
        [self moveX: toX];
        [self moveY: toY];
        state = GIANT_MOVE_STATE;
        
      }
      
      [self wait];
      
    }
    
    // Bound him so he doesn't wander right out of the screen!
    [self boundAtTop: 1 andBottom: ROWS - 2 andLeft: 1 andRight: COLS - 2];
    
    break;
    
  case GIANT_MOVE_STATE:
    if (![self moving]) {
      state = GIANT_STAND_STATE;
    }
    break;
    
  case GIANT_ATTACK_STATE:
    if ([animation finished]) {
      // Send the hero soaring!
      [world attackFromTeam: team atX: [target getX] andY: [target getY]];
      
      state = GIANT_STAND_STATE;
      animation = standAnimation;
      [animation reset];
      [hammer setState: HAMMER_HOLD_STATE];
      [self wait];
    }
    break;
    
  }
  
  return self;
  
}


- draw: (BITMAP *) buffer {
  [super draw: buffer];
  [hammer draw: buffer];
  return self;
}


- setX: (int) newX {
  [super setX: newX];
  [hammer setX: newX];
  return self;
}


- setY: (int) newY {
  [super setY: newY];
  [hammer setY: newY];
  return self;
}


- moveX: (int) newX {
  [super moveX: newX];
  [hammer moveX: newX];
  return self;
}


- moveY: (int) newY {
  [super moveY: newY];
  [hammer moveY: newY];
  return self;
}


- dropItem {
  y++;
  [super dropItem];
  y--;
  return self;
}


- setWorld: (id<Inhabitable, Targetable, Traversable>) aWorld {
  world = aWorld;
  [hammer setWorld: world];
  return self;
}


@end
