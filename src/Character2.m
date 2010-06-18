#import "Character2.h"
#import "Command.h"
#import "List.h"
#import "Sprite2.h"


@implementation Character2


- initSprite:(Sprite2 *)aSprite {
  self = [self init];
  if (self) {
    sprite = aSprite;
    commands = [[List alloc] init];
  }
  return self;
}


- free {
  [sprite free];
  [commands freeIncludingItems];
  return [super free];
}


- update {
  [command execute];
  [sprite update];
  return self;
}


- draw:(BITMAP *)canvas {
  [sprite draw:canvas];
  return self;
}


- addCommand:(Command *)aCommand named:(char *)aName {
  [commands add:aCommand named:aName];
  command = aCommand;
  return self;
}


- setCommandTo:(char *)aName {
  [command finish];
  command = [commands itemNamed:aName];
  [command start];
  return self;
}


- (Sprite2 *)sprite {
  return sprite;
}


@end


@implementation Character2 (Moves)


- (BOOL)isWaiting {
  if (turns > 0) {
    return YES;
  }
  return NO;
}


- go {
  turns--;
  if (turns < 0) {
    turns = 0;
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
