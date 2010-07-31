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
#import "KeyControl.h"


@implementation KeyControl


- initWithKey: (int) aKey {
  self = [super init];
  if (self) {
    keyCode = aKey;
    released = YES;
    timer = 0;
    delay = 0; //GAME_TICKER / 4;
  }
  return self;
}


- (BOOL) isPressed {
  
  BOOL ret = NO;
  
  if (delay == 0 && key[keyCode]) {
    return YES;
  }
  
  if (key[keyCode]) {
    if (released) {
      
      ret = YES;
      timer = 0;
      
    } else {
      timer++;
    }
    
    released = NO;
    
    if (timer >= delay) {
      released = YES;
    }
    
  } else {
    released = YES;
  }
  
  return ret;
  
}


- setDelay: (BOOL) theDelay {
  delay = theDelay;
  return self;
}


@end

