#import <objc/Object.h>

#include <allegro.h>


#define MAX_STATES 16


@class State;
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
  State *state;
  State *states[MAX_STATES];
  int numStates;
}

- initSprite:(Sprite2 *)aSprite;

- update;
- draw:(BITMAP *)canvas;

- addState:(State *)aState;
- setState:(State *)aState;

@end


@interface Character2 (Moves)
- takeTurn;
- (BOOL)finishedTurn;
- wait;
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


@interface Character2 (Sprite)
- (int)width;
- (int)height;
- (int)x;
- (int)y;
- setX:(int)x;
- setY:(int)y;
@end


@interface Character2 (Deprecated)
- (int)getWidth;
- (int)getHeight;
- (int)getX;
- (int)getY;
- (int)getTeam;
- dropItem;
- (BOOL)isWaiting;
- (Sprite2 *)sprite;
@end

