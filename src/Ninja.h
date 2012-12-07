#ifndef NINJA_HEADER
#define NINJA_HEADER


#include "Enemy.h"

class Sword;


class Ninja : public Enemy {
  
protected:

  Sword *sword;
  
  Animation *standAnimation;
  Animation *attackAnimation;
  Animation *dashAnimation;
  
public:

  Ninja();
  ~Ninja();
};


#endif
