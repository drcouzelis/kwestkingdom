#ifndef BOW_HEADER
#define BOW_HEADER


#include "Arrow.h"
#include "Sprite.h"


@interface Bow : Sprite {
  
  Arrow *arrow;
  
  Animation *holdAnimation;
  Animation *attackUpAnimation;
  Animation *attackDownAnimation;
  Animation *attackLeftAnimation;
  Animation *attackRightAnimation;
  
}


- setArrow: (Arrow *) anArrow;
- (Arrow *) getArrow;

- setArrowWithX: (int) newX
    andY: (int) newY
    andDirection: (int) aDirection
    andTeam: (int) aTeam
    andWorld: (id<Inhabitable, Targetable, Traversable>) aWorld;

- (bool) held;

// State control
- toHoldState;
- toAwayState;
- toAttackUpState;
- toAttackDownState;
- toAttackLeftState;
- toAttackRightState;


@end


#endif