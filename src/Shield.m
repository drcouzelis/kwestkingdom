#import "Shield.h"


typedef enum {
  SHIELD_HOLD_STATE,
  SHIELD_AWAY_STATE
} SHIELD_STATE;


@implementation Shield


- init {

  self = [super init];

  if (self) {

    holdAnimation = [[Animation alloc] init];
    [holdAnimation addFrame: getImage(IMG_SHIELD_1)];
    [holdAnimation addFrame: getImage(IMG_SHIELD_2)];
    [holdAnimation addFrame: getImage(IMG_SHIELD_3)];
    [holdAnimation addFrame: getImage(IMG_SHIELD_4)];
    [holdAnimation setLoop: YES];
    [holdAnimation setSpeed: 6];

    [self toAwayState];

  }

  return self;

}


- free {
  [holdAnimation free];
  return [super free];
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


- (BOOL) held {
  if (state == SHIELD_HOLD_STATE) {
    return YES;
  }
  return NO;
}


@end

