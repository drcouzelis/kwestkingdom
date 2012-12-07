#include "Shield.h"


typedef enum {
  SHIELD_HOLD_STATE,
  SHIELD_AWAY_STATE
} SHIELD_STATE;


@implementation Shield


- init {
  
  self = [super init];
  
  if (self) {
    
    holdAnimation = [[Animation alloc] init];
    [holdAnimation addFrame: getImage(IMAGES_SHIELD_1)];
    [holdAnimation addFrame: getImage(IMAGES_SHIELD_2)];
    [holdAnimation addFrame: getImage(IMAGES_SHIELD_3)];
    [holdAnimation addFrame: getImage(IMAGES_SHIELD_4)];
    [holdAnimation setLoop: true];
    [holdAnimation setSpeed: 6];
	
    [self toAwayState];
    
  }
  
  return self;
  
}


- (void) dealloc {
  [holdAnimation release];
  [super dealloc];
}


- toHoldState {
  state = SHIELD_HOLD_STATE;
  animation = holdAnimation;
  return self;
}


- toAwayState {
  state = SHIELD_AWAY_STATE;
  animation = nil;
  return self;
}


- (bool) held {
  if (state == SHIELD_HOLD_STATE) {
    return true;
  }
  return false;
}


@end
