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
