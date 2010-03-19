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
#import "Sprite.h"


@implementation Sprite


- init {
  
  self = [super init];
  
  if (self) {
    x = 0;
    y = 0;
    w = 1;
    h = 1;
    visualX = 0;
    visualY = 0;
    fudge = 0;
    speed = 0;
    animation = nil;
    world = nil;
    state = 0;
  }
  
  return self;
  
}


- update {
  
  [animation update];
  
  // This will make the visual position of the sprite match up
  // with the actual position of the sprite at the right speed.
  if ([self moving]) {
    
    if (speed > 0) {
      
      fudge += speed;
      
      while (fudge >= GAME_TICKER) {
        if (visualX != x * TILE_SIZE) {
          if (visualX < x * TILE_SIZE) {
            visualX++;
          } else {
            visualX--;
          }
        }
        if (visualY != y * TILE_SIZE) {
          if (visualY < y * TILE_SIZE) {
            visualY++;
          } else {
            visualY--;
          }
        }
        fudge -= GAME_TICKER;
      }
      
    } else {
      visualX = x * TILE_SIZE;
      visualY = y * TILE_SIZE;
    }
    
    if (![self moving]) {
      fudge = 0;
    }
    
  }
  
  return self;
  
}


- draw: (BITMAP *) buffer {
  
  // Add a shadow.
  /*
  hline(buffer, visualX + 6, visualY + 30, visualX + 33, BLACK);
  hline(buffer, visualX + 6, visualY + 31, visualX + 33, BLACK);
  hline(buffer, visualX + 4, visualY + 32, visualX + 35, BLACK);
  hline(buffer, visualX + 4, visualY + 33, visualX + 35, BLACK);
  hline(buffer, visualX + 6, visualY + 34, visualX + 33, BLACK);
  hline(buffer, visualX + 6, visualY + 35, visualX + 33, BLACK);
  */
  
  [animation drawTo: buffer atX: visualX andY: visualY];
  
  return self;
  
}


- (BOOL) moving {
  if (visualX != x * TILE_SIZE || visualY != y * TILE_SIZE) {
    return YES;
  }
  return NO;
}


- boundAtTop: (int) top andBottom: (int) bottom andLeft: (int) left andRight: (int) right {
  
  if (x < left) {
    [self moveX: left];
  } else if (x + w - 1 > right) {
    [self moveX: right];
  }
  
  if (y < top) {
    [self moveY: top];
  } else if (y + h - 1 > bottom) {
    [self moveY: bottom];
  }
  
  return self;
  
}


- (int) getX {
  return x;
}


- (int) getY {
  return y;
}


- setX: (int) newX {
  x = newX;
  visualX = x * TILE_SIZE;
  return self;
}


- setY: (int) newY {
  y = newY;
  visualY = y * TILE_SIZE;
  return self;
}


- moveX: (int) newX {
  x = newX;
  return self;
}


- moveY: (int) newY {
  y = newY;
  return self;
}


- (int) getWidth {
  return w;
}


- (int) getHeight {
  return h;
}


- setWorld: (id<Inhabitable, Targetable, Traversable>) aWorld {
  world = aWorld;
  return self;
}


- setState: (int) aState {
  state = aState;
  return self;
}


- setSpeed: (int) theSpeed {
  speed = theSpeed;
  return self;
}


@end

