#import "Sprite.h"


@interface Sword : Sprite {

  Animation *holdAnimation;
  Animation *attackUpAnimation;
  Animation *attackDownAnimation;
  Animation *attackLeftAnimation;
  Animation *attackRightAnimation;

}


- (BOOL) held;

- toHoldState;
- toAwayState;

// Deprecated
- toAttackUpState;
- toAttackDownState;
- toAttackLeftState;
- toAttackRightState;


@end
