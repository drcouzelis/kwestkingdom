#ifndef SNAPSHOT_HEADER
#define SNAPSHOT_HEADER


#include "Sprite.h"


@interface Snapshot : Sprite {
  
  BITMAP *canvas;
  
}


- (BITMAP *) getCanvas;


@end


#endif