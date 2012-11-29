#import "Room.h"


@implementation Room


- init {
  
  int i;
  
  self = [super init];
  
  if (self) {
    
    pathMap = nil;
    terrainMap = nil;
    
    enemyStorage = nil;
    itemStorage = nil;
    helpTileStorage = [[List alloc] init]; //nil;
    
    entranceFromNextRoomX = 0;
    entranceFromNextRoomY = 0;
    entranceFromPrevRoomX = 0;
    entranceFromPrevRoomY = 0;
    exitToNextRoomX = 0;
    exitToNextRoomY = 0;
    exitToPrevRoomX = 0;
    exitToPrevRoomY = 0;
    
    number = 0;
    
    grassAnimation = nil;
    pathAnimation = nil;
    mountainAnimation = nil;
    waterAnimation = nil;
    shoreNorthAnimation = nil;
    shoreSouthAnimation = nil;
    shoreEastAnimation = nil;
    shoreWestAnimation = nil;
    shoreInsideNEAnimation = nil;
    shoreInsideNWAnimation = nil;
    shoreInsideSEAnimation = nil;
    shoreInsideSWAnimation = nil;
    shoreOutsideNEAnimation = nil;
    shoreOutsideNWAnimation = nil;
    shoreOutsideSEAnimation = nil;
    shoreOutsideSWAnimation = nil;
    
    for (i = 0; i < MAX_NUM_OF_STEPS; i++) {
      path[i] = NO_STEP;
    }
    steps = 0;
    
  }
  
  return self;
  
}


- (void) dealloc {
  
  [grassAnimation release];
  [pathAnimation release];
  [mountainAnimation release];
  [waterAnimation release];
  [shoreNorthAnimation release];
  [shoreSouthAnimation release];
  [shoreEastAnimation release];
  [shoreWestAnimation release];
  [shoreInsideNEAnimation release];
  [shoreInsideNWAnimation release];
  [shoreInsideSEAnimation release];
  [shoreInsideSWAnimation release];
  [shoreOutsideNEAnimation release];
  [shoreOutsideNWAnimation release];
  [shoreOutsideSEAnimation release];
  [shoreOutsideSWAnimation release];
  
  [pathMap release];
  [terrainMap release];
  [enemyStorage release];
  [itemStorage release];
  [helpTileStorage release];
  
  [super dealloc];
  
}


- update {
  [grassAnimation update];
  [pathAnimation update];
  [mountainAnimation update];
  [waterAnimation update];
  [shoreNorthAnimation update];
  [shoreSouthAnimation update];
  [shoreEastAnimation update];
  [shoreWestAnimation update];
  [shoreInsideNEAnimation update];
  [shoreInsideNWAnimation update];
  [shoreInsideSEAnimation update];
  [shoreInsideSWAnimation update];
  [shoreOutsideNEAnimation update];
  [shoreOutsideNWAnimation update];
  [shoreOutsideSEAnimation update];
  [shoreOutsideSWAnimation update];
  return self;
}


- draw: (BITMAP *) buffer {
  
  int x;
  int y;
  
  for (y = 0; y < ROWS; y++) {
    for (x = 0; x < COLS; x++) {
      
      //if ([pathMap getValueAtX: x andY: y] == YES) { // Draw the path
        //[pathAnimation drawTo: buffer atX: x * getTileSize() andY: y * getTileSize()];
      //} else
      if ([terrainMap getValueAtX: x andY: y] == GRASS_TERRAIN) {
        [grassAnimation drawTo: buffer atX: x * getTileSize() andY: y * getTileSize()];
      } else if ([terrainMap getValueAtX: x andY: y] == TREE_TERRAIN) {
        [mountainAnimation drawTo: buffer atX: x * getTileSize() andY: y * getTileSize()];
      } else if ([terrainMap getValueAtX: x andY: y] == WATER_TERRAIN) {
        
        [waterAnimation drawTo: buffer atX: x * getTileSize() andY: y * getTileSize()];
        
        // Add the shore borders
        if ([terrainMap getValueAtX: x andY: y - 1] != WATER_TERRAIN) { // North
          [shoreNorthAnimation drawTo: buffer atX: x * getTileSize() andY: y * getTileSize()];
        }
        if ([terrainMap getValueAtX: x andY: y + 1] != WATER_TERRAIN) { // South
          [shoreSouthAnimation drawTo: buffer atX: x * getTileSize() andY: y * getTileSize()];
        }
        if ([terrainMap getValueAtX: x + 1 andY: y] != WATER_TERRAIN) { // East
          [shoreEastAnimation drawTo: buffer atX: x * getTileSize() andY: y * getTileSize()];
        }
        if ([terrainMap getValueAtX: x - 1 andY: y] != WATER_TERRAIN) { // West
          [shoreWestAnimation drawTo: buffer atX: x * getTileSize() andY: y * getTileSize()];
        }
          
      }
      
    }
  }
  
  // Add the shore corners
  for (y = 0; y < ROWS; y++) {
    for (x = 0; x < COLS; x++) {
      
      if ([terrainMap getValueAtX: x andY: y] == WATER_TERRAIN) {
        
        // Add the shore inside corners
        if (
          [terrainMap getValueAtX: x andY: y - 1] != WATER_TERRAIN &&
          [terrainMap getValueAtX: x + 1 andY: y] != WATER_TERRAIN
        ) { // North East
          [shoreInsideNEAnimation drawTo: buffer atX: x * getTileSize() andY: y * getTileSize()];
        }
        if (
          [terrainMap getValueAtX: x andY: y + 1] != WATER_TERRAIN &&
          [terrainMap getValueAtX: x + 1 andY: y] != WATER_TERRAIN
        ) { // South East
          [shoreInsideSEAnimation drawTo: buffer atX: x * getTileSize() andY: y * getTileSize()];
        }
        if (
          [terrainMap getValueAtX: x andY: y - 1] != WATER_TERRAIN &&
          [terrainMap getValueAtX: x - 1 andY: y] != WATER_TERRAIN
        ) { // North West
          [shoreInsideNWAnimation drawTo: buffer atX: x * getTileSize() andY: y * getTileSize()];
        }
        if (
          [terrainMap getValueAtX: x andY: y + 1] != WATER_TERRAIN &&
          [terrainMap getValueAtX: x - 1 andY: y] != WATER_TERRAIN
        ) { // South West
          [shoreInsideSWAnimation drawTo: buffer atX: x * getTileSize() andY: y * getTileSize()];
        }
          
        // Add the shore outside corners.
        if (
          [terrainMap getValueAtX: x andY: y - 1] == WATER_TERRAIN &&
          [terrainMap getValueAtX: x + 1 andY: y] == WATER_TERRAIN &&
          [terrainMap getValueAtX: x + 1 andY: y - 1] != WATER_TERRAIN
        ) { // North East
          [shoreOutsideNEAnimation drawTo: buffer atX: x * getTileSize() andY: y * getTileSize()];
        }
        if (
          [terrainMap getValueAtX: x andY: y + 1] == WATER_TERRAIN &&
          [terrainMap getValueAtX: x + 1 andY: y] == WATER_TERRAIN &&
          [terrainMap getValueAtX: x + 1 andY: y + 1] != WATER_TERRAIN
        ) { // South East
          [shoreOutsideSEAnimation drawTo: buffer atX: x * getTileSize() andY: y * getTileSize()];
        }
        if (
          [terrainMap getValueAtX: x andY: y - 1] == WATER_TERRAIN &&
          [terrainMap getValueAtX: x - 1 andY: y] == WATER_TERRAIN &&
          [terrainMap getValueAtX: x - 1 andY: y - 1] != WATER_TERRAIN
        ) { // North West
          [shoreOutsideNWAnimation drawTo: buffer atX: x * getTileSize() andY: y * getTileSize()];
        }
        if (
          [terrainMap getValueAtX: x andY: y + 1] == WATER_TERRAIN &&
          [terrainMap getValueAtX: x - 1 andY: y] == WATER_TERRAIN &&
          [terrainMap getValueAtX: x - 1 andY: y + 1] != WATER_TERRAIN
        ) { // South West
          [shoreOutsideSWAnimation drawTo: buffer atX: x * getTileSize() andY: y * getTileSize()];
        }
          
      }
      
    }
  }
  
  return self;
  
}


- (List *) retrieveEnemies {
  List *list;
  list = enemyStorage;
  enemyStorage = nil;
  return list;
}


- storeEnemies: (List *) list {
  [enemyStorage release];
  enemyStorage = list;
  return self;
}


- (List *) retrieveItems {
  List *list;
  list = itemStorage;
  itemStorage = nil;
  return list;
}


- storeItems: (List *) list {
  [itemStorage release];
  itemStorage = list;
  return self;
}


- (List *) retrieveHelpTiles {
  List *list;
  list = helpTileStorage;
  helpTileStorage = nil;
  return list;
}


- storeHelpTiles: (List *) list {
  [helpTileStorage release];
  helpTileStorage = list;
  return self;
}


- setNumber: (int) aNumber {
  number = aNumber;
  return self;
}


- (int) getNumber {
  return number;
}


- setPathMap: (Map *) aPathMap {
  pathMap = aPathMap;
  return self;
}


- addStep: (int) aStep {
  path[steps] = aStep;
  steps++;
  return self;
}


- (int) getSizeOfPath {
  return steps;
}


- (int) getXOfStepNumber: (int) aStep {
  if (path[aStep] == NO_STEP) {
    return NO_STEP;
  }
  return path[aStep] - ((path[aStep] / COLS) * COLS);
}


- (int) getYOfStepNumber: (int) aStep {
  if (path[aStep] == NO_STEP) {
    return NO_STEP;
  }
  return path[aStep] / COLS;
}


- (Map *) getPathMap {
  return pathMap;
}


- setTerrainMap: (Map *) aTerrainMap {
  terrainMap = aTerrainMap;
  return self;
}


- (BOOL) isSwimmableAtX: (int) x andY: (int) y {
  if ([terrainMap getValueAtX: x andY: y] == WATER_TERRAIN) {
    return YES;
  }
  return NO;
}


- (BOOL) isWalkableAtX: (int) x andY: (int) y {
  if ([terrainMap getValueAtX: x andY: y] == GRASS_TERRAIN) {
    return YES;
  }
  return NO;
}


- (BOOL) isJumpableAtX: (int) x andY: (int) y {
  if ([terrainMap getValueAtX: x andY: y] == TREE_TERRAIN) {
    return NO;
  }
  return YES;
}


- (BOOL) isFlyableAtX: (int) x andY: (int) y {
  if ([terrainMap getValueAtX: x andY: y] == TREE_TERRAIN) {
    return NO;
  }
  return YES;
}


- (BOOL) isSoarableAtX: (int) x andY: (int) y {
  // You can soar above any type of terrain.
  return YES;
}


- removeExitToPrevRoom {
  [terrainMap setX: entranceFromPrevRoomX andY: entranceFromPrevRoomY toValue: TREE_TERRAIN];
  [self setExitToPrevRoomX: -1];
  [self setExitToPrevRoomY: -1];
  return self;
}


- (int) getEntranceFromNextRoomX {
  return entranceFromNextRoomX;
}


- (int) getEntranceFromNextRoomY {
  return entranceFromNextRoomY;
}


- (int) getEntranceFromPrevRoomX {
  return entranceFromPrevRoomX;
}


- (int) getEntranceFromPrevRoomY {
  return entranceFromPrevRoomY;
}


- (int) getExitToNextRoomX {
  return exitToNextRoomX;
}


- (int) getExitToNextRoomY {
  return exitToNextRoomY;
}


- (int) getExitToPrevRoomX {
  return exitToPrevRoomX;
}


- (int) getExitToPrevRoomY {
  return exitToPrevRoomY;
}


- setEntranceFromNextRoomX: (int) newX {
  entranceFromNextRoomX = newX;
  return self;
}


- setEntranceFromNextRoomY: (int) newY {
  entranceFromNextRoomY = newY;
  return self;
}


- setEntranceFromPrevRoomX: (int) newX {
  entranceFromPrevRoomX = newX;
  return self;
}


- setEntranceFromPrevRoomY: (int) newY {
  entranceFromPrevRoomY = newY;
  return self;
}


- setExitToNextRoomX: (int) newX {
  exitToNextRoomX = newX;
  return self;
}


- setExitToNextRoomY: (int) newY {
  exitToNextRoomY = newY;
  return self;
}


- setExitToPrevRoomX: (int) newX {
  exitToPrevRoomX = newX;
  return self;
}


- setExitToPrevRoomY: (int) newY {
  exitToPrevRoomY = newY;
  return self;
}


@end

