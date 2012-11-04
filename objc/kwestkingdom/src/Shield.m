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
#import "Shield.h"


typedef enum {
  SHIELD_HOLD_STATE,
  SHIELD_AWAY_STATE
} SHIELD_STATE;


@implementation Shield


- init {
  
  self = [super init];
  
  if (self) {
    
    holdAnimation = [[Animation alloc] init];
    [holdAnimation addFrame: getImage(IMG_SHIELD_1)];
    [holdAnimation addFrame: getImage(IMG_SHIELD_2)];
    [holdAnimation addFrame: getImage(IMG_SHIELD_3)];
    [holdAnimation addFrame: getImage(IMG_SHIELD_4)];
    [holdAnimation setLoop: YES];
    [holdAnimation setSpeed: 6];
	
    [self toAwayState];
    
  }
  
  return self;
  
}


- (void) dealloc {
  [holdAnimation release];
  [super dealloc];
}


- toHoldState {
  state = SHIELD_HOLD_STATE;
  animation = holdAnimation;
  return self;
}


- toAwayState {
  state = SHIELD_AWAY_STATE;
  animation = nil;
  return self;
}


- (BOOL) held {
  if (state == SHIELD_HOLD_STATE) {
    return YES;
  }
  return NO;
}


@end

