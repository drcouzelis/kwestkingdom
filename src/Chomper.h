#ifndef CHOMPER_HEADER
#define CHOMPER_HEADER


#include "Enemy.h"


@interface Chomper : Enemy {
  
  Animation *standAnimation;
  Animation *attackAnimation;
  
  int prevDirection;
  
}


@end


#endif