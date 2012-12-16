#include "Animation.h"
#include "Archer.h"
#include "Character.h"
#include "Chomper.h"
#include "ForestRoom.h"
#include "Giant.h"
#include "Heart.h"
#include "List.h"
#include "Map.h"
#include "Ninja.h"
#include "RoomFactory.h"
#include "SnowRoom.h"
#include "UndergroundRoom.h"
#include "World.h"


#define STRAIGHT 0
#define TURN 1

#define OPEN 0
#define PATH 1


int roomNumber;


RoomFactory::RoomFactory() {
  
  world = NULL;
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
  
  pathMap = NULL;
  terrainMap = NULL;
  enemies = NULL;
  items = NULL;
}


Room * RoomFactory::createRoom() {
  
  Room *room;
  int i;
  
  if (type == ROOM_FOREST) {
    room = new ForestRoom();
  } else if (type == ROOM_SNOW) {
    room = new SnowRoom();
  } else if (type == ROOM_UNDERGROUND) {
    room = new UndergroundRoom();
  } else {
    return NULL;
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
    pathMap = new Map();
  } else {
    pathMap = this->generatePathToEdge();
  }
  
  // Create the terrain, enemies, and items.
  terrainMap = this->generateTerrain();
  this->generateEnemies(room);
  this->generateItems(room);
  
  // Set the two entrances to this room.
  room->setEntranceFromPrevRoomX(pathStartX);
  room->setEntranceFromPrevRoomY(pathStartY);
  room->setEntranceFromNextRoomX(pathStopX);
  room->setEntranceFromNextRoomY(pathStopY);
  
  // Set the two exits from this room.
  if (room->getEntranceFromPrevRoomX() == 0) {
    room->setExitToPrevRoomX(room->getEntranceFromPrevRoomX() - 1);
  } else if (room->getEntranceFromPrevRoomX() == COLS - 1) {
    room->setExitToPrevRoomX(room->getEntranceFromPrevRoomX() + 1);
  } else {
    room->setExitToPrevRoomX(room->getEntranceFromPrevRoomX());
  }
  
  if (room->getEntranceFromPrevRoomY() == 0) {
    room->setExitToPrevRoomY(room->getEntranceFromPrevRoomY() - 1);
  } else if (room->getEntranceFromPrevRoomY() == ROWS - 1) {
    room->setExitToPrevRoomY(room->getEntranceFromPrevRoomY() + 1);
  } else {
    room->setExitToPrevRoomY(room->getEntranceFromPrevRoomY());
  }
  
  if (room->getEntranceFromNextRoomX() == 0) {
    room->setExitToNextRoomX(room->getEntranceFromNextRoomX() - 1);
  } else if (room->getEntranceFromNextRoomX() == COLS - 1) {
    room->setExitToNextRoomX(room->getEntranceFromNextRoomX() + 1);
  } else {
    room->setExitToNextRoomX(room->getEntranceFromNextRoomX());
  }
  
  if (room->getEntranceFromNextRoomY() == 0) {
    room->setExitToNextRoomY(room->getEntranceFromNextRoomY() - 1);
  } else if (room->getEntranceFromNextRoomY() == ROWS - 1) {
    room->setExitToNextRoomY(room->getEntranceFromNextRoomY() + 1);
  } else {
    room->setExitToNextRoomY(room->getEntranceFromNextRoomY());
  }
  
  /*
  printf("Entrance from prev %d %d; next %d %d; Exit to prev %d %d; next %d %d \n",
    room->getEntranceFromPrevRoomX(),
    room->getEntranceFromPrevRoomY(),
    room->getEntranceFromNextRoomX(),
    room->getEntranceFromNextRoomY(),
    room->getExitToPrevRoomX(),
    room->getExitToPrevRoomY(),
    room->getExitToNextRoomX(),
    room->getExitToNextRoomY());
  */
  
  // Set other information.
  room->setNumber(number);
  room->setPathMap(pathMap);
  room->setTerrainMap(terrainMap);
  
  for (i = 0; path[i] != NO_STEP; i++) {
    room->addStep(path[i]);
  }
  
  return room;
  
}


bool RoomFactory::characterExists(List *list, int x, int y, int w, int h) {
  
  Character *character;
  int i, j;
  int m, n;
  
  for (i = 0; i < w; i++) {
    for (j = 0; j < h; j++) {
      
      list->iterate();
      while ((character = (Character *)list->getNext()) != NULL) {
        for (m = 0; m < character->getWidth(); m++) {
          for (n = 0; n < character->getHeight(); n++) {
            if (x + i == character->getX() + m && y + j == character->getY() + n) {
              return true;
            }
          }
        }
      }
      
    }
  }
  
  return false;
  
}


void RoomFactory::generateEnemies(Room *room) {
  
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
  
  list = room->getEnemies();
  
  if (difficulty == 0) {
    return;
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
  
  for (y = 1; y < ROWS - 1 && list->getSize() <= maxEnemies; y++) {
    for (x = 1; x < COLS - 1 && list->getSize() <= maxEnemies; x++) {
      
      if (
        x > pathStartX - 3 && x < pathStartX + 3 &&
        y > pathStartY - 3 && y < pathStartY + 3
      ) {
        
        // Don't create enemies too close to the entrance.
        
      } else {
        
        if (
          terrainMap->getValue(x, y) == GRASS_TERRAIN &&
          random_number(0, 99) < chanceOfEnemy &&
          this->characterExists(list, x, y, 1, 1) == false
        ) {
          
          enemy = NULL;
          randomNum = chanceOfChomper + chanceOfArcher + chanceOfNinja + chanceOfGiant;
          randomNum = random_number(1, randomNum);
          
          if (randomNum > lowerChomper && randomNum <= upperChomper) { // Chomper
            enemy = new Chomper();
          } else if (randomNum > lowerArcher && randomNum <= upperArcher) { // Archer
            enemy = new Archer();
          } else if (randomNum > lowerNinja && randomNum <= upperNinja) { // Ninja
            enemy = new Ninja();
          } else if (randomNum > lowerGiant && randomNum <= upperGiant) { // Giant
            if (
              terrainMap->getValue(x + 1, y) == GRASS_TERRAIN &&
              terrainMap->getValue(x, y + 1) == GRASS_TERRAIN &&
              terrainMap->getValue(x + 1, y + 1) == GRASS_TERRAIN &&
              this->characterExists(list, x, y, 2, 2) == false
            ) {
              enemy = new Giant();
            } else {
              // If there's no room for a Giant, make someone else.
              if (randomNum % 3 == 0) {
                enemy = new Chomper();
              } else if (randomNum % 3 == 1) {
                enemy = new Archer();
              } else {
                enemy = new Ninja();
              }
            }
          }
          
          if (enemy != NULL) {
            enemy->setWorld(world);
            enemy->setX(x);
            enemy->setY(y);
            list->append(enemy);
          }
          
        }
        
      }
      
    }
  }
  
  return;
}


void RoomFactory::generateItems(Room *room) {
  
  List *list;
  Heart *heart;
  int x;
  int y;
  int backupX;
  int backupY;
  
  list = room->getItems();
  
  heart = NULL;
  
  // The underground passage
  if (type == ROOM_UNDERGROUND) {
    return;
  }
  
  if (number % 5 == 0) {
    
    for (y = 1; heart == NULL && y < ROWS - 1; y++) {
      for (x = 1; heart == NULL && x < COLS - 1; x++) {
        if (pathMap->getValue(x, y) == true) {
          backupX = x;
          backupY = y;
          if (random_number(1, 5) == 1) {
            // Add a heart item.
            heart = new Heart();
            heart->setX(x);
            heart->setY(y);
          }
        }
      }
    }
    
    if (heart == NULL) {
      heart = new Heart();
      heart->setX(backupX);
      heart->setY(backupY);
    }
    
    list->append(heart);
    
  }
  
  return;
}


#define MIN_NUM_OF_STEPS_IN_PATH 15


Map * RoomFactory::generatePathToEdge() {
  
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
  
  map = new Map();
  pathX = pathStartX;
  pathY = pathStartY;
  direction = UP;
  facing = STRAIGHT;
  stepsTaken = 0;
  
  // Clear the pathway grid.
  for (x = 0; x < COLS; x++) {
    for (y = 0; y < ROWS; y++) {
      map->set(x, y, OPEN);
    }
  }
  
  // Clear the list of ordered steps.
  for (i = 0; i < MAX_NUM_OF_STEPS; i++) {
    path[i] = NO_STEP;
  }
  steps = 0;
  
  // Mark the starting location as part of the path
  map->set(pathX, pathY, PATH);
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
      map->set(pathX, pathY, PATH);
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
      map->set(pathX, pathY, PATH);
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
      printf("%d", map->getValue(x, y));
    }
    printf("\n");
  }
  */
  
  return map;
}


Map * RoomFactory::generateTerrain() {
  
  Map *map;
  
  int chanceOfWater;
  int chanceOfTrees;
  int chanceOfClumpedWater;
  int chanceOfClumpedTrees;
  
  int actualChanceOfWater;
  int actualChanceOfTrees;
  
  int x;
  int y;
  
  map = new Map();
  
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
      
      map->set(x, y, GRASS_TERRAIN);
      
      if (pathMap->getValue(x, y) != PATH) {
        
        // Make a border of mountains.
        if (x == 0 || x == COLS - 1 || y == 0 || y == ROWS - 1) {
          map->set(x, y, TREE_TERRAIN);
        } else {
          
          actualChanceOfWater = chanceOfWater;
          actualChanceOfTrees = chanceOfTrees;
          
          // If this spot has any water around it
          // then increase its chance of being water.
          if (
            map->getValue(x, y - 1) == WATER_TERRAIN ||
            map->getValue(x, y + 1) == WATER_TERRAIN ||
            map->getValue(x - 1, y) == WATER_TERRAIN ||
            map->getValue(x + 1, y) == WATER_TERRAIN
          ) {
            actualChanceOfWater = chanceOfClumpedWater;
          }
          
          if (
            map->getValue(x, y - 1) == TREE_TERRAIN ||
            map->getValue(x, y + 1) == TREE_TERRAIN ||
            map->getValue(x - 1, y) == TREE_TERRAIN ||
            map->getValue(x + 1, y) == TREE_TERRAIN
          ) {
            actualChanceOfTrees = chanceOfClumpedTrees;
          }
          
          if (random_number(1, 100) <= actualChanceOfWater) {
            map->set(x, y, WATER_TERRAIN);
          } else if (random_number(1, 100) <= actualChanceOfTrees) {
            map->set(x, y, TREE_TERRAIN);
          }
          
        }
        
      }
      
    }
  }
  
  return map;
}


void RoomFactory::setWorld(World * aWorld) {
  world = aWorld;
}


void RoomFactory::setType(int theType) {
  type = theType;
}


void RoomFactory::setTerrain(int theTerrain) {
  terrain = theTerrain;
}


void RoomFactory::setNumber(int theNumber) {
  number = theNumber;
}


void RoomFactory::setDifficulty(int theDifficulty) {
  difficulty = theDifficulty;
}


void RoomFactory::setPathBeginX(int thePathBeginX) {
  pathStartX = thePathBeginX;
}


void RoomFactory::setPathBeginY(int thePathBeginY) {
  pathStartY = thePathBeginY;
}


void RoomFactory::setChanceOfChomper(int chance) {
  chanceOfChomper = chance;
}


void RoomFactory::setChanceOfArcher(int chance) {
  chanceOfArcher = chance;
}


void RoomFactory::setChanceOfNinja(int chance) {
  chanceOfNinja = chance;
}


void RoomFactory::setChanceOfGiant(int chance) {
  chanceOfGiant = chance;
}

