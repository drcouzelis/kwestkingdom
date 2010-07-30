#import "Character2.h"
#import "Sprite2.h"
#import "State.h"


@implementation Character2


- initSprite:(Sprite2 *)aSprite {
  if ([self init]) {
    sprite = aSprite;
  }
  return self;
}


- free {
  [sprite free];
  int i;
  for (i = 0; i < numStates; i++) {
    [states[i] free];
  }
  return [super free];
}


- update {
  [sprite update];
  return self;
}


- draw:(BITMAP *)canvas {
  [sprite draw:canvas];
  return self;
}


- addState:(State *)aState {
  if (numStates < MAX_STATES) {
    states[numStates] = aState;
    numStates++;
    [self setState:aState]; // Set the current state to the new state
  } else {
    fprintf(stderr, "Failed to add state because there are too many. \n");
  }
  return self;
}


- setState:(State *)aState {
  [state finish];
  state = aState;
  [state start];
  return self;
}


@end


@implementation Character2 (Moves)


- (BOOL)finishedTurn {
  if (turns > 0) {
    return YES;
  }
  return NO;
}


- takeTurn {
  turns--;
  if (turns < 0) {
    turns = 0;
  }
  if (turns == 0) {
    [state update];
  }
  return self;
}


- wait {
  turns++;
  return self;
}


@end


@implementation Character2 (Teams)


- setTeam:(int)aTeam {
  team = aTeam;
  return self;
}


- (int)team {
  return team;
}


@end


@implementation Character2 (Health)


- setMaxHealth:(int)amount {
  maxHealth = amount;
  return self;
}


- (int)maxHealth {
  return maxHealth;
}


- setHealth:(int)amount {
  health = amount;
  if (health < 0) {
    health = 0;
  } else if (health > maxHealth) {
    if (maxHealth <= 0) {
      fprintf(stderr, "Warning, max health of character is %d. \n", maxHealth);
    }
    health = maxHealth;
  }
  return self;
}


- (int)health {
  return health;
}


- hurt {
  health--;
  if (health < 0) {
    health = 0;
  }
  return self;
}


- (BOOL)isDead {
  if (health == 0) {
    return YES;
  }
  return NO;
}


@end


@implementation Character2 (Money)


- (int)money {
  return money;
}


- setMoney:(int)amount {
  money = amount;
  if (money < 0) {
    money = 0;
  } else if (money > 999) {
    money = 999;
  }
  return self;
}


@end


@implementation Character2 (Sprite)


- (int)width {
  return [sprite width];
}


- (int)height {
  return [sprite height];
}


- (int)x {
  return [sprite x];
}


- (int)y {
  return [sprite y];
}


- setX:(int)x {
  return [sprite setX:x];
}


- setY:(int)y {
  return [sprite setY:y];
}


@end


@implementation Character2 (Deprecated)


- (int)getWidth {
  return [self width];
}


- (int)getHeight {
  return [self height];
}


- (int)getX {
  return [self x];
}


- (int)getY {
  return [self y];
}


- (int)getTeam {
  return [self team];
}


- dropItem {
  return self;
}


- (BOOL)isWaiting {
  return [self finishedTurn];
}


- (Sprite2 *)sprite {
  return sprite;
}


@end

