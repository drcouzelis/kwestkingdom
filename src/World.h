#ifndef WORLD_HEADER
#define WORLD_HEADER


#include "anim.h"
#include "utilities.h"

class Character;
class HelpTile;
class Hero;
class Item;
class List;
class Room;
class RoomFactory;
class Snapshot;


class World {
  
public:

  Hero *hero;
  List *rooms;
  
  RoomFactory *roomFactory;
  Room *room;
  
  ANIM heart_anim;
  ANIM heart_empty_anim;
  ANIM help_tile_anim;
  
  int whose_turn;
  
  int difficulty;
  
  Snapshot *prevRoomSnapshot;
  Snapshot *nextRoomSnapshot;
  
  int state;
  
public:

  World();
  virtual ~World();

  virtual void update();
  void draw(IMAGE *canvas);

  FLAG isInhabited(int x, int y);

  FLAG isAttackable(int team, int x, int y);
  void attackFromTeam(int team, int x, int y);
  void shake();

  void addItem(Item *anItem);

  Character *getTarget();

  FLAG isSwimmable(int x, int y);
  FLAG isWalkable(int x, int y);
  FLAG isJumpable(int x, int y);
  FLAG isFlyable(int x, int y);
  FLAG isSoarable(int x, int y);

  void updateRoom();
  void updateItems();
  void updateTurn();
  void updateHero();
  void updateEnemies();

  Room *createNextRoom();
  virtual void changeRooms();

  void drawTerrain(IMAGE *canvas);
  void drawCharacters(IMAGE *canvas);
  void drawUserInterface(IMAGE *canvas);

  int getRoomNumber();
  int getMoney();

  void addHelpTile(HelpTile *aHelpTile);
};


#endif
