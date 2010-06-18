#import <objc/Object.h>

#include <allegro.h>


@class Animation;
@class List;
@class Object;
@class World;


@interface Sprite2 : Object {
 @private 
  // Position on the map
  int x; // Horizontal, from 0 to COLS - 1
  int y; // Vertical, from 0 to ROWS - 1

  int w; // Width of the sprite, or, how many square it occupies horizontally
  int h; // Height of the sprite
  
  // Where the image is on the screen
  int visualX; // Screen width
  int visualY; // Screen height
  int fudge;
  
  int speed; // In FPS
  
  Animation *animation;
  List *animations;
  
  World *world;
}

- initWorld:(World *)aWorld width:(int)width height:(int)height;

- setSpeed:(int)fps;

- addAnimation:(Animation *)anAnimation named:(char *)aName;
- setAnimationTo:(char *)aName;

- update;
- draw:(BITMAP *)canvas;

- (int)width;
- (int)height;

- (BOOL)isMoving;

// Set the position to a new location
- setX:(int)pos;
- setY:(int)pos;

// These methods move the sprite smoothly
- moveToX:(int)pos;
- moveToY:(int)pos;

// The current position on the map
- (int)x;
- (int)y;

// Ensure the sprite stays inside these boundaries
- boundAtTop:(int)top bottom:(int)bottom left:(int)left right:(int)right;

- (World *)world;

@end

