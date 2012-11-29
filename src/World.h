#import <Foundation/Foundation.h>
#import "Collectable.h"
#import "Drawable.h"
#import "Enemy.h"
#import "HelpTile.h"
#import "Hero.h"
#import "Inhabitable.h"
#import "List.h"
#import "Room.h"
#import "RoomFactory.h"
#import "Snapshot.h"
#import "Targetable.h"
#import "Traversable.h"
#import "Updatable.h"
#import "Text.h"


@interface World : NSObject <Drawable, Inhabitable, Targetable, Traversable, Updatable> {
  
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


@end

