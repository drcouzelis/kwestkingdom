#import "Arrow.h"
#import "Bow.h"
#import "Character.h"
#import "KeyControl.h"
#import "Resources.h"
#import "Shield.h"
#import "Sword.h"


#define MAX_HERO_HEALTH 3


@interface Hero : Character {
  
  Shield *shield;
  Sword *sword;
  Bow *bow;
  
  Animation *standAnimation;
  Animation *beginAttackAnimation;
  Animation *endAttackAnimation;
  Animation *hurtAnimation;
  Animation *deadAnimation;
  
  KeyControl *upKey;
  KeyControl *downKey;
  KeyControl *rightKey;
  KeyControl *leftKey;
  KeyControl *waitKey;
  KeyControl *attackKey;
  KeyControl *handKey;
  KeyControl *shieldKey;
  KeyControl *swordKey;
  KeyControl *bowKey;
  
  int direction;
  
}


- emptyHands;

// Updates
- updateStandState;

// State control
- toStandState;
- toMoveState;
- toAttackState;
- toHurtState;
- toDeadState;
- toPushSwordState;
- toPullSwordState;
- toDrawBowState;
- toShootArrowState;


@end
