#include "Hammer.h"


@implementation Hammer


- init {
  
  self = [super init];
  
  if (self) {
    
    holdAnimation = [[Animation alloc] init];
    [holdAnimation addFrame: getImage(IMAGES_HAMMER_HOLD_1)];
    [holdAnimation addFrame: getImage(IMAGES_HAMMER_HOLD_2)];
    [holdAnimation addFrame: getImage(IMAGES_HAMMER_HOLD_3)];
    [holdAnimation addFrame: getImage(IMAGES_HAMMER_HOLD_4)];
    [holdAnimation setOffsetY: TILE_SIZE];
    [holdAnimation setLoop: YES];
    [holdAnimation setSpeed: 6];
    
    attackRightAnimation = [[Animation alloc] init];
    [attackRightAnimation addFrame: getImage(IMAGES_HAMMER_SWING_1)];
    [attackRightAnimation addFrame: getImage(IMAGES_HAMMER_SWING_2)];
    [attackRightAnimation addFrame: getImage(IMAGES_HAMMER_SWING_3)];
    [attackRightAnimation addFrame: getImage(IMAGES_HAMMER_SWING_4)];
    [attackRightAnimation addFrame: getImage(IMAGES_HAMMER_SWING_4)];
    [attackRightAnimation addFrame: getImage(IMAGES_HAMMER_SWING_4)];
    [attackRightAnimation addFrame: getImage(IMAGES_HAMMER_SWING_4)];
    [attackRightAnimation addFrame: getImage(IMAGES_HAMMER_SWING_3)];
    [attackRightAnimation addFrame: getImage(IMAGES_HAMMER_SWING_2)];
    [attackRightAnimation addFrame: getImage(IMAGES_HAMMER_SWING_1)];
    [attackRightAnimation setOffsetX: TILE_SIZE];
    [attackRightAnimation setLoop: NO];
    [attackRightAnimation setSpeed: 24];
    
    attackLeftAnimation = [[attackRightAnimation copy] setHorizontalFlip: YES];
    [attackLeftAnimation setOffsetX: -TILE_SIZE * 2];
    attackDownAnimation = [[attackRightAnimation copy] setRotate: YES];
    [attackDownAnimation setOffsetX: 0];
    [attackDownAnimation setOffsetY: TILE_SIZE];
    attackUpAnimation = [[[[attackRightAnimation copy] setHorizontalFlip: YES] setVerticalFlip: YES] setRotate: YES];
    [attackUpAnimation setOffsetX: -TILE_SIZE];
    [attackUpAnimation setOffsetY: -TILE_SIZE * 2];
    
    [self setState: HAMMER_AWAY_STATE];
    
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


- update {
  
  [super update];
  
  switch (state) {
  case HAMMER_ATTACK_UP_STATE:
  case HAMMER_ATTACK_DOWN_STATE:
  case HAMMER_ATTACK_LEFT_STATE:
  case HAMMER_ATTACK_RIGHT_STATE:
    if ([animation currentFrameNumber] == 3) {
      [self setState: HAMMER_END_ATTACK_STATE];
    }
    break;
  }
  
  return self;
  
}



- setState: (int) aState {
  
  state = aState;
  
  switch (state) {
  
  case HAMMER_HOLD_STATE:
    animation = holdAnimation;
    break;
    
  case HAMMER_AWAY_STATE:
    animation = nil;
    break;
    
  case HAMMER_ATTACK_UP_STATE:
    animation = attackUpAnimation;
    [animation reset];
    break;
    
  case HAMMER_ATTACK_DOWN_STATE:
    animation = attackDownAnimation;
    [animation reset];
    break;
    
  case HAMMER_ATTACK_LEFT_STATE:
    animation = attackLeftAnimation;
    [animation reset];
    break;
    
  case HAMMER_ATTACK_RIGHT_STATE:
    animation = attackRightAnimation;
    [animation reset];
    break;
    
  case HAMMER_END_ATTACK_STATE:
    playSound(SOUNDS_HAMMER);
    [world shake];
    break;
    
  }
  
  return self;
  
}


- (BOOL) held {
  if (state == HAMMER_HOLD_STATE) {
    return YES;
  }
  return NO;
}


@end

