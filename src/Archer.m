#include "Archer.h"


typedef enum {
  ARCHER_STAND_STATE,
  ARCHER_ATTACK_STATE,
  ARCHER_MOVE_STATE,
  ARCHER_DRAW_BOW_STATE,
  ARCHER_SHOOT_ARROW_STATE
} ARCHER_STATE;


@implementation Archer


- init {
  
  self = [super init];
  
  if (self) {
    
    x = 0;
    y = 0;
    
    speed = getWalkSpeed();
    team = ENEMY_TEAM;
    
    bow = [[Bow alloc] init];
    [bow setSpeed: speed];
    [bow toHoldState];
    
    standAnimation = [[Animation alloc] init];
    [standAnimation addFrame: getImage(IMAGES_ARCHER_1)];
    [standAnimation addFrame: getImage(IMAGES_ARCHER_2)];
    [standAnimation addFrame: getImage(IMAGES_ARCHER_3)];
    [standAnimation addFrame: getImage(IMAGES_ARCHER_2)];
    [standAnimation setLoop: YES];
    [standAnimation setSpeed: 3];
    
    beginAttackAnimation = [[Animation alloc] init];
    [beginAttackAnimation addFrame: getImage(IMAGES_ARCHER_1)];
    [beginAttackAnimation addFrame: getImage(IMAGES_ARCHER_2)];
    [beginAttackAnimation addFrame: getImage(IMAGES_ARCHER_2)];
    [beginAttackAnimation addFrame: getImage(IMAGES_ARCHER_3)];
    [beginAttackAnimation setLoop: NO];
    [beginAttackAnimation setSpeed: 12];
    
    endAttackAnimation = [[Animation alloc] init];
    [endAttackAnimation addFrame: getImage(IMAGES_ARCHER_3)];
    [endAttackAnimation addFrame: getImage(IMAGES_ARCHER_2)];
    [endAttackAnimation addFrame: getImage(IMAGES_ARCHER_2)];
    [endAttackAnimation setLoop: NO];
    [endAttackAnimation setSpeed: 12];
    
    animation = standAnimation;
    state = ARCHER_STAND_STATE;
    direction = UP;
    [self wait];
    
  }
  
  return self;
  
}


- (void) dealloc {
  [bow release];
  [standAnimation release];
  [beginAttackAnimation release];
  [endAttackAnimation release];
  [super dealloc];
}


- update {
  
  int dir;
  int toX;
  int toY;
  id<Positionable> target;
  
  [super update];
  [bow update];
  
  if ([self waiting]) {
    return self;
  }
  
  if (health == 0) {
    return self;
  }
  
  target = [world getTarget];
  
  switch (state) {
  
  case ARCHER_STAND_STATE:
    
    if (x == [target getX]) {
      
      if (y > [target getY]) { // Hero is up.
        direction = UP;
      } else { // Hero is down.
        direction = DOWN;
      }
      
      [self toDrawBowState];
      [self wait];
      
    } else if (y == [target getY]) {
      
      if (x > [target getX]) { // Hero is left.
        direction = LEFT;
      } else { // Hero is right.
        direction = RIGHT;
      }
      
      [self toDrawBowState];
      [self wait];
      
    } else if ((x == [target getX] - 1 || x == [target getX] + 1) && random_number(0, 1) == 1) {
      
      if (y > [target getY]) { // Hero is up.
        direction = UP;
      } else { // Hero is down.
        direction = DOWN;
      }
      
      [self toDrawBowState];
      [self wait];
      
    } else if ((y == [target getY] - 1 || y == [target getY] + 1) && random_number(0, 1) == 1) {
      
      if (x > [target getX]) { // Hero is left.
        direction = LEFT;
      } else { // Hero is right.
        direction = RIGHT;
      }
      
      [self toDrawBowState];
      [self wait];
      
    } else {
      
      // Wander aimlessly
      dir = random_number(UP, /*DOWN, LEFT,*/ RIGHT);
      
      toX = x;
      toY = y;
      
      if (dir == UP) {
        toY--;
      } else if (dir == DOWN) {
        toY++;
      } else if (dir == RIGHT) {
        toX++;
      } else if (dir == LEFT) {
        toX--;
      }
      
      if ([world isWalkableAtX: toX andY: toY] && ![world isInhabitedAtX: toX andY: toY]) {
        [self moveX: toX];
        [self moveY: toY];
        [self toMoveState];
      }
      
      [self wait];
      
    }
    
    // Bound him so he doesn't wander right out of the screen!
    [self boundAtTop: 1 andBottom: ROWS - 2 andLeft: 1 andRight: COLS - 2];
    
    break;
    
  case ARCHER_MOVE_STATE:
    if (![self moving]) {
      [self toStandState];
    }
    break;
    
  case ARCHER_DRAW_BOW_STATE:
    if ([animation finished]) {
      [self toShootArrowState];
    }
    break;
    
  case ARCHER_SHOOT_ARROW_STATE:
    if ([animation finished]) {
      animation = standAnimation;
      [bow toHoldState];
    }
    if ([[bow getArrow] stopped]) {
      [[bow getArrow] release];
      [bow setArrow: nil];
      [self toStandState];
      [self wait];
    }
    break;
    
  }
  
  return self;
  
}


- draw: (BITMAP *) buffer {
  [super draw: buffer];
  [bow draw: buffer];
  return self;
}


- toStandState {
  state = ARCHER_STAND_STATE;
  animation = standAnimation;
  return self;
}


- toMoveState {
  state = ARCHER_MOVE_STATE;
  animation = standAnimation;
  return self;
}


- toDrawBowState {
  
  state = ARCHER_DRAW_BOW_STATE;
  animation = beginAttackAnimation;
  [animation reset];
  
  switch (direction) {
  case UP:
    [bow toAttackUpState];
    break;
  case DOWN:
    [bow toAttackDownState];
    break;
  case LEFT:
    [bow toAttackLeftState];
    break;
  case RIGHT:
    [bow toAttackRightState];
    break;
  }
  
  [bow setArrowWithX: x andY: y andDirection: direction andTeam: team andWorld: world];
  
  return self;
  
}


- toShootArrowState {
  state = ARCHER_SHOOT_ARROW_STATE;
  animation = endAttackAnimation;
  [animation reset];
  [[bow getArrow] toFlyingState];
  [bow toHoldState];
  return self;
}


- setX: (int) newX {
  [super setX: newX];
  [bow setX: newX];
  return self;
}


- setY: (int) newY {
  [super setY: newY];
  [bow setY: newY];
  return self;
}


- moveX: (int) newX {
  [super moveX: newX];
  [bow moveX: newX];
  return self;
}


- moveY: (int) newY {
  [super moveY: newY];
  [bow moveY: newY];
  return self;
}


@end
