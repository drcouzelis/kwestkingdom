#import "Ninja.h"


typedef enum {
  NINJA_STAND_STATE,
  NINJA_ATTACK_STATE,
  NINJA_MOVE_STATE,
  NINJA_DASH_STATE
} NINJA_STATE;


@implementation Ninja


- init {
  
  self = [super init];
  
  if (self) {
    
    x = 0;
    y = 0;
    
    [self setSpeed: getWalkSpeed()];
    team = ENEMY_TEAM;
    
    sword = [[Sword alloc] init];
    [sword setSpeed: speed];
    [sword toHoldState];
    
    standAnimation = [[Animation alloc] init];
    [standAnimation addFrame: getImage(IMAGES_NINJA_1)];
    [standAnimation addFrame: getImage(IMAGES_NINJA_2)];
    [standAnimation addFrame: getImage(IMAGES_NINJA_3)];
    [standAnimation addFrame: getImage(IMAGES_NINJA_2)];
    [standAnimation setLoop: YES];
    [standAnimation setSpeed: 6];
    
    dashAnimation = [standAnimation copy];
    [dashAnimation setSpeed: 24];
    
    attackAnimation = [[Animation alloc] init];
    [attackAnimation addFrame: getImage(IMAGES_NINJA_1)];
    [attackAnimation addFrame: getImage(IMAGES_NINJA_2)];
    [attackAnimation addFrame: getImage(IMAGES_NINJA_2)];
    [attackAnimation addFrame: getImage(IMAGES_NINJA_3)];
    [attackAnimation addFrame: getImage(IMAGES_NINJA_3)];
    [attackAnimation addFrame: getImage(IMAGES_NINJA_2)];
    [attackAnimation addFrame: getImage(IMAGES_NINJA_2)];
    [attackAnimation setLoop: NO];
    [attackAnimation setSpeed: 12];
    
    animation = standAnimation;
    state = NINJA_STAND_STATE;
    [self wait];
    
  }
  
  return self;
  
}


- (void) dealloc {
  [sword release];
  [standAnimation release];
  [dashAnimation release];
  [attackAnimation release];
  [super dealloc];
}


- update {
  
  int dir;
  int toX;
  int toY;
  id<Positionable> target;
  
  [super update];
  [sword update];
  
  if ([self waiting]) {
    return self;
  }
  
  if (health == 0) {
    return self;
  }
  
  target = [world getTarget];
  
  switch (state) {
  
  case NINJA_STAND_STATE:
    
    // If the target has a walking distance of one...
    if (abs(x - [target getX]) + abs(y - [target getY]) == 1) {
      
      state = NINJA_ATTACK_STATE;
      animation = attackAnimation;
      [animation reset];
      // Change the state of the sword.
      if (x == [target getX] && y == [target getY] + 1) { // Up
        [sword toAttackUpState];
      } else if (x == [target getX] && y == [target getY] - 1) { // Down
        [sword toAttackDownState];
      } else if (x == [target getX] + 1 && y == [target getY]) { // Left
        [sword toAttackLeftState];
      } else if (x == [target getX] - 1 && y == [target getY]) { // Right
        [sword toAttackRightState];
      }
      
    } else if (x == [target getX]) {
      
      if (y > [target getY]) { // Hero is directly up.
        while (y - 1 != [target getY] && [world isWalkableAtX: x andY: y - 1] && ![world isInhabitedAtX: x andY: y - 1]) {
          [self moveY: y - 1];
        }
      } else { // Hero is directly down.
        while (y + 1 != [target getY] && [world isWalkableAtX: x andY: y + 1] && ![world isInhabitedAtX: x andY: y + 1]) {
          [self moveY: y + 1];
        }
      }
      
      state = NINJA_DASH_STATE;
      [self setSpeed: getWalkSpeed() + (getWalkSpeed() / 5)];
      animation = dashAnimation;
      [animation reset];
      
    } else if (y == [target getY]) {
      
      if (x > [target getX]) { // Hero is directly left.
        while (x - 1 != [target getX] && [world isWalkableAtX: x - 1 andY: y] && ![world isInhabitedAtX: x - 1 andY: y]) {
          [self moveX: x - 1];
        }
      } else { // Hero is directly right.
        while (x + 1 != [target getX] && [world isWalkableAtX: x + 1 andY: y] && ![world isInhabitedAtX: x + 1 andY: y]) {
          [self moveX: x + 1];
        }
      }
      
      state = NINJA_DASH_STATE;
      [self setSpeed: getWalkSpeed() + (getWalkSpeed() / 5)];
      animation = dashAnimation;
      [animation reset];
      
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
        state = NINJA_MOVE_STATE;
      }
      
      [self wait];
      
    }
    
    // Bound him so he doesn't wander right out of the screen!
    [self boundAtTop: 1 andBottom: ROWS - 2 andLeft: 1 andRight: COLS - 2];
    
    break;
    
  case NINJA_MOVE_STATE:
    if (![self moving]) {
      state = NINJA_STAND_STATE;
    }
    break;
    
  case NINJA_DASH_STATE:
    if (![self moving]) {
      [self setSpeed: getWalkSpeed()];
      // If the target has a walking distance of one...
      if (abs(x - [target getX]) + abs(y - [target getY]) == 1) {
        state = NINJA_ATTACK_STATE;
        animation = attackAnimation;
        [animation reset];
        // Change the state of the sword.
        if (x == [target getX] && y == [target getY] + 1) { // Up
          [sword toAttackUpState];
        } else if (x == [target getX] && y == [target getY] - 1) { // Down
          [sword toAttackDownState];
        } else if (x == [target getX] + 1 && y == [target getY]) { // Left
          [sword toAttackLeftState];
        } else if (x == [target getX] - 1 && y == [target getY]) { // Right
          [sword toAttackRightState];
        }
      } else {
        state = NINJA_STAND_STATE;
        animation = standAnimation;
        [animation reset];
        [self wait];
      }
    }
    break;
    
  case NINJA_ATTACK_STATE:
    if ([animation finished]) {
      [world attackFromTeam: team atX: [target getX] andY: [target getY]];
      state = NINJA_STAND_STATE;
      animation = standAnimation;
      [animation reset];
      [sword toHoldState];
      [self wait];
    }
	break;
	
  }
  
  return self;
  
}


- draw: (BITMAP *) buffer {
  [super draw: buffer];
  [sword draw: buffer];
  return self;
}


- setX: (int) newX {
  [super setX: newX];
  [sword setX: newX];
  return self;
}


- setY: (int) newY {
  [super setY: newY];
  [sword setY: newY];
  return self;
}


- moveX: (int) newX {
  [super moveX: newX];
  [sword moveX: newX];
  return self;
}


- moveY: (int) newY {
  [super moveY: newY];
  [sword moveY: newY];
  return self;
}


- setSpeed: (int) theSpeed {
  speed = theSpeed;
  [sword setSpeed: speed];
  return self;
}


@end
