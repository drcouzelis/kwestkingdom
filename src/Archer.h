#import "Enemy.h"
#import "Bow.h"


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
