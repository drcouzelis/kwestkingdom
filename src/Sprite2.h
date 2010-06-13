#import <objc/Object.h>


@class Animation;
@class Command;
@class List;
@class Object;
@class World;


struct BITMAP;


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
  
  World *world;
  
  // Keep a collection of commands
  // Select the one you want via a string "label"
  Command *command; // TEMP
  List *commands;
}

- initWorld:(World *)aWorld width:(int)width height:(int)height;

- setSpeed:(int)fps;

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

@end

