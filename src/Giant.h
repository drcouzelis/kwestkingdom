#ifndef GIANT_HEADER
#define GIANT_HEADER


#include "Enemy.h"
#include "Hammer.h"


@interface Giant : Enemy {
  
  Hammer *hammer;
  
  Animation *standAnimation;
  Animation *attackAnimation;
  
}


- (bool) target: (id<Positionable>) target isInRange: (int) range;
- (int) directionToTarget: (id<Positionable>) target;
- (bool) isMeAtX: (int) atX andY: (int) atY;
- (bool) canWalkToX: (int) toX andY: (int) toY;


@end


#endif