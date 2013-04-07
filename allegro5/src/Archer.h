#ifndef ARCHER_HEADER
#define ARCHER_HEADER


#include "Enemy.h"

class Bow;


class Archer : public Enemy {
  
protected:

  Bow *bow;
  
  ANIM stand_anim;
  ANIM begin_attack_anim;
  ANIM end_attack_anim;
  
  int direction;
  
public:

  Archer();
  ~Archer();

  virtual void update();
  virtual void draw(IMAGE *canvas);

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
