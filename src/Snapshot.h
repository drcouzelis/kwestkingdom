#ifndef SNAPSHOT_HEADER
#define SNAPSHOT_HEADER


#include "Sprite.h"


class Snapshot : public Sprite {
  
  BITMAP *canvas;
  
public:

  Snaphshot();
  ~Snapshot();

  BITMAP *getCanvas();
};


#endif
