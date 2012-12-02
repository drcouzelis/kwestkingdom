#ifndef SPRITE_HEADER
#define SPRITE_HEADER


#include <Foundation/Foundation.h>
#include <allegro.h>
#include "Animation.h"
#include "Drawable.h"
#include "Inhabitable.h"
#include "KwestKingdom.h"
#include "Positionable.h"
#include "Resources.h"
#include "Screen.h"
#include "Targetable.h"
#include "Traversable.h"
#include "Updatable.h"


class Sprite : public NSObject <Drawable, Positionable, Updatable> {
  
  // Position on the map
  int x; // Horizontal, from 0 to COLS   1
  int y; // Vertical, from 0 to ROWS   1
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
  
public:


  (bool) moving;
  (int) getWidth;
  (int) getHeight;

  setWorld: (id<Inhabitable, Targetable, Traversable>) aWorld;
  setSpeed: (int) theSpeed;
  setState: (int) aState;


};


#endif