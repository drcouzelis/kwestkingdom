#ifndef WORLD_HEADER
#define WORLD_HEADER


#include <allegro.h>

class Animation;
class Character;
class HelpTile;
class Hero;
class Item;
class List;
class Room;
class RoomFactory;
class Snapshot;


class World {
  
protected:

  Hero *hero;
  List *rooms;
  
  RoomFactory *roomFactory;
  Room *room;
  
  Animation *heartAnimation;
  Animation *heartEmptyAnimation;
  Animation *helpTileAnimation;
  
  Character *currentCharacter;
  
  int difficulty;
  
  Snapshot *prevRoomSnapshot;
  Snapshot *nextRoomSnapshot;
  
  int state;
  
public:

  World();
  virtual ~World();

  void update();
  void draw(BITMAP *buffer);

  bool isInhabited(int x, int y);

  bool isAttackable(int team, int x, int y);
  void attackFromTeam(int team, int x, int y);
  void shake();

  void addItem(Item *anItem);

  Character *getTarget();

  bool isSwimmable(int x, int y);
  bool isWalkable(int x, int y);
  bool isJumpable(int x, int y);
  bool isFlyable(int x, int y);
  bool isSoarable(int x, int y);

  void updateRoom();
  void updateItems();
  void updateTurn();
  void updateHero();
  void updateEnemies();

  Room *createNextRoom();
  void changeRooms();

  void drawTerrain(BITMAP *buffer);
  void drawCharacters(BITMAP *buffer);
  void drawUserInterface(BITMAP *buffer);

  int getRoomNumber();
  int getMoney();

  void addHelpTile(HelpTile *aHelpTile);
};


#endif
