#ifndef GIANT_HEADER
#define GIANT_HEADER


#include "Enemy.h"

class Hammer;


class Giant : public Enemy {
  
protected:

  Hammer *hammer;
  
  ANIM stand_anim;
  ANIM attack_anim;
  
public:

  Giant();
  ~Giant();

  void update();
  void draw(IMAGE *canvas);

  virtual void setX(int newX);
  virtual void setY(int newY);
  virtual void moveX(int newX);
  virtual void moveY(int newY);
  virtual void setWorld(World *aWorld);
  virtual void dropItem();

  bool target(Character *target, int range);
  int directionToTarget(Character *target);
  bool isMe(int atX, int atY);
  bool canWalkTo(int toX, int toY);
};


#endif
