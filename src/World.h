#import <objc/Object.h>
#import "Enemy.h"
#import "HelpTile.h"
#import "Hero.h"
#import "Inhabitable.h"
#import "List.h"
#import "Powerup.h"
#import "Room.h"
#import "RoomFactory.h"
#import "Snapshot.h"
#import "Targetable.h"
#import "Traversable.h"
#import "Updatable.h"
#import "Text.h"


@interface World : Object <Inhabitable, Targetable, Traversable, Updatable> {

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


- draw:(BITMAP *)buffer;

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


@end

