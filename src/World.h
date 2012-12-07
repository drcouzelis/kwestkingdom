#ifndef WORLD_HEADER
#define WORLD_HEADER


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
  
  Hero *hero;
  List *enemies;
  List *rooms;
  
  RoomFactory *roomFactory;
  Room *room;
  
  List *items;
  List *helpTiles;
  
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
  ~World();

  virtual void update();
  virtual void draw(BITMAP *buffer);

  virtual bool isInhabited(int x, int y);

  virtual bool isAttackable(int team, int x, int y);
  virtual void attackFromTeam(int team, int x, int y);
  virtual void shake();

  virtual void addCharacter(Character *aCharacter);
  virtual void addItem(Item *anItem);

  virtual Character *getTarget();

  virtual bool isSwimmable(int x, int y);
  virtual bool isWalkable(int x, int y);
  virtual bool isJumpable(int x, int y);
  virtual bool isFlyable(int x, int y);
  virtual bool isSoarable(int x, int y);

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
