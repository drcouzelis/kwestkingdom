#include "Animation.h"
#include "List.h"
#include "Map.h"
#include "Room.h"


Room::Room() {
  
  int i;
  
  pathMap = NULL;
  terrainMap = NULL;
  
  enemies = new List();
  items = new List();
  helpTiles = new List();
  
  entranceFromNextRoomX = 0;
  entranceFromNextRoomY = 0;
  entranceFromPrevRoomX = 0;
  entranceFromPrevRoomY = 0;
  exitToNextRoomX = 0;
  exitToNextRoomY = 0;
  exitToPrevRoomX = 0;
  exitToPrevRoomY = 0;
  
  number = 0;
  
  grassAnimation = NULL;
  pathAnimation = NULL;
  mountainAnimation = NULL;
  waterAnimation = NULL;
  shoreNorthAnimation = NULL;
  shoreSouthAnimation = NULL;
  shoreEastAnimation = NULL;
  shoreWestAnimation = NULL;
  shoreInsideNEAnimation = NULL;
  shoreInsideNWAnimation = NULL;
  shoreInsideSEAnimation = NULL;
  shoreInsideSWAnimation = NULL;
  shoreOutsideNEAnimation = NULL;
  shoreOutsideNWAnimation = NULL;
  shoreOutsideSEAnimation = NULL;
  shoreOutsideSWAnimation = NULL;
  
  for (i = 0; i < MAX_NUM_OF_STEPS; i++) {
    path[i] = NO_STEP;
  }
  steps = 0;
}


Room::~Room() {
  delete grassAnimation;
  delete pathAnimation;
  delete mountainAnimation;
  delete waterAnimation;
  delete shoreNorthAnimation;
  delete shoreSouthAnimation;
  delete shoreEastAnimation;
  delete shoreWestAnimation;
  delete shoreInsideNEAnimation;
  delete shoreInsideNWAnimation;
  delete shoreInsideSEAnimation;
  delete shoreInsideSWAnimation;
  delete shoreOutsideNEAnimation;
  delete shoreOutsideNWAnimation;
  delete shoreOutsideSEAnimation;
  delete shoreOutsideSWAnimation;

  delete pathMap;
  delete terrainMap;

  delete enemies;
  delete items;
  delete helpTiles;
}


void Room::update() {
  grassAnimation->update();
  pathAnimation->update();
  mountainAnimation->update();
  waterAnimation->update();
  shoreNorthAnimation->update();
  shoreSouthAnimation->update();
  shoreEastAnimation->update();
  shoreWestAnimation->update();
  shoreInsideNEAnimation->update();
  shoreInsideNWAnimation->update();
  shoreInsideSEAnimation->update();
  shoreInsideSWAnimation->update();
  shoreOutsideNEAnimation->update();
  shoreOutsideNWAnimation->update();
  shoreOutsideSEAnimation->update();
  shoreOutsideSWAnimation->update();

}


void Room::draw(BITMAP * buffer) {
  
  int x;
  int y;
  
  for (y = 0; y < ROWS; y++) {
    for (x = 0; x < COLS; x++) {
      
      //if (pathMap->getValue(x, y) == true) { // Draw the path
        //pathAnimation->drawTo(buffer, x * getTileSize(), y * getTileSize());
      //} else
      if (terrainMap->getValue(x, y) == GRASS_TERRAIN) {
        grassAnimation->drawTo(buffer, x * getTileSize(), y * getTileSize());
      } else if (terrainMap->getValue(x, y) == TREE_TERRAIN) {
        mountainAnimation->drawTo(buffer, x * getTileSize(), y * getTileSize());
      } else if (terrainMap->getValue(x, y) == WATER_TERRAIN) {
        
        waterAnimation->drawTo(buffer, x * getTileSize(), y * getTileSize());
        
        // Add the shore borders
        if (terrainMap->getValue(x, y - 1) != WATER_TERRAIN) { // North
          shoreNorthAnimation->drawTo(buffer, x * getTileSize(), y * getTileSize());
        }
        if (terrainMap->getValue(x, y + 1) != WATER_TERRAIN) { // South
          shoreSouthAnimation->drawTo(buffer, x * getTileSize(), y * getTileSize());
        }
        if (terrainMap->getValue(x + 1, y) != WATER_TERRAIN) { // East
          shoreEastAnimation->drawTo(buffer, x * getTileSize(), y * getTileSize());
        }
        if (terrainMap->getValue(x - 1, y) != WATER_TERRAIN) { // West
          shoreWestAnimation->drawTo(buffer, x * getTileSize(), y * getTileSize());
        }
          
      }
      
    }
  }
  
  // Add the shore corners
  for (y = 0; y < ROWS; y++) {
    for (x = 0; x < COLS; x++) {
      
      if (terrainMap->getValue(x, y) == WATER_TERRAIN) {
        
        // Add the shore inside corners
        if (
          terrainMap->getValue(x, y - 1) != WATER_TERRAIN &&
          terrainMap->getValue(x + 1, y) != WATER_TERRAIN
        ) { // North East
          shoreInsideNEAnimation->drawTo(buffer, x * getTileSize(), y * getTileSize());
        }
        if (
          terrainMap->getValue(x, y + 1) != WATER_TERRAIN &&
          terrainMap->getValue(x + 1, y) != WATER_TERRAIN
        ) { // South East
          shoreInsideSEAnimation->drawTo(buffer, x * getTileSize(), y * getTileSize());
        }
        if (
          terrainMap->getValue(x, y - 1) != WATER_TERRAIN &&
          terrainMap->getValue(x - 1, y) != WATER_TERRAIN
        ) { // North West
          shoreInsideNWAnimation->drawTo(buffer, x * getTileSize(), y * getTileSize());
        }
        if (
          terrainMap->getValue(x, y + 1) != WATER_TERRAIN &&
          terrainMap->getValue(x - 1, y) != WATER_TERRAIN
        ) { // South West
          shoreInsideSWAnimation->drawTo(buffer, x * getTileSize(), y * getTileSize());
        }
          
        // Add the shore outside corners.
        if (
          terrainMap->getValue(x, y - 1) == WATER_TERRAIN &&
          terrainMap->getValue(x + 1, y) == WATER_TERRAIN &&
          terrainMap->getValue(x + 1, y - 1) != WATER_TERRAIN
        ) { // North East
          shoreOutsideNEAnimation->drawTo(buffer, x * getTileSize(), y * getTileSize());
        }
        if (
          terrainMap->getValue(x, y + 1) == WATER_TERRAIN &&
          terrainMap->getValue(x + 1, y) == WATER_TERRAIN &&
          terrainMap->getValue(x + 1, y + 1) != WATER_TERRAIN
        ) { // South East
          shoreOutsideSEAnimation->drawTo(buffer, x * getTileSize(), y * getTileSize());
        }
        if (
          terrainMap->getValue(x, y - 1) == WATER_TERRAIN &&
          terrainMap->getValue(x - 1, y) == WATER_TERRAIN &&
          terrainMap->getValue(x - 1, y - 1) != WATER_TERRAIN
        ) { // North West
          shoreOutsideNWAnimation->drawTo(buffer, x * getTileSize(), y * getTileSize());
        }
        if (
          terrainMap->getValue(x, y + 1) == WATER_TERRAIN &&
          terrainMap->getValue(x - 1, y) == WATER_TERRAIN &&
          terrainMap->getValue(x - 1, y + 1) != WATER_TERRAIN
        ) { // South West
          shoreOutsideSWAnimation->drawTo(buffer, x * getTileSize(), y * getTileSize());
        }
          
      }
      
    }
  }
  

  
}


List * Room::getEnemies() {
  return enemies;
}


List * Room::getItems() {
  return items;
}


List * Room::getHelpTiles() {
  return helpTiles;
}


void Room::setNumber(int aNumber) {
  number = aNumber;

}


int Room::getNumber() {
  return number;
}


void Room::setPathMap(Map * aPathMap) {
  pathMap = aPathMap;

}


void Room::addStep(int aStep) {
  path[steps] = aStep;
  steps++;

}


int Room::getSizeOfPath() {
  return steps;
}


int Room::getXOfStepNumber(int aStep) {
  if (path[aStep] == NO_STEP) {
    return NO_STEP;
  }
  return path[aStep] - ((path[aStep] / COLS) * COLS);
}


int Room::getYOfStepNumber(int aStep) {
  if (path[aStep] == NO_STEP) {
    return NO_STEP;
  }
  return path[aStep] / COLS;
}


Map * Room::getPathMap() {
  return pathMap;
}


void Room::setTerrainMap(Map * aTerrainMap) {
  terrainMap = aTerrainMap;

}


bool Room::isSwimmable(int x, int y) {
  if (terrainMap->getValue(x, y) == WATER_TERRAIN) {
    return true;
  }
  return false;
}


bool Room::isWalkable(int x, int y) {
  if (terrainMap->getValue(x, y) == GRASS_TERRAIN) {
    return true;
  }
  return false;
}


bool Room::isJumpable(int x, int y) {
  if (terrainMap->getValue(x, y) == TREE_TERRAIN) {
    return false;
  }
  return true;
}


bool Room::isFlyable(int x, int y) {
  if (terrainMap->getValue(x, y) == TREE_TERRAIN) {
    return false;
  }
  return true;
}


bool Room::isSoarable(int x, int y) {
  // You can soar above any type of terrain.
  return true;
}


void Room::removeExitToPrevRoom() {
  terrainMap->set(entranceFromPrevRoomX, entranceFromPrevRoomY, TREE_TERRAIN);
  this->setExitToPrevRoomX(-1);
  this->setExitToPrevRoomY(-1);

}


int Room::getEntranceFromNextRoomX() {
  return entranceFromNextRoomX;
}


int Room::getEntranceFromNextRoomY() {
  return entranceFromNextRoomY;
}


int Room::getEntranceFromPrevRoomX() {
  return entranceFromPrevRoomX;
}


int Room::getEntranceFromPrevRoomY() {
  return entranceFromPrevRoomY;
}


int Room::getExitToNextRoomX() {
  return exitToNextRoomX;
}


int Room::getExitToNextRoomY() {
  return exitToNextRoomY;
}


int Room::getExitToPrevRoomX() {
  return exitToPrevRoomX;
}


int Room::getExitToPrevRoomY() {
  return exitToPrevRoomY;
}


void Room::setEntranceFromNextRoomX(int newX) {
  entranceFromNextRoomX = newX;

}


void Room::setEntranceFromNextRoomY(int newY) {
  entranceFromNextRoomY = newY;

}


void Room::setEntranceFromPrevRoomX(int newX) {
  entranceFromPrevRoomX = newX;

}


void Room::setEntranceFromPrevRoomY(int newY) {
  entranceFromPrevRoomY = newY;

}


void Room::setExitToNextRoomX(int newX) {
  exitToNextRoomX = newX;

}


void Room::setExitToNextRoomY(int newY) {
  exitToNextRoomY = newY;

}


void Room::setExitToPrevRoomX(int newX) {
  exitToPrevRoomX = newX;

}


void Room::setExitToPrevRoomY(int newY) {
  exitToPrevRoomY = newY;

}




