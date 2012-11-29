#import "Sprite.h"


@interface Shield : Sprite {
  
  Animation *holdAnimation;
  
}


- (BOOL) held;

// Deprecated
- toHoldState;
- toAwayState;


@end
