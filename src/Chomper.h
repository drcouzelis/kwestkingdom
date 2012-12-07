#ifndef CHOMPER_HEADER
#define CHOMPER_HEADER


#include "Enemy.h"


class Chomper : public Enemy {

protected:
  
  Animation *standAnimation;
  Animation *attackAnimation;
  
  int prevDirection;
  
public:

  Chomper();
  ~Chomper();

};


#endif
