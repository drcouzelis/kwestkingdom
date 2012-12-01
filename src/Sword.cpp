#include "Sword.h"


typedef enum {
  SWORD_HOLD_STATE,
  SWORD_AWAY_STATE
} SWORD_STATE;

typedef enum {
  SWORD_ATTACK_UP_STATE,
  SWORD_ATTACK_DOWN_STATE,
  SWORD_ATTACK_LEFT_STATE,
  SWORD_ATTACK_RIGHT_STATE
} SWORD_ATTACK_STATE;


@implementation Sword


- init {
  
  self = [super init];
  
  if (self) {
    
    holdAnimation = [[Animation alloc] init];
    [holdAnimation addFrame: getImage(IMAGES_SWORD_HOLD_1)];
    [holdAnimation addFrame: getImage(IMAGES_SWORD_HOLD_2)];
    [holdAnimation addFrame: getImage(IMAGES_SWORD_HOLD_3)];
    [holdAnimation addFrame: getImage(IMAGES_SWORD_HOLD_4)];
    [holdAnimation setLoop: true];
    [holdAnimation setSpeed: 6];
    
    attackRightAnimation = [[Animation alloc] init];
    [attackRightAnimation addFrame: getImage(IMAGES_SWORD_STAB_1)];
    [attackRightAnimation addFrame: getImage(IMAGES_SWORD_STAB_2)];
    [attackRightAnimation addFrame: getImage(IMAGES_SWORD_STAB_3)];
    [attackRightAnimation addFrame: getImage(IMAGES_SWORD_STAB_4)];
    [attackRightAnimation addFrame: getImage(IMAGES_SWORD_STAB_3)];
    [attackRightAnimation addFrame: getImage(IMAGES_SWORD_STAB_2)];
    [attackRightAnimation addFrame: getImage(IMAGES_SWORD_STAB_1)];
    [attackRightAnimation setOffsetX: -TILE_SIZE];
    [attackRightAnimation setOffsetY: -TILE_SIZE];
    [attackRightAnimation setLoop: false];
    [attackRightAnimation setSpeed: 12];
    
    attackLeftAnimation = [[attackRightAnimation copy] setHorizontalFlip: true];
    attackDownAnimation = [[attackRightAnimation copy] setRotate: true];
    attackUpAnimation = [[[attackRightAnimation copy] setHorizontalFlip: true] setRotate: true];
    
    [self toAwayState];
    
  }
  
  return self;
  
}


- (void) dealloc {
  [holdAnimation release];
  [attackUpAnimation release];
  [attackDownAnimation release];
  [attackLeftAnimation release];
  [attackRightAnimation release];
  [super dealloc];
}


- toHoldState {
  state = SWORD_HOLD_STATE;
  animation = holdAnimation;
  return self;
}


- toAwayState {
  state = SWORD_AWAY_STATE;
  animation = nil;
  return self;
}


- toAttackUpState {
  animation = attackUpAnimation;
  [animation reset];
  playSound(SOUNDS_SWORD);
  return self;
}


- toAttackDownState {
  animation = attackDownAnimation;
  [animation reset];
  playSound(SOUNDS_SWORD);
  return self;
}


- toAttackLeftState {
  animation = attackLeftAnimation;
  [animation reset];
  playSound(SOUNDS_SWORD);
  return self;
}


- toAttackRightState {
  animation = attackRightAnimation;
  [animation reset];
  playSound(SOUNDS_SWORD);
  return self;
}


- (bool) held {
  if (state == SWORD_HOLD_STATE) {
    return true;
  }
  return false;
}


@end

