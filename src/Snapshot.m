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
#import "Snapshot.h"


@implementation Snapshot


- init {
  
  self = [super init];
  
  if (self) {
    canvas = create_bitmap(getScreenWidth(), getScreenHeight());
  }
  
  return self;
  
}


- free {
  destroy_bitmap(canvas);
  return [super free];
}


- update {
  
  if ([self moving]) {
    
    if (speed > 0) {
      
      fudge += speed;
      
      while (fudge >= GAME_TICKER) {
        if (visualX != x) {
          if (visualX < x) {
            visualX++;
          } else {
            visualX--;
          }
        }
        if (visualY != y) {
          if (visualY < y) {
            visualY++;
          } else {
            visualY--;
          }
        }
        fudge -= GAME_TICKER;
      }
      
    } else {
      visualX = x;
      visualY = y;
    }
    
    if (![self moving]) {
      fudge = 0;
    }
    
  }
  
  return self;
  
}


- draw: (BITMAP *) buffer {
  draw_sprite(buffer, [self getCanvas], visualX, visualY);
  return self;
}


- (BITMAP *) getCanvas {
  return canvas;
}


- (BOOL) moving {
  if (visualX != x || visualY != y) {
    return YES;
  }
  return NO;
}


- setX: (int) newX {
  x = newX;
  visualX = x;
  return self;
}


- setY: (int) newY {
  y = newY;
  visualY = y;
  return self;
}


@end
