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
#ifndef __ROOM_FACTORY_H
#define __ROOM_FACTORY_H


#include "Inhabitable.h"
#include "Map.h"
#include "KwestKingdom.h"
#include "Targetable.h"
#include "Traversable.h"

// Rooms
#include "ForestRoom.h"
#include "SnowRoom.h"
#include "UndergroundRoom.h"

// Enemies
#include "Archer.h"
#include "Giant.h"
#include "Ninja.h"
#include "Chomper.h"


// Types
#define ROOM_FOREST 0
#define ROOM_SNOW 1
#define ROOM_UNDERGROUND 2

// Terrain
#define ROOM_RANDOM 0
#define ROOM_NO_WATER 1
#define ROOM_NO_TREES 2
#define ROOM_DENSE_FOREST 3 // All trees and no water.
// These aren't very good yet...
#define ROOM_NO_WATER_AND_NO_TREES 4
#define ROOM_SWAMP 5 // Lots of water and a few trees.
#define ROOM_LAKE 6 // All water and no trees.

// Number of enemies
#define DEFAULT_CHANCE_OF_CHOMPER 9
#define DEFAULT_CHANCE_OF_ARCHER 6
#define DEFAULT_CHANCE_OF_NINJA 6
#define DEFAULT_CHANCE_OF_GIANT 3


class World;


class RoomFactory
{
public:
  RoomFactory();
  
  virtual Room* createRoom();
  
  virtual Map* generatePathToEdge();
  virtual Map* generateTerrain();
  virtual std::vector<Enemy*>* generateEnemies();
  virtual std::vector<Collectable*>* generateItems();

  virtual bool characterExists(std::vector<Enemy*>* list, int x, int y, int w, int h);

  virtual void setWorld(World* world);
  virtual void setType(int type);
  virtual void setTerrain(int terrain);
  virtual void setNumber(int number);
  virtual void setDifficulty(int difficulty);
  virtual void setPathBeginX(int pathBeginX);
  virtual void setPathBeginY(int pathBeginY);

  virtual void setChanceOfChomper(int chance);
  virtual void setChanceOfArcher(int chance);
  virtual void setChanceOfNinja(int chance);
  virtual void setChanceOfGiant(int chance);
  
private:
  World* world;
  int type;
  int terrain;
  int number;
  int difficulty;
  int pathStartX;
  int pathStartY;
  
  int chanceOfChomper;
  int chanceOfNinja;
  int chanceOfArcher;
  int chanceOfGiant;
  
  // These are created internally.
  int pathStopX;
  int pathStopY;
  Map* pathMap;
  Map* terrainMap;
  std::vector<Enemy*>* enemies;
  std::vector<Collectable*>* items;
  
  int path[MAX_NUM_OF_STEPS];
  int steps;
};


#endif // __ROOM_FACTORY_H
