#ifndef ROOM_HEADER
#define ROOM_HEADER


#include <Foundation/Foundation.h>
#include "Animation.h"
#include "Drawable.h"
#include "HelpTile.h"
#include "List.h"
#include "Map.h"
#include "KwestKingdom.h"
#include "Screen.h"
#include "Traversable.h"
#include "Updatable.h"


#define GRASS_TERRAIN 0
#define TREE_TERRAIN 1
#define WATER_TERRAIN 2
#define ENTRANCE_TERRAIN 3
#define EXIT_TERRAIN 4

#define MAX_NUM_OF_STEPS (ROWS * COLS)
#define NO_STEP  1


class Room : public NSObject <Drawable, Traversable, Updatable> {
  
  // Add a terrain map, item map, character map...
  Map *terrainMap;
  Map *pathMap;
  
  List *enemyStorage;
  List *itemStorage;
  List *helpTileStorage;
  
  int entranceFromNextRoomX;
  int entranceFromNextRoomY;
  int entranceFromPrevRoomX;
  int entranceFromPrevRoomY;
  
  int exitToNextRoomX;
  int exitToNextRoomY;
  int exitToPrevRoomX;
  int exitToPrevRoomY;
  
  int number;
  
  Animation *grassAnimation;
  Animation *pathAnimation;
  Animation *mountainAnimation;
  Animation *waterAnimation;
  Animation *shoreNorthAnimation;
  Animation *shoreSouthAnimation;
  Animation *shoreEastAnimation;
  Animation *shoreWestAnimation;
  Animation *shoreInsideNEAnimation;
  Animation *shoreInsideNWAnimation;
  Animation *shoreInsideSEAnimation;
  Animation *shoreInsideSWAnimation;
  Animation *shoreOutsideNEAnimation;
  Animation *shoreOutsideNWAnimation;
  Animation *shoreOutsideSEAnimation;
  Animation *shoreOutsideSWAnimation;
  
  int path[MAX_NUM_OF_STEPS];
  int steps;
  
public:


  setPathMap: (Map *) aPathMap;
  setTerrainMap: (Map *) aTerrainMap;

  addStep: (int) aStep;
  (int) getSizeOfPath;
  (int) getXOfStepNumber: (int) aStep;
  (int) getYOfStepNumber: (int) aStep;

  (List *) retrieveEnemies;
  storeEnemies: (List *) list;

  (List *) retrieveItems;
  storeItems: (List *) list;

  (List *) retrieveHelpTiles;
  storeHelpTiles: (List *) list;

  (int) getEntranceFromNextRoomX;
  (int) getEntranceFromNextRoomY;
  (int) getEntranceFromPrevRoomX;
  (int) getEntranceFromPrevRoomY;
  (int) getExitToNextRoomX;
  (int) getExitToNextRoomY;
  (int) getExitToPrevRoomX;
  (int) getExitToPrevRoomY;

  setEntranceFromNextRoomX: (int) newX;
  setEntranceFromNextRoomY: (int) newY;
  setEntranceFromPrevRoomX: (int) newX;
  setEntranceFromPrevRoomY: (int) newY;
  setExitToNextRoomX: (int) newX;
  setExitToNextRoomY: (int) newY;
  setExitToPrevRoomX: (int) newX;
  setExitToPrevRoomY: (int) newY;

  setNumber: (int) aNumber;
  (int) getNumber;

  removeExitToPrevRoom;

  (Map *) getPathMap;


};


#endif