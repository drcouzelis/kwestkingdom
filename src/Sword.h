#ifndef SWORD_HEADER
#define SWORD_HEADER


#include "Sprite.h"


class Sword : public Sprite {
  
  Animation *holdAnimation;
  Animation *attackUpAnimation;
  Animation *attackDownAnimation;
  Animation *attackLeftAnimation;
  Animation *attackRightAnimation;
  
public:


  (bool) held;

  toHoldState;
  toAwayState;

// Deprecated
  toAttackUpState;
  toAttackDownState;
  toAttackLeftState;
  toAttackRightState;


};


#endif