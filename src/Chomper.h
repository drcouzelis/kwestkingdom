#ifndef CHOMPER_HEADER
#define CHOMPER_HEADER


#include "Enemy.h"


class Chomper : public Enemy {

protected:
  
  ANIM stand_anim;
  ANIM attack_anim;
  
  int prevDirection;
  
public:

  Chomper();
  ~Chomper();

  virtual void update();
};


#endif
