#ifndef ARCHER_HEADER
#define ARCHER_HEADER


#include "Enemy.h"
#include "Bow.h"


class Archer : public public Enemy {
  
  Bow *bow;
  
  Animation *standAnimation;
  Animation *beginAttackAnimation;
  Animation *endAttackAnimation;
  
  int direction;
  
public:

  Archer();
  ~Archer();

  // State control
  void toStandState();
  void toMoveState();
  void toDrawBowState();
  void toShootArrowState();
public:;


#endif
