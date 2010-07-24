#import <objc/Object.h>
#import "Animation.h"
#import "HelpTile.h"
#import "List.h"
#import "Map.h"
#import "KwestKingdom.h"
#import "Screen.h"


#define GRASS_TERRAIN 0
#define TREE_TERRAIN 1
#define WATER_TERRAIN 2
#define ENTRANCE_TERRAIN 3
#define EXIT_TERRAIN 4

#define MAX_NUM_OF_STEPS (ROWS * COLS)
#define NO_STEP -1


@interface Room : Object {

  // Add a terrain map, item map, character map...
  Map *terrainMap;
  Map *pathMap;

  List *enemies;
  List *items;
  List *helpTiles;

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

}


- setPathMap: (Map *) aPathMap;
- setTerrainMap: (Map *) aTerrainMap;

- addStep: (int) aStep;
- (int) getSizeOfPath;
- (int) getXOfStepNumber: (int) aStep;
- (int) getYOfStepNumber: (int) aStep;

- (List *)enemies;
- (List *)items;
- (List *)helpTiles;

- setEnemies:(List *)list;
- setItems:(List *)list;
- setHelpTiles:(List *)list;

- (int) getEntranceFromNextRoomX;
- (int) getEntranceFromNextRoomY;
- (int) getEntranceFromPrevRoomX;
- (int) getEntranceFromPrevRoomY;
- (int) getExitToNextRoomX;
- (int) getExitToNextRoomY;
- (int) getExitToPrevRoomX;
- (int) getExitToPrevRoomY;

- setEntranceFromNextRoomX: (int) newX;
- setEntranceFromNextRoomY: (int) newY;
- setEntranceFromPrevRoomX: (int) newX;
- setEntranceFromPrevRoomY: (int) newY;
- setExitToNextRoomX: (int) newX;
- setExitToNextRoomY: (int) newY;
- setExitToPrevRoomX: (int) newX;
- setExitToPrevRoomY: (int) newY;

- setNumber: (int) aNumber;
- (int) getNumber;

- removeExitToPrevRoom;

- (Map *) getPathMap;

- update;
- draw:(BITMAP *)buffer;

- (BOOL) isSwimmableAtX: (int) x andY: (int) y;
- (BOOL) isWalkableAtX: (int) x andY: (int) y;
- (BOOL) isJumpableAtX: (int) x andY: (int) y;
- (BOOL) isFlyableAtX: (int) x andY: (int) y;
- (BOOL) isSoarableAtX: (int) x andY: (int) y;


@end
