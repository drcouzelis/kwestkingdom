#ifndef CHARACTER_HEADER
#define CHARACTER_HEADER


#include "Heart.h"
#include "Inhabitable.h"
#include "Livable.h"
#include "KwestKingdom.h"
#include "Moneyable.h"
#include "MoneyBag.h"
#include "Screen.h"
#include "Sprite.h"
#include "Targetable.h"


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


#endif