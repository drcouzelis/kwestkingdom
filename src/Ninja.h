#ifndef NINJA_HEADER
#define NINJA_HEADER


#include "Enemy.h"

class Sword;


class Ninja : public Enemy {
  
protected:

  Sword *sword;
  
  ANIM stand_anim;
  ANIM attack_anim;
  ANIM dash_anim;
  
public:

  Ninja();
  ~Ninja();

  void update();
  void draw(BITMAP *buffer);

  virtual void setX(int newX);
  virtual void setY(int newY);
  virtual void moveX(int newX);
  virtual void moveY(int newY);
  virtual void setSpeed(int theSpeed);
};


#endif
