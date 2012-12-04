#include "Sprite.h"


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
        if (visualX != x * getTileSize()) {
          if (visualX < x * getTileSize()) {
            visualX++;
          } else {
            visualX--;
          }
        }
        if (visualY != y * getTileSize()) {
          if (visualY < y * getTileSize()) {
            visualY++;
          } else {
            visualY--;
          }
        }
        fudge -= GAME_TICKER;
      }
      
    } else {
      visualX = x * getTileSize();
      visualY = y * getTileSize();
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


- (bool) moving {
  if (visualX != x * getTileSize() || visualY != y * getTileSize()) {
    return true;
  }
  return false;
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
  visualX = x * getTileSize();
  return self;
}


- setY: (int) newY {
  y = newY;
  visualY = y * getTileSize();
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


- setWorld: (World *) aWorld {
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

