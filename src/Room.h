/**
 * Copyright 2009 David Couzelis
 * 
 * This file is part of "Kwest Kingdom".
 * 
 * "Kwest Kingdom" is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * "Kwest Kingdom" is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with "Kwest Kingdom".  If not, see <http://www.gnu.org/licenses/>.
 */
#import <objc/Object.h>
#import "Animation.h"
#import "Drawable.h"
#import "HelpTile.h"
#import "List.h"
#import "Map.h"
#import "KwestKingdom.h"
#import "Screen.h"
#import "Traversable.h"
#import "Updatable.h"


#define GRASS_TERRAIN 0
#define TREE_TERRAIN 1
#define WATER_TERRAIN 2
#define ENTRANCE_TERRAIN 3
#define EXIT_TERRAIN 4

#define MAX_NUM_OF_STEPS (ROWS * COLS)
#define NO_STEP -1


@interface Room : Object <Drawable, Traversable, Updatable> {
  
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
  
}


- setPathMap: (Map *) aPathMap;
- setTerrainMap: (Map *) aTerrainMap;

- addStep: (int) aStep;
- (int) getSizeOfPath;
- (int) getXOfStepNumber: (int) aStep;
- (int) getYOfStepNumber: (int) aStep;

- (List *) retrieveEnemies;
- storeEnemies: (List *) list;

- (List *) retrieveItems;
- storeItems: (List *) list;

- (List *) retrieveHelpTiles;
- storeHelpTiles: (List *) list;

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


@end
