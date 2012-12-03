#ifndef ROOM_HEADER
#define ROOM_HEADER


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


class Room : public Drawable, public Traversable, public Updatable {
  
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

  Room();
  ~Room();

  void setPathMap(Map *aPathMap);
  void setTerrainMap(Map *aTerrainMap);

  void addStep(int aStep);
  int getSizeOfPath();
  int getXOfStepNumber(int aStep;)
  int getYOfStepNumber(int aStep);

  List *retrieveEnemies();
  void storeEnemies(List *list);

  List *retrieveItems();
  void storeItems(List *list);

  List *retrieveHelpTiles();
  void storeHelpTiles(List *list);

  int getEntranceFromNextRoomX();
  int getEntranceFromNextRoomY();
  int getEntranceFromPrevRoomX();
  int getEntranceFromPrevRoomY();
  int getExitToNextRoomX();
  int getExitToNextRoomY();
  int getExitToPrevRoomX();
  int getExitToPrevRoomY();

  void setEntranceFromNextRoomX(int newX);
  void setEntranceFromNextRoomY(int newY);
  void setEntranceFromPrevRoomX(int newX);
  void setEntranceFromPrevRoomY(int newY);
  void setExitToNextRoomX(int newX);
  void setExitToNextRoomY(int newY);
  void setExitToPrevRoomX(int newX);
  void setExitToPrevRoomY(int newY);

  void setNumber(int aNumber);
  int getNumber();

  void removeExitToPrevRoom();

  Map *getPathMap();
};


#endif
