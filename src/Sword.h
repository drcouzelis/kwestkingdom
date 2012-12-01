#ifndef SWORD_HEADER
#define SWORD_HEADER


#include "Sprite.h"


@interface Sword : Sprite {
  
  Animation *holdAnimation;
  Animation *attackUpAnimation;
  Animation *attackDownAnimation;
  Animation *attackLeftAnimation;
  Animation *attackRightAnimation;
  
}


- (bool) held;

- toHoldState;
- toAwayState;

// Deprecated
- toAttackUpState;
- toAttackDownState;
- toAttackLeftState;
- toAttackRightState;


@end


#endif