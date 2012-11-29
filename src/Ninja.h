#ifndef NINJA_HEADER
#define NINJA_HEADER


#include "Enemy.h"
#include "Sword.h"


@interface Ninja : Enemy {
  
  Sword *sword;
  
  Animation *standAnimation;
  Animation *attackAnimation;
  Animation *dashAnimation;
  
}


@end


#endif