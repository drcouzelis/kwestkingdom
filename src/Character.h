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
#import "Heart.h"
#import "Inhabitable.h"
#import "Livable.h"
#import "KwestKingdom.h"
#import "Moneyable.h"
#import "MoneyBag.h"
#import "Screen.h"
#import "Sprite.h"
#import "Targetable.h"


typedef enum {
  NO_TEAM,
  HERO_TEAM,
  ENEMY_TEAM
} TEAM;


@interface Character : Sprite <Livable, Moneyable> {
  
  int health;
  int maxHealth;
  int money;
  int team; // Characters on the same team can't hurt each other.
  
  int turns;
  
}


- (BOOL) waiting;
- wait;
- go;

- setTeam: (int) aTeam;
- (int) getTeam;


@end
