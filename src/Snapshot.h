#ifndef SNAPSHOT_HEADER
#define SNAPSHOT_HEADER


#include "Sprite.h"


class Snapshot : public Sprite {
 
protected:

  BITMAP *canvas;
  
public:

  Snapshot();
  ~Snapshot();

  void update();
  void draw(BITMAP *buffer);

  virtual bool moving();
  virtual void setX(int newX);
  virtual void setY(int newY);

  BITMAP *getCanvas();
};


#endif
