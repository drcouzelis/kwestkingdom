#import "Enemy.h"
#import "Hammer.h"


@interface Giant : Enemy {
  
  Hammer *hammer;
  
  Animation *standAnimation;
  Animation *attackAnimation;
  
}


- (BOOL) target: (id<Positionable>) target isInRange: (int) range;
- (int) directionToTarget: (id<Positionable>) target;
- (BOOL) isMeAtX: (int) atX andY: (int) atY;
- (BOOL) canWalkToX: (int) toX andY: (int) toY;


@end
