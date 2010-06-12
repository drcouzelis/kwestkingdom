#import <objc/Object.h>
#import <allegro.h>
#import "Animation.h"
#import "KwestKingdom.h"
#import "Resources.h"
#import "Screen.h"


@class World;


@interface Sprite : Object {
  
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
  
}


- update;
- draw:(BITMAP *)buffer;

- (BOOL) moving;
- (int) getWidth;
- (int) getHeight;

- setWorld: (World *)aWorld;
- setSpeed: (int) theSpeed;
- setState: (int) aState;

- setX: (int) newX;
- setY: (int) newY;
- (int) getX;
- (int) getY;
- moveX: (int) newX;
- moveY: (int) newY;
- setSpeed: (int) newSpeed;
- boundAtTop: (int) top andBottom: (int) bottom andLeft: (int) left andRight: (int) right;


@end
