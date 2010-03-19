/**
 * Copyright 2009 David Couzelis
 * 
 * This file is part of "Kwest Kingdom".
 * 
 * "Kwest Kingdom" is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * "Kwest Kingdom" is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with "Kwest Kingdom".  If not, see <http://www.gnu.org/licenses/>.
 */
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
    speed = CHARACTER_WALK_SPEED;
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
