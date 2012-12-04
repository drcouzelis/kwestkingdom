#ifndef SNAPSHOT_HEADER
#define SNAPSHOT_HEADER


#include "Sprite.h"


class Snapshot : public Sprite {
 
protected:

  BITMAP *canvas;
  
public:

  Snapshot();
  ~Snapshot();

  BITMAP *getCanvas();
};


#endif
