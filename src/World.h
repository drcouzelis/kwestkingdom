#import <objc/Object.h>

#include <allegro.h>

#import "Environment.h"


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


@interface World : Object <Environment> {

  Hero *hero;
  List *rooms;

  RoomFactory *roomFactory;
  Room *room;

  Animation *heartAnimation;
  Animation *heartEmptyAnimation;
  Animation *helpTileAnimation;

  id currentCharacter;

  int difficulty;

  Snapshot *prevRoomSnapshot;
  Snapshot *nextRoomSnapshot;

  int state;

}

- (Room *) createNextRoom;
- changeRooms;

- (int) getRoomNumber;
- (int) getMoney;

- addHelpTile: (id) aHelpTile;

- addCharacter:(id)aCharacter;
- addItem:(Powerup *)anItem;

- update;
- updateRoom;
- updateItems;
- updateTurn;
- updateHero;
- updateEnemies;

- draw:(BITMAP *)buffer;
- drawTerrain: (BITMAP *) buffer;
- drawCharacters: (BITMAP *) buffer;
- drawUserInterface: (BITMAP *) buffer;

@end

