#ifndef ARROW_HEADER
#define ARROW_HEADER


#include "Character.h"
#include "Resources.h"


@interface Arrow : Character {
  
  Animation *flyUpAnimation;
  Animation *flyDownAnimation;
  Animation *flyLeftAnimation;
  Animation *flyRightAnimation;
  
  int direction;
  
}


- (BOOL) isInsideScreen;
- findTarget;
- setDirection: (int) aDirection;

- (BOOL) stopped;

// Deprecated
- toHoldState;
- toFlyingState;
- toStoppedState;


@end


#endif