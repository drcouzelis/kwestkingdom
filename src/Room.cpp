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
#include "KwestKingdom.h"
#include "Room.h"
#include "Screen.h"


Room::Room()
  : terrainMap(NULL),
    pathMap(NULL),
    enemyStorage(NULL),
    itemStorage(NULL),
    helpTileStorage(new std::vector<HelpTile*>),
    entranceFromNextRoomX(0),
    entranceFromNextRoomY(0),
    entranceFromPrevRoomX(0),
    entranceFromPrevRoomY(0),
    exitToNextRoomX(0),
    exitToNextRoomY(0),
    exitToPrevRoomX(0),
    exitToPrevRoomY(0),
    number(0),
    grassAnimation(NULL),
    pathAnimation(NULL),
    mountainAnimation(NULL),
    waterAnimation(NULL),
    shoreNorthAnimation(NULL),
    shoreSouthAnimation(NULL),
    shoreEastAnimation(NULL),
    shoreWestAnimation(NULL),
    shoreInsideNEAnimation(NULL),
    shoreInsideNWAnimation(NULL),
    shoreInsideSEAnimation(NULL),
    shoreInsideSWAnimation(NULL),
    shoreOutsideNEAnimation(NULL),
    shoreOutsideNWAnimation(NULL),
    shoreOutsideSEAnimation(NULL),
    shoreOutsideSWAnimation(NULL),
    steps(0)
{
  for (int i = 0; i < MAX_NUM_OF_STEPS; i++) {
    path[i] = NO_STEP;
  }
}


Room::~Room()
{
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
  
  delete enemyStorage;
  delete itemStorage;
  delete helpTileStorage;
  
  delete pathMap;
  delete terrainMap;
}


void
Room::update()
{
  grassAnimation->animate();
  pathAnimation->animate();
  mountainAnimation->animate();
  waterAnimation->animate();
  shoreNorthAnimation->animate();
  shoreSouthAnimation->animate();
  shoreEastAnimation->animate();
  shoreWestAnimation->animate();
  shoreInsideNEAnimation->animate();
  shoreInsideNWAnimation->animate();
  shoreInsideSEAnimation->animate();
  shoreInsideSWAnimation->animate();
  shoreOutsideNEAnimation->animate();
  shoreOutsideNWAnimation->animate();
  shoreOutsideSEAnimation->animate();
  shoreOutsideSWAnimation->animate();
}


void
Room::draw(BITMAP* buffer)
{
  for (int y = 0; y < ROWS; y++) {
    for (int x = 0; x < COLS; x++) {
      
      //if ([pathMap getValueAtX: x andY: y] == YES) { // Draw the path
        //[pathAnimation->draw(buffer, x * getTileSize(), y * getTileSize());
      //} else
      if (terrainMap->getValue(x, y) == GRASS_TERRAIN) {
        grassAnimation->draw(buffer, x * getTileSize(), y * getTileSize());
      } else if (terrainMap->getValue(x, y) == TREE_TERRAIN) {
        mountainAnimation->draw(buffer, x * getTileSize(), y * getTileSize());
      } else if (terrainMap->getValue(x, y) == WATER_TERRAIN) {
        
        waterAnimation->draw(buffer, x * getTileSize(), y * getTileSize());
        
        // Add the shore borders
        if (terrainMap->getValue(x, y - 1) != WATER_TERRAIN) { // North
          shoreNorthAnimation->draw(buffer, x * getTileSize(), y * getTileSize());
        }
        if (terrainMap->getValue(x, y + 1) != WATER_TERRAIN) { // South
          shoreSouthAnimation->draw(buffer, x * getTileSize(), y * getTileSize());
        }
        if (terrainMap->getValue(x + 1, y) != WATER_TERRAIN) { // East
          shoreEastAnimation->draw(buffer, x * getTileSize(), y * getTileSize());
        }
        if (terrainMap->getValue(x - 1, y) != WATER_TERRAIN) { // West
          shoreWestAnimation->draw(buffer, x * getTileSize(), y * getTileSize());
        }
          
      }
      
    }
  }
  
  // Add the shore corners
  for (int y = 0; y < ROWS; y++) {
    for (int x = 0; x < COLS; x++) {
      
      if (terrainMap->getValue(x, y) == WATER_TERRAIN) {
        
        // Add the shore inside corners
        if (
          terrainMap->getValue(x, y - 1) != WATER_TERRAIN &&
          terrainMap->getValue(x + 1, y) != WATER_TERRAIN
        ) { // North East
          shoreInsideNEAnimation->draw(buffer, x * getTileSize(), y * getTileSize());
        }
        if (
          terrainMap->getValue(x, y + 1) != WATER_TERRAIN &&
          terrainMap->getValue(x + 1, y) != WATER_TERRAIN
        ) { // South East
          shoreInsideSEAnimation->draw(buffer, x * getTileSize(), y * getTileSize());
        }
        if (
          terrainMap->getValue(x, y - 1) != WATER_TERRAIN &&
          terrainMap->getValue(x - 1, y) != WATER_TERRAIN
        ) { // North West
          shoreInsideNWAnimation->draw(buffer, x * getTileSize(), y * getTileSize());
        }
        if (
          terrainMap->getValue(x, y + 1) != WATER_TERRAIN &&
          terrainMap->getValue(x - 1, y) != WATER_TERRAIN
        ) { // South West
          shoreInsideSWAnimation->draw(buffer, x * getTileSize(), y * getTileSize());
        }
          
        // Add the shore outside corners.
        if (
          terrainMap->getValue(x, y - 1) == WATER_TERRAIN &&
          terrainMap->getValue(x + 1, y) == WATER_TERRAIN &&
          terrainMap->getValue(x + 1, y - 1) != WATER_TERRAIN
        ) { // North East
          shoreOutsideNEAnimation->draw(buffer, x * getTileSize(), y * getTileSize());
        }
        if (
          terrainMap->getValue(x, y + 1) == WATER_TERRAIN &&
          terrainMap->getValue(x + 1, y) == WATER_TERRAIN &&
          terrainMap->getValue(x + 1, y + 1) != WATER_TERRAIN
        ) { // South East
          shoreOutsideSEAnimation->draw(buffer, x * getTileSize(), y * getTileSize());
        }
        if (
          terrainMap->getValue(x, y - 1) == WATER_TERRAIN &&
          terrainMap->getValue(x - 1, y) == WATER_TERRAIN &&
          terrainMap->getValue(x - 1, y - 1) != WATER_TERRAIN
        ) { // North West
          shoreOutsideNWAnimation->draw(buffer, x * getTileSize(), y * getTileSize());
        }
        if (
          terrainMap->getValue(x, y + 1) == WATER_TERRAIN &&
          terrainMap->getValue(x - 1, y) == WATER_TERRAIN &&
          terrainMap->getValue(x - 1, y + 1) != WATER_TERRAIN
        ) { // South West
          shoreOutsideSWAnimation->draw(buffer, x * getTileSize(), y * getTileSize());
        }
          
      }
      
    }
  }
}


std::vector<Enemy*>*
Room::retrieveEnemies()
{
  std::vector<Enemy*>* list = enemyStorage;
  enemyStorage = NULL;
  return list;
}


void
Room::storeEnemies(std::vector<Enemy*>* list)
{
  delete enemyStorage;
  enemyStorage = list;
}


std::vector<Collectable*>*
Room::retrieveItems()
{
  std::vector<Collectable*>* list = itemStorage;
  itemStorage = NULL;
  return list;
}


void
Room::storeItems(std::vector<Collectable*>* list)
{
  delete itemStorage;
  itemStorage = list;
}


std::vector<HelpTile*>*
Room::retrieveHelpTiles() {
  std::vector<HelpTile*>* list = helpTileStorage;
  helpTileStorage = NULL;
  return list;
}


void
Room::storeHelpTiles(std::vector<HelpTile*>* list)
{
  delete helpTileStorage;
  helpTileStorage = list;
}


void
Room::setNumber(int number)
{
  this->number = number;
}


int
Room::getNumber()
{
  return number;
}


void
Room::setPathMap(Map* map)
{
  pathMap = map;
}


void
Room::addStep(int step)
{
  path[steps] = step;
  steps++;
}


int
Room::getSizeOfPath()
{
  return steps;
}


int
Room::getXOfStepNumber(int step)
{
  if (path[step] == NO_STEP) {
    return NO_STEP;
  }
  return path[step] - ((path[step] / COLS) * COLS);
}


int
Room::getYOfStepNumber(int step)
{
  if (path[step] == NO_STEP) {
    return NO_STEP;
  }
  return path[step] / COLS;
}


Map*
Room::getPathMap()
{
  return pathMap;
}


void
Room::setTerrainMap(Map* map)
{
  terrainMap = map;
}


bool
Room::isSwimmable(int x, int y)
{
  if (terrainMap->getValue(x, y) == WATER_TERRAIN) {
    return true;
  }
  return false;
}


bool
Room::isWalkable(int x, int y)
{
  if (terrainMap->getValue(x, y) == GRASS_TERRAIN) {
    return true;
  }
  return false;
}


bool
Room::isJumpable(int x, int y)
{
  if (terrainMap->getValue(x, y) == TREE_TERRAIN) {
    return false;
  }
  return true;
}


bool
Room::isFlyable(int x, int y)
{
  if (terrainMap->getValue(x, y) == TREE_TERRAIN) {
    return false;
  }
  return true;
}


bool
Room::isSoarable(int x, int y)
{
  // You can soar above any type of terrain.
  return true;
}


void
Room::removeExitToPrevRoom()
{
  terrainMap->set(entranceFromPrevRoomX, entranceFromPrevRoomY, TREE_TERRAIN);
  setExitToPrevRoomX(-1);
  setExitToPrevRoomY(-1);
}


int
Room::getEntranceFromNextRoomX()
{
  return entranceFromNextRoomX;
}


int
Room::getEntranceFromNextRoomY()
{
  return entranceFromNextRoomY;
}


int
Room::getEntranceFromPrevRoomX()
{
  return entranceFromPrevRoomX;
}


int
Room::getEntranceFromPrevRoomY()
{
  return entranceFromPrevRoomY;
}


int
Room::getExitToNextRoomX()
{
  return exitToNextRoomX;
}


int
Room::getExitToNextRoomY()
{
  return exitToNextRoomY;
}


int
Room::getExitToPrevRoomX()
{
  return exitToPrevRoomX;
}


int
Room::getExitToPrevRoomY()
{
  return exitToPrevRoomY;
}


void
Room::setEntranceFromNextRoomX(int x)
{
  entranceFromNextRoomX = x;
}


void
Room::setEntranceFromNextRoomY(int y)
{
  entranceFromNextRoomY = y;
}


void
Room::setEntranceFromPrevRoomX(int x)
{
  entranceFromPrevRoomX = x;
}


void
Room::setEntranceFromPrevRoomY(int y)
{
  entranceFromPrevRoomY = y;
}


void
Room::setExitToNextRoomX(int x)
{
  exitToNextRoomX = x;
}


void
Room::setExitToNextRoomY(int y)
{
  exitToNextRoomY = y;
}


void
Room::setExitToPrevRoomX(int x)
{
  exitToPrevRoomX = x;
}


void
Room::setExitToPrevRoomY(int y)
{
  exitToPrevRoomY = y;
}
