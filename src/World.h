#ifndef WORLD_HEADER
#define WORLD_HEADER


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


class World {
  
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

  World();
  ~World();

  void updateRoom();
  void updateItems();
  void updateTurn();
  void updateHero();
  void updateEnemies();

  Room *createNextRoom();
  void changeRooms();

  void drawTerrain(BITMAP *buffer);
  void drawCharacters(BITMAP *buffer);
  void drawUserInterface(BITMAP *buffer);

  int getRoomNumber();
  int getMoney();

  void addHelpTile(HelpTile *aHelpTile);
};


#endif
