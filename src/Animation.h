#import <objc/Object.h>
#import <allegro.h>
#import "KwestKingdom.h"


#define ANIMATION_MAX_FRAMES 16


@interface Animation : Object {

  BITMAP *frames[ANIMATION_MAX_FRAMES];
  
  // An animation is drawn with respect to its offset.
  int offsetX;
  int offsetY;

  int length;
  int pos;
  BOOL loop;
  BOOL finished;
  
  int speed;
  int fudge;
  
  BOOL hFlip;
  BOOL vFlip;
  BOOL rotate;

}

- (BITMAP *) getImage;

- addFrame: (BITMAP *) bitmap;

- setLoop: (BOOL) loopOn;
- setSpeed: (int) newSpeed;
- setOffsetX: (int) newOffsetX;
- setOffsetY: (int) newOffsetY;
- setRotate: (BOOL) rotateOn;
- setHorizontalFlip: (BOOL) hFlipOn;
- setVerticalFlip: (BOOL) vFlipOn;

- reset;

- update;
- drawTo: (BITMAP *) buffer atX: (int) x andY: (int) y;
- (Animation *) copy;

- (BOOL) finished;
- (int) width;
- (int) height;
- (int) currentFrameNumber;


@end

