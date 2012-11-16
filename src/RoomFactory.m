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
#import "RoomFactory.h"


#define STRAIGHT 0
#define TURN 1

#define OPEN 0
#define PATH 1


int roomNumber;


@implementation RoomFactory


- init {
  
  self = [super init];
  
  if (self) {
    
    world = nil;
    type = ROOM_FOREST;
    terrain = ROOM_RANDOM;
    number = 0;
    difficulty = 0;
    pathStartX = -1;
    pathStartY = -1;
    pathStopX = 0;;
    pathStopY = 0;
    
    // Default values for enemies
    chanceOfChomper = DEFAULT_CHANCE_OF_CHOMPER;
    chanceOfNinja = DEFAULT_CHANCE_OF_NINJA;
    chanceOfArcher = DEFAULT_CHANCE_OF_ARCHER;
    chanceOfGiant = DEFAULT_CHANCE_OF_GIANT;
    
    pathMap = nil;
    terrainMap = nil;
    enemies = nil;
    items = nil;
    
  }
  
  return self;
  
}


- (Room *) createRoom {
  
  Room *room;
  int i;
  
  if (type == ROOM_FOREST) {
    room = [[ForestRoom alloc] init];
  } else if (type == ROOM_SNOW) {
    room = [[SnowRoom alloc] init];
  } else if (type == ROOM_UNDERGROUND) {
    room = [[UndergroundRoom alloc] init];
  } else {
    return nil;
  }
  
  if (terrain == ROOM_RANDOM) {
    terrain = random_number(ROOM_RANDOM, ROOM_DENSE_FOREST);
  }
  
  for (i = 0; i < MAX_NUM_OF_STEPS; i++) {
    path[i] = NO_STEP;
  }
  steps = 0;
  
  // Create a path from the entrance to a random exit.
  if (pathStartX == -1 && pathStartY == -1) {
    pathMap = [[Map alloc] init];
  } else {
    pathMap = [self generatePathToEdge];
  }
  
  // Create the terrain, enemies, and items.
  terrainMap = [self generateTerrain];
  enemies = [self generateEnemies];
  items = [self generateItems];
  
  // Set the two entrances to this room.
  [room setEntranceFromPrevRoomX: pathStartX];
  [room setEntranceFromPrevRoomY: pathStartY];
  [room setEntranceFromNextRoomX: pathStopX];
  [room setEntranceFromNextRoomY: pathStopY];
  
  // Set the two exits from this room.
  if ([room getEntranceFromPrevRoomX] == 0) {
    [room setExitToPrevRoomX: [room getEntranceFromPrevRoomX] - 1];
  } else if ([room getEntranceFromPrevRoomX] == COLS - 1) {
    [room setExitToPrevRoomX: [room getEntranceFromPrevRoomX] + 1];
  } else {
    [room setExitToPrevRoomX: [room getEntranceFromPrevRoomX]];
  }
  
  if ([room getEntranceFromPrevRoomY] == 0) {
    [room setExitToPrevRoomY: [room getEntranceFromPrevRoomY] - 1];
  } else if ([room getEntranceFromPrevRoomY] == ROWS - 1) {
    [room setExitToPrevRoomY: [room getEntranceFromPrevRoomY] + 1];
  } else {
    [room setExitToPrevRoomY: [room getEntranceFromPrevRoomY]];
  }
  
  if ([room getEntranceFromNextRoomX] == 0) {
    [room setExitToNextRoomX: [room getEntranceFromNextRoomX] - 1];
  } else if ([room getEntranceFromNextRoomX] == COLS - 1) {
    [room setExitToNextRoomX: [room getEntranceFromNextRoomX] + 1];
  } else {
    [room setExitToNextRoomX: [room getEntranceFromNextRoomX]];
  }
  
  if ([room getEntranceFromNextRoomY] == 0) {
    [room setExitToNextRoomY: [room getEntranceFromNextRoomY] - 1];
  } else if ([room getEntranceFromNextRoomY] == ROWS - 1) {
    [room setExitToNextRoomY: [room getEntranceFromNextRoomY] + 1];
  } else {
    [room setExitToNextRoomY: [room getEntranceFromNextRoomY]];
  }
  
  /*
  printf("Entrance from prev %d %d; next %d %d; Exit to prev %d %d; next %d %d \n",
    [room getEntranceFromPrevRoomX],
    [room getEntranceFromPrevRoomY],
    [room getEntranceFromNextRoomX],
    [room getEntranceFromNextRoomY],
    [room getExitToPrevRoomX],
    [room getExitToPrevRoomY],
    [room getExitToNextRoomX],
    [room getExitToNextRoomY]);
  */
  
  // Set other information.
  [room setNumber: number];
  [room setPathMap: pathMap];
  [room setTerrainMap: terrainMap];
  [room storeEnemies: enemies];
  [room storeItems: items];
  
  for (i = 0; path[i] != NO_STEP; i++) {
    [room addStep: path[i]];
  }
  
  return room;
  
}


- (BOOL) characterExistsInList: (List *) list atX: (int) x andY: (int) y withWidth: (int) w andHeight: (int) h {
  
  Character *character;
  int i, j;
  int m, n;
  
  for (i = 0; i < w; i++) {
    for (j = 0; j < h; j++) {
      
      [list iterate];
      while ((character = (Character *)[list next]) != nil) {
        for (m = 0; m < [character getWidth]; m++) {
          for (n = 0; n < [character getHeight]; n++) {
            if (x + i == [character getX] + m && y + j == [character getY] + n) {
              return YES;
            }
          }
        }
      }
      
    }
  }
  
  return NO;
  
}


- (List *) generateEnemies {
  
  List *list;
  Character *enemy;
  int x;
  int y;
  
  int chanceOfEnemy;
  
  int lowerChomper;
  int upperChomper;
  int lowerArcher;
  int upperArcher;
  int lowerNinja;
  int upperNinja;
  int lowerGiant;
  int upperGiant;
  
  int maxEnemies;
  
  int randomNum;
  
  list = [[List alloc] init];
  
  if (difficulty == 0) {
    return list;
  }
  
  // The default difficulty.
  chanceOfEnemy = difficulty;
  if (chanceOfEnemy > 7) {
    chanceOfEnemy = 7;
  }
  
  if (difficulty < 7) {
    maxEnemies = 5;
  } else {
    maxEnemies = ROWS * COLS;
  }
  
  lowerChomper = 0;
  upperChomper = chanceOfChomper;
  lowerArcher = upperChomper;
  upperArcher = upperChomper + chanceOfArcher;
  lowerNinja = upperArcher;
  upperNinja = upperArcher + chanceOfNinja;
  lowerGiant = upperNinja;
  upperGiant = upperNinja + chanceOfGiant;
  
  for (y = 1; y < ROWS - 1 && [list size] <= maxEnemies; y++) {
    for (x = 1; x < COLS - 1 && [list size] <= maxEnemies; x++) {
      
      if (
        x > pathStartX - 3 && x < pathStartX + 3 &&
        y > pathStartY - 3 && y < pathStartY + 3
      ) {
        
        // Don't create enemies too close to the entrance.
        
      } else {
        
        if (
          [terrainMap getValueAtX: x andY: y] == GRASS_TERRAIN &&
          random_number(0, 99) < chanceOfEnemy &&
          [self characterExistsInList: list atX: x andY: y withWidth: 1 andHeight: 1] == NO
        ) {
          
          enemy = nil;
          randomNum = chanceOfChomper + chanceOfArcher + chanceOfNinja + chanceOfGiant;
          randomNum = random_number(1, randomNum);
          
          if (randomNum > lowerChomper && randomNum <= upperChomper) { // Chomper
            enemy = [[Chomper alloc] init];
          } else if (randomNum > lowerArcher && randomNum <= upperArcher) { // Archer
            enemy = [[Archer alloc] init];
          } else if (randomNum > lowerNinja && randomNum <= upperNinja) { // Ninja
            enemy = [[Ninja alloc] init];
          } else if (randomNum > lowerGiant && randomNum <= upperGiant) { // Giant
            if (
              [terrainMap getValueAtX: x + 1 andY: y] == GRASS_TERRAIN &&
              [terrainMap getValueAtX: x andY: y + 1] == GRASS_TERRAIN &&
              [terrainMap getValueAtX: x + 1 andY: y + 1] == GRASS_TERRAIN &&
              [self characterExistsInList: list atX: x andY: y withWidth: 2 andHeight: 2] == NO
            ) {
              enemy = [[Giant alloc] init];
            } else {
              // If there's no room for a Giant, make someone else.
              if (randomNum % 3 == 0) {
                enemy = [[Chomper alloc] init];
              } else if (randomNum % 3 == 1) {
                enemy = [[Archer alloc] init];
              } else {
                enemy = [[Ninja alloc] init];
              }
            }
          }
          
          if (enemy != nil) {
            [enemy setWorld: world];
            [enemy setX: x];
            [enemy setY: y];
            [list append: enemy];
          }
          
        }
        
      }
      
    }
  }
  
  return list;
  
}


- (List *) generateItems {
  
  List *list;
  Heart *heart;
  int x;
  int y;
  int backupX;
  int backupY;
  
  list = [[List alloc] init];
  
  heart = nil;
  
  // The underground passage
  if (type == ROOM_UNDERGROUND) {
    
  }
  
  if (number % 5 == 0) {
    
    for (y = 1; heart == nil && y < ROWS - 1; y++) {
      for (x = 1; heart == nil && x < COLS - 1; x++) {
        if ([pathMap getValueAtX: x andY: y] == YES) {
          backupX = x;
          backupY = y;
          if (random_number(1, 5) == 1) {
            // Add a heart item.
            heart = [[Heart alloc] init];
            [heart setX: x];
            [heart setY: y];
          }
        }
      }
    }
    
    if (heart == nil) {
      heart = [[Heart alloc] init];
      [heart setX: backupX];
      [heart setY: backupY];
    }
    
    [list append: heart];
    
  }
  
  return list;
  
}


#define MIN_NUM_OF_STEPS_IN_PATH 15


- (Map *) generatePathToEdge {
  
  Map *map;
  
  int pathX;
  int pathY;
  int changeX;
  int changeY;
  
  int direction;
  int facing;
  int stepsTaken;
  
  int x;
  int y;
  
  int num;
  int i;
  
  map = [[Map alloc] init];
  pathX = pathStartX;
  pathY = pathStartY;
  direction = UP;
  facing = STRAIGHT;
  stepsTaken = 0;
  
  // Clear the pathway grid.
  for (x = 0; x < COLS; x++) {
    for (y = 0; y < ROWS; y++) {
      [map setX: x andY: y toValue: OPEN];
    }
  }
  
  // Clear the list of ordered steps.
  for (i = 0; i < MAX_NUM_OF_STEPS; i++) {
    path[i] = NO_STEP;
  }
  steps = 0;
  
  // Mark the starting location as part of the path
  [map setX: pathX andY: pathY toValue: PATH];
  path[steps] = (pathY * COLS) + pathX;
  steps++;
  
  if (pathY == ROWS - 1) {
    direction = UP;
  } else if (pathY == 0) {
    direction = DOWN;
  } else if (pathX == COLS - 1) {
    direction = LEFT;
  } else if (pathX == 0) {
    direction = RIGHT;
  } else {
    direction = UP;
  }
  
  // Loop while not at the edge of the screen...
  do {
    
    changeX = 0;
    changeY = 0;
    
    // Determine how many new steps to take and in which direction.
    if (facing == STRAIGHT) {
      num = random_number(1, 3);
      if (direction == UP) {
        changeY = -num;
      } else if (direction == DOWN) {
        changeY = num;
      } else if (direction == RIGHT) {
        changeX = num;
      } else if (direction == LEFT) {
        changeX = -num;
      }
    } else if (facing == TURN) {
      num = random_number(-4, 4);
      if (direction == UP || direction == DOWN) {
        changeX = num;
      } else if (direction == LEFT || direction == RIGHT) {
        changeY = num;
      }
    }
    
    // Make sure the path is pretty long.
    if (pathX + changeX >= COLS - 1 || pathX + changeX <= 0) {
      if (stepsTaken + abs(changeX) < MIN_NUM_OF_STEPS_IN_PATH) {
        changeX = -changeX;
      }
    }
    
    if (pathY + changeY >= ROWS - 1 || pathY + changeY <= 0) {
      if (stepsTaken + abs(changeY) < MIN_NUM_OF_STEPS_IN_PATH) {
        changeY = -changeY;
      }
    }
    
    // Add the new random X steps to the path map.
    for (i = 0; i < abs(changeX); i++) {
      pathX += changeX / abs(changeX);
      if (pathX < 0) {
        pathX = 0;
      } else if (pathX > COLS - 1) {
        pathX = COLS - 1;
      }
      [map setX: pathX andY: pathY toValue: PATH];
      stepsTaken++;
      path[steps] = (pathY * COLS) + pathX;
      steps++;
    }
    
    // Same for the Y steps.
    for (i = 0; i < abs(changeY); i++) {
      pathY += changeY / abs(changeY);
      if (pathY < 0) {
        pathY = 0;
      } else if (pathY > ROWS - 1) {
        pathY = ROWS - 1;
      }
      [map setX: pathX andY: pathY toValue: PATH];
      stepsTaken++;
      path[steps] = (pathY * COLS) + pathX;
      steps++;
    }
    
    // Change direction.
    if (facing == STRAIGHT) {
      facing = TURN;
    } else {
      facing = STRAIGHT;
    }
    
  } while (pathX != 0 && pathX != COLS - 1 && pathY != 0 && pathY != ROWS - 1);
  
  pathStopX = pathX;
  pathStopY = pathY;
  
  // Let's see what the newly created pathway looks like!
  /*
  for (y = 0; y < ROWS; y++) {
    for (x = 0; x < COLS; x++) {
      printf("%d", [map getValueAtX: x andY: y]);
    }
    printf("\n");
  }
  */
  
  return map;
  
}


- (Map *) generateTerrain {
  
  Map *map;
  
  int chanceOfWater;
  int chanceOfTrees;
  int chanceOfClumpedWater;
  int chanceOfClumpedTrees;
  
  int actualChanceOfWater;
  int actualChanceOfTrees;
  
  int x;
  int y;
  
  map = [[Map alloc] init];
  
  if (terrain == ROOM_NO_WATER_AND_NO_TREES) {
    chanceOfWater = 0;
    chanceOfTrees = 0;
    chanceOfClumpedWater = 0;
    chanceOfClumpedTrees = 0;
  } else if (terrain == ROOM_NO_WATER) {
    chanceOfWater = 0;
    chanceOfTrees = 10;
    chanceOfClumpedWater = 0;
    chanceOfClumpedTrees = 40;
  } else if (terrain == ROOM_NO_TREES) {
    chanceOfWater = 3;
    chanceOfTrees = 0;
    chanceOfClumpedWater = 75;
    chanceOfClumpedTrees = 0;
  } else if (terrain == ROOM_DENSE_FOREST) {
    chanceOfWater = 2;
    chanceOfTrees = 10;
    chanceOfClumpedWater = 30;
    chanceOfClumpedTrees = 40;
  } else if (terrain == ROOM_SWAMP) {
    chanceOfWater = 10;
    chanceOfTrees = 3;
    chanceOfClumpedWater = 75;
    chanceOfClumpedTrees = 3;
  } else if (terrain == ROOM_LAKE) {
    chanceOfWater = 30;
    chanceOfTrees = 1;
    chanceOfClumpedWater = 75;
    chanceOfClumpedTrees = 1;
  } else { // ROOM_RANDOM
    chanceOfWater = 3;
    chanceOfTrees = 10;
    chanceOfClumpedWater = 50;
    chanceOfClumpedTrees = 10;
  }
  
  for (x = 0; x < COLS; x++) {
    for (y = 0; y < ROWS; y++) {
      
      [map setX: x andY: y toValue: GRASS_TERRAIN];
      
      if ([pathMap getValueAtX: x andY: y] != PATH) {
        
        // Make a border of mountains.
        if (x == 0 || x == COLS - 1 || y == 0 || y == ROWS - 1) {
          [map setX: x andY: y toValue: TREE_TERRAIN];
        } else {
          
          actualChanceOfWater = chanceOfWater;
          actualChanceOfTrees = chanceOfTrees;
          
          // If this spot has any water around it
          // then increase its chance of being water.
          if (
            [map getValueAtX: x andY: y - 1] == WATER_TERRAIN ||
            [map getValueAtX: x andY: y + 1] == WATER_TERRAIN ||
            [map getValueAtX: x - 1 andY: y] == WATER_TERRAIN ||
            [map getValueAtX: x + 1 andY: y] == WATER_TERRAIN
          ) {
            actualChanceOfWater = chanceOfClumpedWater;
          }
          
          if (
            [map getValueAtX: x andY: y - 1] == TREE_TERRAIN ||
            [map getValueAtX: x andY: y + 1] == TREE_TERRAIN ||
            [map getValueAtX: x - 1 andY: y] == TREE_TERRAIN ||
            [map getValueAtX: x + 1 andY: y] == TREE_TERRAIN
          ) {
            actualChanceOfTrees = chanceOfClumpedTrees;
          }
          
          if (random_number(1, 100) <= actualChanceOfWater) {
            [map setX: x andY: y toValue: WATER_TERRAIN];
          } else if (random_number(1, 100) <= actualChanceOfTrees) {
            [map setX: x andY: y toValue: TREE_TERRAIN];
          }
          
        }
        
      }
      
    }
  }
  
  return map;

}


- setWorld: (id<Inhabitable, Targetable, Traversable>) aWorld {
  world = aWorld;
  return self;
}


- setType: (int) theType {
  type = theType;
  return self;
}


- setTerrain: (int) theTerrain {
  terrain = theTerrain;
  return self;
}


- setNumber: (int) theNumber {
  number = theNumber;
  return self;
}


- setDifficulty: (int) theDifficulty {
  difficulty = theDifficulty;
  return self;
}


- setPathBeginX: (int) thePathBeginX {
  pathStartX = thePathBeginX;
  return self;
}


- setPathBeginY: (int) thePathBeginY {
  pathStartY = thePathBeginY;
  return self;
}


- setChanceOfChomper: (int) chance {
  chanceOfChomper = chance;
  return self;
}


- setChanceOfArcher: (int) chance {
  chanceOfArcher = chance;
  return self;
}


- setChanceOfNinja: (int) chance {
  chanceOfNinja = chance;
  return self;
}


- setChanceOfGiant: (int) chance {
  chanceOfGiant = chance;
  return self;
}


@end

