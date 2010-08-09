#import <objc/Object.h>
#import <allegro.h>
#import "Animation.h"
#import "Inhabitable.h"
#import "KwestKingdom.h"
#import "Positionable.h"
#import "Resources.h"
#import "Screen.h"
#import "Targetable.h"
#import "Traversable.h"
#import "Updatable.h"


@interface Sprite : Object <Positionable, Updatable> {

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

  id<Inhabitable, Targetable, Traversable> world;

  int state;

}


- draw:(BITMAP *)buffer;

- (BOOL) moving;
- (int) getWidth;
- (int) getHeight;

- setWorld: (id<Inhabitable, Targetable, Traversable>) aWorld;
- setSpeed: (int) theSpeed;
- setState: (int) aState;


@end
