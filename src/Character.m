#import "Character.h"


@implementation Character


- init {
  
  self = [super init];
  
  if (self) {
    turns = 0;
    health = 1;
    maxHealth = 3;
    money = 0;
    team = NO_TEAM;
    speed = getWalkSpeed();
  }
  
  return self;
  
}


- (BOOL) isDead {
  if (health == 0) {
    return YES;
  }
  return NO;
}


- setHealth: (int) theHealth {
  health = theHealth;
  if (health < 0) {
    health = 0;
  } else if (health > maxHealth) {
    health = maxHealth;
  }
  return self;
}


- (int) getHealth {
  return health;
}


- setMaxHealth: (int) theHealth {
  maxHealth = theHealth;
  return self;
}


- (int) getMaxHealth {
  return maxHealth;
}


- hurt {
  health--;
  if (health < 0) {
    health = 0;
  }
  return self;
}


- (BOOL) waiting {
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


- setTeam: (int) aTeam {
  team = aTeam;
  return self;
}


- (int) getTeam {
  return team;
}


- (int) getMoney {
  return money;
}


- setMoney: (int) amount {
  money = amount;
  if (money < 0) {
    money = 0;
  } else if (money > 999) {
    money = 999;
  }
  return self;
}


@end
