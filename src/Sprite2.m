#include <allegro.h>

#import "Animation.h"
#import "Command.h"
#import "List.h"
#import "KwestKingdom.h"
#import "Resources.h"
#import "Screen.h"
#import "Sprite2.h"
#import "World.h"


@interface Sprite2 (PrivateMethods)
- move;
@end


@implementation Sprite2


- initWorld:(World *)aWorld width:(int)width height:(int)height {
  
  self = [self init];
  
  if (self) {
    world = aWorld;
    w = width;
    h = height;
    commands = [[List alloc] init];
  }
  
  return self;
}


- free {
  [commands freeIncludingItems];
  return [super free];
}


- addCommand:(Command *)aCommand named:(char *)aName {
  [commands add:aCommand named:aName];
  return self;
}


- setCommandTo:(char *)aName {
  command = [commands itemNamed:aName];
  return self;
}


- update {
  [animation update];
  [command execute];
  [self move];
  return self;
}


- draw:(BITMAP *)canvas {
  [animation draw:canvas atX:visualX andY:visualY];
  return self;
}


- (BOOL)isMoving {
  if (visualX != x * getTileSize() || visualY != y * getTileSize()) {
    return YES;
  }
  return NO;
}


- (int)width {
  return w;
}


- (int)height {
  return h;
}


- setSpeed:(int)fps {
  speed = fps;
  return self;
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


- setX:(int)pos {
  x = pos;
  visualX = x * getTileSize();
  return self;
}


- setY:(int)pos {
  y = pos;
  visualY = y * getTileSize();
  return self;
}


- moveToX:(int)pos {
  x = pos;
  return self;
}


- moveToY:(int)pos {
  y = pos;
  return self;
}


@end


@implementation Sprite2 (PrivateMethods)


- move {

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
  
  return self;
}


@end

