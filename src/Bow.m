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
#import "Bow.h"


typedef enum {
  BOW_HOLD_STATE,
  BOW_AWAY_STATE
} BOW_STATE;


@implementation Bow


- init {
  
  self = [super init];
  
  if (self) {
    
    arrow = nil;
    
    holdAnimation = [[Animation alloc] init];
    [holdAnimation addFrame: getImage(BOW_01_BMP)];
    [holdAnimation addFrame: getImage(BOW_02_BMP)];
    [holdAnimation addFrame: getImage(BOW_03_BMP)];
    [holdAnimation addFrame: getImage(BOW_04_BMP)];
    [holdAnimation setLoop: YES];
    [holdAnimation setSpeed: 6];
	
    attackRightAnimation = [[Animation alloc] init];
    [attackRightAnimation addFrame: getImage(BOW_ATTACK_01_BMP)];
    [attackRightAnimation addFrame: getImage(BOW_ATTACK_02_BMP)];
    [attackRightAnimation addFrame: getImage(BOW_ATTACK_03_BMP)];
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
  [arrow free];
  return [super free];
}


- update {
  [super update];
  [arrow update];
  return self;
}


- draw: (BITMAP *) buffer {
  [super draw: buffer];
  [arrow draw: buffer];
  return self;
}


- setArrow: (Arrow *) anArrow {
  arrow = anArrow;
  return self;
}


- (Arrow *) getArrow {
  return arrow;
}


- setArrowWithX: (int) newX
    andY: (int) newY
    andDirection: (int) aDirection
    andTeam: (int) aTeam
    andWorld: (id<Inhabitable, Targetable, Traversable>) aWorld {
  
  arrow = [[Arrow alloc] init];
  [arrow setTeam: aTeam];
  [arrow setX: newX];
  [arrow setY: newY];
  [arrow setWorld: aWorld];
  [arrow setDirection: aDirection];
  [arrow toHoldState];
  
  return self;
  
}


- toHoldState {
  state = BOW_HOLD_STATE;
  animation = holdAnimation;
  return self;
}


- toAwayState {
  state = BOW_AWAY_STATE;
  animation = nil;
  return self;
}


- toAttackUpState {
  animation = attackUpAnimation;
  [animation reset];
  return self;
}


- toAttackDownState {
  animation = attackDownAnimation;
  [animation reset];
  return self;
}


- toAttackLeftState {
  animation = attackLeftAnimation;
  [animation reset];
  return self;
}


- toAttackRightState {
  animation = attackRightAnimation;
  [animation reset];
  return self;
}


- (BOOL) held {
  if (state != BOW_AWAY_STATE) {
    return YES;
  }
  return NO;
}


@end

