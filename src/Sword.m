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
#import "Sword.h"


typedef enum {
  SWORD_HOLD_STATE,
  SWORD_AWAY_STATE
} SWORD_STATE;

typedef enum {
  SWORD_ATTACK_UP_STATE,
  SWORD_ATTACK_DOWN_STATE,
  SWORD_ATTACK_LEFT_STATE,
  SWORD_ATTACK_RIGHT_STATE
} SWORD_ATTACK_STATE;


@implementation Sword


- init {
  
  self = [super init];
  
  if (self) {
    
    holdAnimation = [[Animation alloc] init];
    [holdAnimation addFrame: getImage(IMG_SWORD_HOLD_1)];
    [holdAnimation addFrame: getImage(IMG_SWORD_HOLD_2)];
    [holdAnimation addFrame: getImage(IMG_SWORD_HOLD_3)];
    [holdAnimation addFrame: getImage(IMG_SWORD_HOLD_4)];
    [holdAnimation setLoop: YES];
    [holdAnimation setSpeed: 6];
    
    attackRightAnimation = [[Animation alloc] init];
    [attackRightAnimation addFrame: getImage(IMG_SWORD_STAB_1)];
    [attackRightAnimation addFrame: getImage(IMG_SWORD_STAB_2)];
    [attackRightAnimation addFrame: getImage(IMG_SWORD_STAB_3)];
    [attackRightAnimation addFrame: getImage(IMG_SWORD_STAB_4)];
    [attackRightAnimation addFrame: getImage(IMG_SWORD_STAB_3)];
    [attackRightAnimation addFrame: getImage(IMG_SWORD_STAB_2)];
    [attackRightAnimation addFrame: getImage(IMG_SWORD_STAB_1)];
    [attackRightAnimation setOffsetX: -TILE_SIZE];
    [attackRightAnimation setOffsetY: -TILE_SIZE];
    [attackRightAnimation setLoop: NO];
    [attackRightAnimation setSpeed: 12];
    
    attackLeftAnimation = [[attackRightAnimation copy] setHorizontalFlip: YES];
    attackDownAnimation = [[attackRightAnimation copy] setRotate: YES];
    attackUpAnimation = [[[attackRightAnimation copy] setHorizontalFlip: YES] setRotate: YES];
    
    [self toAwayState];
    
  }
  
  return self;
  
}


- free {
  [holdAnimation free];
  [attackUpAnimation free];
  [attackDownAnimation free];
  [attackLeftAnimation free];
  [attackRightAnimation free];
  return [super free];
}


- toHoldState {
  state = SWORD_HOLD_STATE;
  animation = holdAnimation;
  return self;
}


- toAwayState {
  state = SWORD_AWAY_STATE;
  animation = nil;
  return self;
}


- toAttackUpState {
  animation = attackUpAnimation;
  [animation reset];
  playSound(SND_SWORD);
  return self;
}


- toAttackDownState {
  animation = attackDownAnimation;
  [animation reset];
  playSound(SND_SWORD);
  return self;
}


- toAttackLeftState {
  animation = attackLeftAnimation;
  [animation reset];
  playSound(SND_SWORD);
  return self;
}


- toAttackRightState {
  animation = attackRightAnimation;
  [animation reset];
  playSound(SND_SWORD);
  return self;
}


- (BOOL) held {
  if (state == SWORD_HOLD_STATE) {
    return YES;
  }
  return NO;
}


@end

