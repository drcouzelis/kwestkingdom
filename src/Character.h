#import "Heart.h"
#import "KwestKingdom.h"
#import "MoneyBag.h"
#import "Screen.h"
#import "Sprite.h"


typedef enum {
  NO_TEAM,
  HERO_TEAM,
  ENEMY_TEAM
} TEAM;


@interface Character : Sprite {
  
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

- (BOOL) isDead;
- setHealth: (int) theHealth;
- (int) getHealth;
- setMaxHealth: (int) theHealth;
- (int) getMaxHealth;
- hurt;

- (int) getMoney;
- setMoney: (int) amount;


@end
