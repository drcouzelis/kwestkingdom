#import <objc/Object.h>
#import <allegro.h>
#import "Animation.h"
#import "KwestKingdom.h"
#import "Resources.h"
#import "Screen.h"


@class Command;
@class World;


@interface Sprite2 : Object {
  
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
  
  int state;
  
  Command *command;
}


- update;
- draw:(BITMAP *)buffer;

- (BOOL)isMoving;
- (int)width;
- (int)height;

- setWorld:(World *)aWorld;
- setSpeed:(int)theSpeed;
- setState:(int)aState;

- setX:(int)newX;
- setY:(int)newY;
- (int)x;
- (int)y;
- moveToX:(int)newX;
- moveToY:(int)newY;
- setSpeed:(int)newSpeed;
- boundAtTop:(int)top bottom:(int)bottom left:(int)left right:(int)right;


@end
