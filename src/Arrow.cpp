#include "Arrow.h"


typedef enum {
  ARROW_HOLD_STATE,
  ARROW_FLYING_STATE,
  ARROW_STOPPED_STATE
} ARROW_STATE;


@implementation Arrow


- init {
  
  self = [super init];
  
  if (self) {
    
    [self setSpeed: getWalkSpeed() * 4];
    
    flyRightAnimation = [[Animation alloc] init];
    [flyRightAnimation addFrame: getImage(IMAGES_ARROW)];
    
    flyLeftAnimation = [[flyRightAnimation copy] setHorizontalFlip: true];
    flyDownAnimation = [[flyRightAnimation copy] setRotate: true];
    flyUpAnimation = [[[flyRightAnimation copy] setHorizontalFlip: true] setRotate: true];
    
    direction = UP;
    
    [self toHoldState];
    
  }
  
  return self;
  
}


- (void) dealloc {
  [flyUpAnimation release];
  [flyDownAnimation release];
  [flyLeftAnimation release];
  [flyRightAnimation release];
  [super dealloc];
}


- update {
  
  [super update];
  
  switch (state) {
  case ARROW_HOLD_STATE:
    // There's just not much going on when it's being held.
    break;
    
  case ARROW_FLYING_STATE:
    
    if (![self moving]) {
      
      if (direction == LEFT) {
        [world attackFromTeam: team atX: x - 1 andY: y];
      } else if (direction == RIGHT) {
        [world attackFromTeam: team atX: x + 1 andY: y];
      } else if (direction == UP) {
        [world attackFromTeam: team atX: x andY: y - 1];
      } else {
        [world attackFromTeam: team atX: x andY: y + 1];
      }
      
      [self toStoppedState];
      
    }
    
    break;
    
  case ARROW_STOPPED_STATE:
    // There's not much going on when it's stopped.
    break;
  }
  
  return self;
  
}


- (bool) isInsideScreen {
  if (x < 0 || x > COLS - 1 || y < 0 || y > ROWS - 1) {
    return false;
  }
  return true;
}


- findTarget {
  
  if (direction == LEFT) {
    while ([world isFlyableAtX: x - 1 andY: y] && ![world isAttackableFromTeam: team atX: x - 1 andY: y] && [self isInsideScreen]) {
      x--;
    }
  } else if (direction == RIGHT) {
    while ([world isFlyableAtX: x + 1 andY: y] && ![world isAttackableFromTeam: team atX: x + 1 andY: y] && [self isInsideScreen]) {
      x++;
    }
  } else if (direction == UP) {
    while ([world isFlyableAtX: x andY: y - 1] && ![world isAttackableFromTeam: team atX: x andY: y - 1] && [self isInsideScreen]) {
      y--;
    }
  } else {
    while ([world isFlyableAtX: x andY: y + 1] && ![world isAttackableFromTeam: team atX: x andY: y + 1] && [self isInsideScreen]) {
      y++;
    }
  }
  
  return self;
  
}


- setDirection: (int) aDirection {
  direction = aDirection;
  if (direction == UP) {
    animation = flyUpAnimation;
  } else if (direction == DOWN) {
    animation = flyDownAnimation;
  } else if (direction == LEFT) {
    animation = flyLeftAnimation;
  } else {
    animation = flyRightAnimation;
  }
  return self;
}


- toHoldState {
  
  int visualOffset;
  
  visualOffset = (getTileSize() / 3) + (getTileSize() / 10);
  
  state = ARROW_HOLD_STATE;
  
  [self setDirection: direction];
  
  // Offset the animation a little bit to make it look like
  // the arrow is in the bow string.
  [flyUpAnimation setOffsetX: 0];
  [flyUpAnimation setOffsetY: visualOffset];
  [flyDownAnimation setOffsetX: 0];
  [flyDownAnimation setOffsetY: -visualOffset];
  [flyLeftAnimation setOffsetX: visualOffset];
  [flyLeftAnimation setOffsetY: 0];
  [flyRightAnimation setOffsetX: -visualOffset];
  [flyRightAnimation setOffsetY: 0];
  
  return self;
}


- toFlyingState {
  state = ARROW_FLYING_STATE;
  [self setDirection: direction];
  [self findTarget];
  // Put the animation back to where it's supposed to be.
  [flyUpAnimation setOffsetX: 0];
  [flyUpAnimation setOffsetY: 0];
  [flyDownAnimation setOffsetX: 0];
  [flyDownAnimation setOffsetY: 0];
  [flyLeftAnimation setOffsetX: 0];
  [flyLeftAnimation setOffsetY: 0];
  [flyRightAnimation setOffsetX: 0];
  [flyRightAnimation setOffsetY: 0];
  playSound(SOUNDS_ARROW_FLY);
  return self;
}


- toStoppedState {
  state = ARROW_STOPPED_STATE;
  [self setDirection: direction];
  playSound(SOUNDS_ARROW_HIT);
  return self;
}


- (bool) stopped {
  if (state == ARROW_STOPPED_STATE) {
    return true;
  }
  return false;
}


@end
