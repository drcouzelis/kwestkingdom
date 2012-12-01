#ifndef SHIELD_HEADER
#define SHIELD_HEADER


#include "Sprite.h"


@interface Shield : Sprite {
  
  Animation *holdAnimation;
  
}


- (bool) held;

// Deprecated
- toHoldState;
- toAwayState;


@end


#endif