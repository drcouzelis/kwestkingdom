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
#import "Hammer.h"


@implementation Hammer


- init {
  
  self = [super init];
  
  if (self) {
    
    holdAnimation = [[Animation alloc] init];
    [holdAnimation addFrame: getImage(HAMMER_01_BMP)];
    [holdAnimation addFrame: getImage(HAMMER_02_BMP)];
    [holdAnimation addFrame: getImage(HAMMER_03_BMP)];
    [holdAnimation addFrame: getImage(HAMMER_04_BMP)];
    [holdAnimation setOffsetY: TILE_SIZE];
    [holdAnimation setLoop: YES];
    [holdAnimation setSpeed: 6];
    
    attackRightAnimation = [[Animation alloc] init];
    [attackRightAnimation addFrame: getImage(HAMMER_ATTACK_01_BMP)];
    [attackRightAnimation addFrame: getImage(HAMMER_ATTACK_02_BMP)];
    [attackRightAnimation addFrame: getImage(HAMMER_ATTACK_03_BMP)];
    [attackRightAnimation addFrame: getImage(HAMMER_ATTACK_04_BMP)];
    [attackRightAnimation addFrame: getImage(HAMMER_ATTACK_04_BMP)];
    [attackRightAnimation addFrame: getImage(HAMMER_ATTACK_04_BMP)];
    [attackRightAnimation addFrame: getImage(HAMMER_ATTACK_04_BMP)];
    [attackRightAnimation addFrame: getImage(HAMMER_ATTACK_03_BMP)];
    [attackRightAnimation addFrame: getImage(HAMMER_ATTACK_02_BMP)];
    [attackRightAnimation addFrame: getImage(HAMMER_ATTACK_01_BMP)];
    [attackRightAnimation setOffsetX: TILE_SIZE];
    [attackRightAnimation setLoop: NO];
    [attackRightAnimation setSpeed: 24];
    
    attackLeftAnimation = [[attackRightAnimation copy] setHorizontalFlip: YES];
    [attackLeftAnimation setOffsetX: -TILE_SIZE * 2];
    attackDownAnimation = [[attackRightAnimation copy] setRotate: YES];
    [attackDownAnimation setOffsetX: 0];
    [attackDownAnimation setOffsetY: TILE_SIZE];
    attackUpAnimation = [[[[attackRightAnimation copy] setHorizontalFlip: YES] setVerticalFlip: YES] setRotate: YES];
    [attackUpAnimation setOffsetX: -TILE_SIZE];
    [attackUpAnimation setOffsetY: -TILE_SIZE * 2];
    
    [self setState: HAMMER_AWAY_STATE];
    
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


- update {
  
  [super update];
  
  switch (state) {
  case HAMMER_ATTACK_UP_STATE:
  case HAMMER_ATTACK_DOWN_STATE:
  case HAMMER_ATTACK_LEFT_STATE:
  case HAMMER_ATTACK_RIGHT_STATE:
    if ([animation currentFrameNumber] == 3) {
      [self setState: HAMMER_END_ATTACK_STATE];
    }
    break;
  }
  
  return self;
  
}



- setState: (int) aState {
  
  state = aState;
  
  switch (state) {
  
  case HAMMER_HOLD_STATE:
    animation = holdAnimation;
    break;
    
  case HAMMER_AWAY_STATE:
    animation = nil;
    break;
    
  case HAMMER_ATTACK_UP_STATE:
    animation = attackUpAnimation;
    [animation reset];
    break;
    
  case HAMMER_ATTACK_DOWN_STATE:
    animation = attackDownAnimation;
    [animation reset];
    break;
    
  case HAMMER_ATTACK_LEFT_STATE:
    animation = attackLeftAnimation;
    [animation reset];
    break;
    
  case HAMMER_ATTACK_RIGHT_STATE:
    animation = attackRightAnimation;
    [animation reset];
    break;
    
  case HAMMER_END_ATTACK_STATE:
    playSound(HAMMER_ATTACK_SOUND);
    [world shake];
    break;
    
  }
  
  return self;
  
}


- (BOOL) held {
  if (state == HAMMER_HOLD_STATE) {
    return YES;
  }
  return NO;
}


@end

