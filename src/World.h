#ifndef WORLD_HEADER
#define WORLD_HEADER


#include <Foundation/Foundation.h>
#include "Collectable.h"
#include "Drawable.h"
#include "Enemy.h"
#include "HelpTile.h"
#include "Hero.h"
#include "Inhabitable.h"
#include "List.h"
#include "Room.h"
#include "RoomFactory.h"
#include "Snapshot.h"
#include "Targetable.h"
#include "Traversable.h"
#include "Updatable.h"
#include "Text.h"


class World : public NSObject <Drawable, Inhabitable, Targetable, Traversable, Updatable> {
  
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
  
public:


  updateRoom;
  updateItems;
  updateTurn;
  updateHero;
  updateEnemies;

  (Room *) createNextRoom;
  changeRooms;

  drawTerrain: (BITMAP *) buffer;
  drawCharacters: (BITMAP *) buffer;
  drawUserInterface: (BITMAP *) buffer;

  (int) getRoomNumber;
  (int) getMoney;

  addHelpTile: (id) aHelpTile;


};



#endif