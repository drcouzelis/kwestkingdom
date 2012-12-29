#ifndef ROOMFACTORY_HEADER
#define ROOMFACTORY_HEADER


#include "Room.h"

class List;
class World;


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


class RoomFactory {
  
  World *world;
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
  
  int path[MAX_TILES];
  int steps;
  
public:

  RoomFactory();

  Room *createRoom();

  void generatePath(Room *room);
  void generateTerrain(Room *room);
  void generateEnemies(Room *room);
  void generateItems(Room *room);

  bool characterExists(Room *room, int x, int y, int w, int h);

  void setWorld(World *aWorld);
  void setType(int theType);
  void setTerrain(int theTerrain);
  void setNumber(int theNumber);
  void setDifficulty(int theDifficulty);
  void setPathBeginX(int thePathBeginX);
  void setPathBeginY(int thePathBeginY);

  void setChanceOfChomper(int chance);
  void setChanceOfArcher(int chance);
  void setChanceOfNinja(int chance);
  void setChanceOfGiant(int chance);
};


#endif
