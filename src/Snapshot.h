#ifndef SNAPSHOT_HEADER
#define SNAPSHOT_HEADER


#include "Sprite.h"


class Snapshot : public Sprite {
 
protected:

  IMAGE *canvas;
  
public:

  Snapshot();
  ~Snapshot();

  void update();
  void draw(IMAGE *canvas);

  virtual bool moving();
  virtual void setX(int newX);
  virtual void setY(int newY);

  IMAGE *getCanvas();
};


#endif
