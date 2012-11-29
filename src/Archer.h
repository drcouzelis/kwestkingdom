#ifndef ARCHER_HEADER
#define ARCHER_HEADER


#include "Enemy.h"
#include "Bow.h"


@interface Archer : Enemy {
  
  Bow *bow;
  
  Animation *standAnimation;
  Animation *beginAttackAnimation;
  Animation *endAttackAnimation;
  
  int direction;
  
}


// State control
- toStandState;
- toMoveState;
- toDrawBowState;
- toShootArrowState;


@end


#endif