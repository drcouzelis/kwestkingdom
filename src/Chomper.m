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
#import "Chomper.h"


typedef enum {
  CHOMPER_STAND_STATE,
  CHOMPER_ATTACK_STATE,
  CHOMPER_MOVE_STATE
} CHOMPER_STATE;


@implementation Chomper


- init {
  
  self = [super init];
  
  if (self) {
    
    prevDirection = UP;
    
    standAnimation = [[Animation alloc] init];
    [standAnimation addFrame: getImage(CHOMPER_01_BMP)];
    [standAnimation addFrame: getImage(CHOMPER_02_BMP)];
    [standAnimation addFrame: getImage(CHOMPER_03_BMP)];
    [standAnimation addFrame: getImage(CHOMPER_02_BMP)];
    [standAnimation setLoop: YES];
    [standAnimation setSpeed: 6];
    
    attackAnimation = [[Animation alloc] init];
    [attackAnimation addFrame: getImage(CHOMPER_ATTACK_01_BMP)];
    [attackAnimation addFrame: getImage(CHOMPER_ATTACK_02_BMP)];
    [attackAnimation addFrame: getImage(CHOMPER_ATTACK_03_BMP)];
    [attackAnimation addFrame: getImage(CHOMPER_ATTACK_04_BMP)];
    [attackAnimation addFrame: getImage(CHOMPER_ATTACK_05_BMP)];
    [attackAnimation addFrame: getImage(CHOMPER_ATTACK_04_BMP)];
    [attackAnimation addFrame: getImage(CHOMPER_ATTACK_03_BMP)];
    [attackAnimation addFrame: getImage(CHOMPER_ATTACK_02_BMP)];
    [attackAnimation addFrame: getImage(CHOMPER_ATTACK_01_BMP)];
    [attackAnimation setLoop: NO];
    [attackAnimation setSpeed: 20];
    
    animation = standAnimation;
    state = CHOMPER_STAND_STATE;
    [self wait];
    
  }
  
  return self;
  
}


- free {
  [standAnimation free];
  [attackAnimation free];
  return [super free];
}


- update {
  
  int dir;
  int toX;
  int toY;
  id<Positionable> target;
  
  [super update];
  
  if ([self waiting]) {
    return self;
  }
  
  if (health == 0) {
    return self;
  }
  
  target = [world getTarget];
  
  switch (state) {
  
  case CHOMPER_STAND_STATE:
    
	// If the target has a walking distance of one...
    if (abs(x - [target getX]) + abs(y - [target getY]) == 1) {
	  
      state = CHOMPER_ATTACK_STATE;
      animation = attackAnimation;
      [animation reset];
      playSound(CHOMP_SOUND);
      
    } else {
      
      if (abs(x - [target getX]) < 4 && abs(y - [target getY]) < 4) {
        if (abs(x - [target getX]) < abs(y - [target getY])) {
          if (y - [target getY] > 0) {
            dir = UP;
          } else {
            dir = DOWN;
          }
        } else if (abs(x - [target getX]) > abs(y - [target getY])) {
          if (x - [target getX] > 0) {
            dir = LEFT;
          } else {
            dir = RIGHT;
          }
        } else {
          if (x - [target getX] < 0 && y - [target getY] > 0) { // NE
            if (prevDirection == UP) {
              dir = RIGHT;
            } else {
              dir = UP;
            }
          } else if (x - [target getX] < 0 && y - [target getY] < 0) { // SE
            if (prevDirection == DOWN) {
              dir = RIGHT;
            } else {
              dir = DOWN;
            }
          } else if (x - [target getX] > 0 && y - [target getY] > 0) { // NW
            if (prevDirection == UP) {
              dir = LEFT;
            } else {
              dir = UP;
            }
          } else { // SW
            if (prevDirection == DOWN) {
              dir = LEFT;
            } else {
              dir = DOWN;
            }
          }
        }
      } else {
        dir = random_number(UP, LEFT);
      }
      
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
        state = CHOMPER_MOVE_STATE;
      }
      
      // Bound him so he doesn't wander right out of the screen!
      [self boundAtTop: 1 andBottom: ROWS - 2 andLeft: 1 andRight: COLS - 2];
      
      prevDirection = dir;
      
      [self wait];
      
    }
    
    break;
    
  case CHOMPER_MOVE_STATE:
    if (![self moving]) {
      state = CHOMPER_STAND_STATE;
    }
    break;
    
  case CHOMPER_ATTACK_STATE:
    if ([animation finished]) {
      [world attackFromTeam: team atX: [target getX] andY: [target getY]];
      state = CHOMPER_STAND_STATE;
      animation = standAnimation;
      [animation reset];
      [self wait];
    }
	break;
	
  }
  
  return self;
  
}


@end

