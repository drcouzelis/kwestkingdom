#import "Command.h"
#import "Sprite2.h"
#import "World.h"


@implementation Sprite2


- init {
  
  self = [super init];
  
  if (self) {
    w = 1;
    h = 1;
  }
  
  return self;
}


- update {
  
  [animation update];
  
  // This will make the visual position of the sprite match up
  // with the actual position of the sprite at the right speed.
  if ([self isMoving]) {
    
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
    
    if (![self isMoving]) {
      fudge = 0;
    }
    
  }
  
  [command execute];
  
  return self;
  
}


- draw:(BITMAP *)buffer {
  
  // Add a shadow.
  /*
  hline(buffer, visualX + 6, visualY + 30, visualX + 33, BLACK);
  hline(buffer, visualX + 6, visualY + 31, visualX + 33, BLACK);
  hline(buffer, visualX + 4, visualY + 32, visualX + 35, BLACK);
  hline(buffer, visualX + 4, visualY + 33, visualX + 35, BLACK);
  hline(buffer, visualX + 6, visualY + 34, visualX + 33, BLACK);
  hline(buffer, visualX + 6, visualY + 35, visualX + 33, BLACK);
  */
  
  [animation draw: buffer atX: visualX andY: visualY];
  
  return self;
  
}


- (BOOL)isMoving {
  if (visualX != x * getTileSize() || visualY != y * getTileSize()) {
    return YES;
  }
  return NO;
}


- boundAtTop:(int)top bottom:(int)bottom left:(int)left right:(int)right {

  if (x < left) {
    [self moveToX: left];
  } else if (x + w - 1 > right) {
    [self moveToX: right];
  }
  
  if (y < top) {
    [self moveToY: top];
  } else if (y + h - 1 > bottom) {
    [self moveToY: bottom];
  }
  
  return self;
}


- (int)x {
  return x;
}


- (int)y {
  return y;
}


- setX:(int)newX {
  x = newX;
  visualX = x * getTileSize();
  return self;
}


- setY:(int)newY {
  y = newY;
  visualY = y * getTileSize();
  return self;
}


- moveToX:(int)newX {
  x = newX;
  return self;
}


- moveToY:(int)newY {
  y = newY;
  return self;
}


- (int)width {
  return w;
}


- (int)height {
  return h;
}


- setWorld:(World *)aWorld {
  world = aWorld;
  return self;
}


- setState:(int)aState {
  state = aState;
  return self;
}


- setSpeed:(int)theSpeed {
  speed = theSpeed;
  return self;
}


@end

