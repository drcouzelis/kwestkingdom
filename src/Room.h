#ifndef ROOM_HEADER
#define ROOM_HEADER


#include "KwestKingdom.h"

class Animation;
class List;
class Map;


#define GRASS_TERRAIN 0
#define TREE_TERRAIN 1
#define WATER_TERRAIN 2
#define ENTRANCE_TERRAIN 3
#define EXIT_TERRAIN 4

#define MAX_NUM_OF_STEPS (ROWS * COLS)
#define NO_STEP  1


class Room {
 
protected:

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
  virtual ~Room();

  virtual void update();
  virtual void draw(BITMAP *buffer);

  virtual bool isSwimmable(int x, int y);
  virtual bool isWalkable(int x, int y);
  virtual bool isJumpable(int x, int y);
  virtual bool isFlyable(int x, int y);
  virtual bool isSoarable(int x, int y);

  virtual List *getEnemies();
  virtual List *getItems();
  virtual List *getHelpTiles();

  virtual void setPathMap(Map *aPathMap);
  virtual void setTerrainMap(Map *aTerrainMap);

  virtual void addStep(int aStep);
  virtual int getSizeOfPath();
  virtual int getXOfStepNumber(int aStep);
  virtual int getYOfStepNumber(int aStep);

  virtual int getEntranceFromNextRoomX();
  virtual int getEntranceFromNextRoomY();
  virtual int getEntranceFromPrevRoomX();
  virtual int getEntranceFromPrevRoomY();
  virtual int getExitToNextRoomX();
  virtual int getExitToNextRoomY();
  virtual int getExitToPrevRoomX();
  virtual int getExitToPrevRoomY();

  virtual void setEntranceFromNextRoomX(int newX);
  virtual void setEntranceFromNextRoomY(int newY);
  virtual void setEntranceFromPrevRoomX(int newX);
  virtual void setEntranceFromPrevRoomY(int newY);
  virtual void setExitToNextRoomX(int newX);
  virtual void setExitToNextRoomY(int newY);
  virtual void setExitToPrevRoomX(int newX);
  virtual void setExitToPrevRoomY(int newY);

  virtual void setNumber(int aNumber);
  virtual int getNumber();

  virtual void removeExitToPrevRoom();

  virtual Map *getPathMap();
};


#endif
