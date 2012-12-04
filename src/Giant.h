#ifndef GIANT_HEADER
#define GIANT_HEADER


#include "Enemy.h"
#include "Hammer.h"


class Giant : public Enemy {
  
  Hammer *hammer;
  
  Animation *standAnimation;
  Animation *attackAnimation;
  
public:

  Giant();
  ~Giant();

  bool target(Character *target, int range);
  int directionToTarget(Character *target);
  bool isMe(int atX, int atY);
  bool canWalkTo(int toX, int toY);
};


#endif
