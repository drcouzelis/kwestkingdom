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
#import "Inhabitable.h"
#import "List.h"
#import "Map.h"
#import "Main.h"
#import "Targetable.h"
#import "Traversable.h"

// Rooms
#import "ForestRoom.h"
#import "SnowRoom.h"
#import "UndergroundRoom.h"

// Enemies
#import "Archer.h"
#import "Giant.h"
#import "Ninja.h"
#import "Chomper.h"


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


@interface RoomFactory : Object {
  
  id<Inhabitable, Targetable, Traversable> world;
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
  Map *pathMap;
  Map *terrainMap;
  List *enemies;
  List *items;
  
  int path[MAX_NUM_OF_STEPS];
  int steps;
  
}

- (Room *) createRoom;

- (Map *) generatePathToEdge;
- (Map *) generateTerrain;
- (List *) generateEnemies;
- (List *) generateItems;

- (BOOL) characterExistsInList: (List *) list atX: (int) x andY: (int) y withWidth: (int) w andHeight: (int) h;

- setWorld: (id<Inhabitable, Targetable, Traversable>) aWorld;
- setType: (int) theType;
- setTerrain: (int) theTerrain;
- setNumber: (int) theNumber;
- setDifficulty: (int) theDifficulty;
- setPathBeginX: (int) thePathBeginX;
- setPathBeginY: (int) thePathBeginY;

- setChanceOfChomper: (int) chance;
- setChanceOfArcher: (int) chance;
- setChanceOfNinja: (int) chance;
- setChanceOfGiant: (int) chance;


@end
