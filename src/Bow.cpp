#include "Bow.h"


typedef enum {
  BOW_HOLD_STATE,
  BOW_AWAY_STATE
} BOW_STATE;


@implementation Bow


- init {
  
  self = [super init];
  
  if (self) {
    
    arrow = nil;
    
    holdAnimation = [[Animation alloc] init];
    [holdAnimation addFrame: getImage(IMAGES_BOW_HOLD_1)];
    [holdAnimation addFrame: getImage(IMAGES_BOW_HOLD_2)];
    [holdAnimation addFrame: getImage(IMAGES_BOW_HOLD_3)];
    [holdAnimation addFrame: getImage(IMAGES_BOW_HOLD_4)];
    [holdAnimation setLoop: true];
    [holdAnimation setSpeed: 6];
	
    attackRightAnimation = [[Animation alloc] init];
    [attackRightAnimation addFrame: getImage(IMAGES_BOW_DRAW_1)];
    [attackRightAnimation addFrame: getImage(IMAGES_BOW_DRAW_2)];
    [attackRightAnimation addFrame: getImage(IMAGES_BOW_DRAW_3)];
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
  [arrow release];
  [super dealloc];
}


- update {
  [super update];
  [arrow update];
  return self;
}


- draw: (BITMAP *) buffer {
  [super draw: buffer];
  [arrow draw: buffer];
  return self;
}


- setArrow: (Arrow *) anArrow {
  arrow = anArrow;
  return self;
}


- (Arrow *) getArrow {
  return arrow;
}


- setArrowWithX: (int) newX
    andY: (int) newY
    andDirection: (int) aDirection
    andTeam: (int) aTeam
    andWorld: (id<Inhabitable, Targetable, Traversable>) aWorld {
  
  arrow = [[Arrow alloc] init];
  [arrow setTeam: aTeam];
  [arrow setX: newX];
  [arrow setY: newY];
  [arrow setWorld: aWorld];
  [arrow setDirection: aDirection];
  [arrow toHoldState];
  
  return self;
  
}


- toHoldState {
  state = BOW_HOLD_STATE;
  animation = holdAnimation;
  return self;
}


- toAwayState {
  state = BOW_AWAY_STATE;
  animation = nil;
  return self;
}


- toAttackUpState {
  animation = attackUpAnimation;
  [animation reset];
  return self;
}


- toAttackDownState {
  animation = attackDownAnimation;
  [animation reset];
  return self;
}


- toAttackLeftState {
  animation = attackLeftAnimation;
  [animation reset];
  return self;
}


- toAttackRightState {
  animation = attackRightAnimation;
  [animation reset];
  return self;
}


- (bool) held {
  if (state != BOW_AWAY_STATE) {
    return true;
  }
  return false;
}


@end

