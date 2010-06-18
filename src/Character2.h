#import <objc/Object.h>

#include <allegro.h>


@class Command;
@class List;
@class Sprite2;


typedef enum {
  NO_TEAM,
  HERO_TEAM,
  ENEMY_TEAM
} TEAM;


@interface Character2 : Object {
 @private
  Sprite2 *sprite;

  int health;
  int maxHealth;
  int money;
  int team; // Characters on the same team can't hurt each other.

  int turns;

  // Keep a collection of commands
  // Select the one you want via a string "label"
  Command *command; // TEMP
  List *commands;
}

- initSprite:(Sprite2 *)aSprite;

- update;
- draw:(BITMAP *)canvas;

- addCommand:(Command *)aCommand named:(char *)aName;
- setCommandTo:(char *)aName;

- (Sprite2 *)sprite;

@end


@interface Character2 (Moves)
- (BOOL)isWaiting;
- wait;
- go;
@end


@interface Character2 (Teams)
- setTeam:(int)aTeam;
- (int)team;
@end


@interface Character2 (Health)
- setMaxHealth:(int)amount;
- (int)maxHealth;
- setHealth:(int)amount;
- (int)health;
- hurt;
- (BOOL)isDead;
@end


@interface Character2 (Money)
- (int)money;
- setMoney:(int)amount;
@end
