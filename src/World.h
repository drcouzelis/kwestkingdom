#import <objc/Object.h>

#include <allegro.h>


@class Animation;
@class Character;
@class Enemy;
@class HelpTile;
@class Hero;
@class List;
@class Powerup;
@class Room;
@class RoomFactory;
@class Snapshot;


@interface World : Object {
  
  Hero *hero;
  List *enemies;
  List *rooms;
  
  RoomFactory *roomFactory;
  Room *room;
  
  List *items;
  List *helpTiles;
  
  Animation *heartAnimation;
  Animation *heartEmptyAnimation;
  Animation *helpTileAnimation;
  
  Character *currentCharacter;
  
  int difficulty;
  
  Snapshot *prevRoomSnapshot;
  Snapshot *nextRoomSnapshot;
  
  int state;
  
}


- updateRoom;
- updateItems;
- updateTurn;
- updateHero;
- updateEnemies;

- (Room *) createNextRoom;
- changeRooms;

- drawTerrain: (BITMAP *) buffer;
- drawCharacters: (BITMAP *) buffer;
- drawUserInterface: (BITMAP *) buffer;

- (int) getRoomNumber;
- (int) getMoney;

- addHelpTile: (id) aHelpTile;

- (BOOL) isInhabitedAtX: (int) x andY: (int) y;

- (BOOL) isAttackableFromTeam: (int) team atX: (int) x andY: (int) y;
- attackFromTeam: (int) team atX: (int) x andY: (int) y;
- shake;

- addCharacter:(Character *)aCharacter;
- addItem:(Powerup *)anItem;

- (Character *)getTarget;

- (BOOL) isSwimmableAtX: (int) x andY: (int) y;
- (BOOL) isWalkableAtX: (int) x andY: (int) y;
- (BOOL) isJumpableAtX: (int) x andY: (int) y;
- (BOOL) isFlyableAtX: (int) x andY: (int) y;
- (BOOL) isSoarableAtX: (int) x andY: (int) y;

- update;
- draw:(BITMAP *)buffer;


@end

