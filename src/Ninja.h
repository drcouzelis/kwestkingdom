#ifndef NINJA_HEADER
#define NINJA_HEADER


#include "Enemy.h"
#include "Sword.h"


class Ninja : public Enemy {
  
  Sword *sword;
  
  Animation *standAnimation;
  Animation *attackAnimation;
  Animation *dashAnimation;
  
public:

  Ninja();
  ~Ninja();
};


#endif
