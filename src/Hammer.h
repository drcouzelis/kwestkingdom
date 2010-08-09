#import "Sprite.h"


typedef enum {

  HAMMER_HOLD_STATE,
  HAMMER_AWAY_STATE,

  HAMMER_ATTACK_UP_STATE,
  HAMMER_ATTACK_DOWN_STATE,
  HAMMER_ATTACK_LEFT_STATE,
  HAMMER_ATTACK_RIGHT_STATE,

  HAMMER_END_ATTACK_STATE

} HAMMER_STATE;


@interface Hammer : Sprite {

  Animation *holdAnimation;
  Animation *attackUpAnimation;
  Animation *attackDownAnimation;
  Animation *attackLeftAnimation;
  Animation *attackRightAnimation;

}


- (BOOL) held;


@end
