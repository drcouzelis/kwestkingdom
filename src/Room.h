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
#ifndef __ROOM_H
#define __ROOM_H


#include <vector>

#include "Animation.h"
#include "Drawable.h"
#include "HelpTile.h"
#include "Map.h"
#include "Traversable.h"
#include "Updatable.h"


class Enemy;
class Collectable;


typedef enum {
  GRASS_TERRAIN,
  TREE_TERRAIN,
  WATER_TERRAIN,
  ENTRANCE_TERRAIN,
  EXIT_TERRAIN
} TERRAIN;


#define MAX_NUM_OF_STEPS (ROWS * COLS)
#define NO_STEP -1


class Room : public virtual Drawable, public virtual Traversable, public virtual Updatable
{
public:
  
  Room();
  ~Room();
  
  virtual void draw(BITMAP* buffer); // Drawable
  
  virtual bool isSwimmable(int x, int y) = 0; // Traversable
  virtual bool isWalkable(int x, int y) = 0;  // Traversable
  virtual bool isJumpable(int x, int y) = 0;  // Traversable
  virtual bool isFlyable(int x, int y) = 0;   // Traversable
  virtual bool isSoarable(int x, int y) = 0;  // Traversable
  
  virtual void update(); // Updatable
  
  virtual void setPathMap(Map* map);
  virtual void setTerrainMap(Map* map);
  
  virtual void addStep(int step);
  virtual int  getSizeOfPath();
  virtual int  getXOfStepNumber(int step);
  virtual int  getYOfStepNumber(int step);
  
  virtual std::vector<Enemy*>*       retrieveEnemies();
  virtual std::vector<Collectable*>* retrieveItems();
  virtual std::vector<HelpTile*>*    retrieveHelpTiles();
  
  virtual void storeEnemies(std::vector<Enemy*>* enemies);
  virtual void storeItems(std::vector<Collectable*>* list);
  virtual void storeHelpTiles(std::vector<HelpTile*>* list);
  
  virtual int getEntranceFromNextRoomX();
  virtual int getEntranceFromNextRoomY();
  virtual int getEntranceFromPrevRoomX();
  virtual int getEntranceFromPrevRoomY();
  virtual int getExitToNextRoomX();
  virtual int getExitToNextRoomY();
  virtual int getExitToPrevRoomX();
  virtual int getExitToPrevRoomY();
  
  virtual void setEntranceFromNextRoomX(int x);
  virtual void setEntranceFromNextRoomY(int y);
  virtual void setEntranceFromPrevRoomX(int x);
  virtual void setEntranceFromPrevRoomY(int y);
  virtual void setExitToNextRoomX(int x);
  virtual void setExitToNextRoomY(int y);
  virtual void setExitToPrevRoomX(int x);
  virtual void setExitToPrevRoomY(int y);
  
  virtual void setNumber(int number);
  virtual int  getNumber();
  
  virtual void removeExitToPrevRoom();
  
  virtual Map* getPathMap();
  
private:
  // Add a terrain map, item map, character map...
  Map* terrainMap;
  Map* pathMap;
  
  std::vector<Enemy*>* enemyStorage;
  std::vector<Collectable*>* itemStorage;
  std::vector<HelpTile*>* helpTileStorage;
  
  int entranceFromNextRoomX;
  int entranceFromNextRoomY;
  int entranceFromPrevRoomX;
  int entranceFromPrevRoomY;
  
  int exitToNextRoomX;
  int exitToNextRoomY;
  int exitToPrevRoomX;
  int exitToPrevRoomY;
  
  int number;
  
  Animation* grassAnimation;
  Animation* pathAnimation;
  Animation* mountainAnimation;
  Animation* waterAnimation;
  Animation* shoreNorthAnimation;
  Animation* shoreSouthAnimation;
  Animation* shoreEastAnimation;
  Animation* shoreWestAnimation;
  Animation* shoreInsideNEAnimation;
  Animation* shoreInsideNWAnimation;
  Animation* shoreInsideSEAnimation;
  Animation* shoreInsideSWAnimation;
  Animation* shoreOutsideNEAnimation;
  Animation* shoreOutsideNWAnimation;
  Animation* shoreOutsideSEAnimation;
  Animation* shoreOutsideSWAnimation;
  
  int path[MAX_NUM_OF_STEPS];
  int steps;
};


#endif // __ROOM_H
