#import "Snapshot.h"


@implementation Snapshot


- init {

  self = [super init];

  if (self) {
    canvas = create_bitmap(getWindowWidth(), getWindowHeight());
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
