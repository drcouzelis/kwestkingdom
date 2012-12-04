#ifndef ARCHER_HEADER
#define ARCHER_HEADER


#include "Enemy.h"

class Bow;


class Archer : public Enemy {
  
protected:

  Bow *bow;
  
  Animation *standAnimation;
  Animation *beginAttackAnimation;
  Animation *endAttackAnimation;
  
  int direction;
  
public:

  Archer();
  ~Archer();

  virtual void update();
  virtual void draw(BITMAP *buffer);

  virtual void setX(int newX);
  virtual void setY(int newY);
  virtual void moveX(int newX);
  virtual void moveY(int newY);

  // State control
  void toStandState();
  void toMoveState();
  void toDrawBowState();
  void toShootArrowState();
};


#endif
