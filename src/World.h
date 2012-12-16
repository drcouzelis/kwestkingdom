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
  List *enemies;
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

  virtual void update();
  virtual void draw(BITMAP *buffer);

  virtual bool isInhabited(int x, int y);

  virtual bool isAttackable(int team, int x, int y);
  virtual void attackFromTeam(int team, int x, int y);
  virtual void shake();

  virtual void addItem(Item *anItem);

  virtual Character *getTarget();

  virtual bool isSwimmable(int x, int y);
  virtual bool isWalkable(int x, int y);
  virtual bool isJumpable(int x, int y);
  virtual bool isFlyable(int x, int y);
  virtual bool isSoarable(int x, int y);

  virtual void updateRoom();
  virtual void updateItems();
  virtual void updateTurn();
  virtual void updateHero();
  virtual void updateEnemies();

  virtual Room *createNextRoom();
  virtual void changeRooms();

  virtual void drawTerrain(BITMAP *buffer);
  virtual void drawCharacters(BITMAP *buffer);
  virtual void drawUserInterface(BITMAP *buffer);

  virtual int getRoomNumber();
  virtual int getMoney();

  virtual void addHelpTile(HelpTile *aHelpTile);
};


#endif
