#include <stdio.h>

#include "Animation.h"
#include "Enemy.h"
#include "HelpTile.h"
#include "Hero.h"
#include "Item.h"
#include "KwestKingdom.h"
#include "List.h"
#include "Resources.h"
#include "RoomFactory.h"
#include "Screen.h"
#include "Snapshot.h"
#include "Text.h"
#include "World.h"


typedef enum {
  WORLD_UPDATE_STATE,
  WORLD_ROOM_TRANSITION_STATE,
  WORLD_SHAKING_STATE
} WORLD_STATE;


World::World() {
  
  difficulty = 0;
  
  hero = new Hero();
  hero->setMaxHealth(MAX_HERO_HEALTH);
  hero->setHealth(MAX_HERO_HEALTH);
  hero->setWorld(this);
  hero->setX(COLS / 2 - 1);
  hero->setY(ROWS - 2);
  
  // Create the starting room.
  roomFactory = new RoomFactory();
  roomFactory->setWorld(this);
  roomFactory->setType(ROOM_FOREST);
  roomFactory->setTerrain(ROOM_NO_WATER);
  roomFactory->setNumber(1);
  roomFactory->setDifficulty(difficulty);
  roomFactory->setPathBeginX(hero->getX());
  roomFactory->setPathBeginY(hero->getY());
  
  room = NULL;
  room = this->createNextRoom();
  room->setExitToPrevRoomX(-1); // Remove the entrance to the first room.
  room->setExitToPrevRoomY(-1);
  
  rooms = new List();
  rooms->append(room);
  
  items = new List();
  helpTiles = new List();
  
  heartAnimation = new Animation();
  heartAnimation->addFrame(getImage(IMAGES_HEART));
  heartEmptyAnimation = new Animation();
  heartEmptyAnimation->addFrame(getImage(IMAGES_EMPTYHEART));
  helpTileAnimation = new Animation();
  helpTileAnimation->addFrame(getImage(IMAGES_HELP));
  
  prevRoomSnapshot = new Snapshot();
  nextRoomSnapshot = new Snapshot();
  
  currentCharacter = NULL;
  
  state = WORLD_UPDATE_STATE;
}


World::~World() {
  delete rooms;
  delete roomFactory;
  delete hero;
  delete items;
  delete helpTiles;
  delete heartAnimation;
  delete heartEmptyAnimation;
  delete helpTileAnimation;
  delete prevRoomSnapshot;
  delete nextRoomSnapshot;
}


void World::updateRoom() {
  room->update();
}


void World::updateItems() {
  
  Item *item;
  //Enemy *enemy;
  int x;
  int y;
  
  items->iterate();
  while ((item = (Item *)items->getNext()) != NULL) {
    
    item->update();
    
    // For the entire size of the hero
    // see if he is standing on an item
    for (x = 0; x < hero->getWidth(); x++) {
      for (y = 0; y < hero->getHeight(); y++) {
        
        // Hero is standing on the item
        if (item->getX() == hero->getX() + x && item->getY() == hero->getY() + y) {
          item->collectedBy(hero);
          items->remove(item);
          return;
        }
        
      }
    }
  }
    
  /*
  // Enemies can not collect items.
  List *enemies = room->getEnemies();
  enemies->iterate();
  while ((enemy = (Enemy *)enemies->getNext()) != NULL) {
    
    // For the entire size of the hero
    // see if he is standing on an item
    for (x = 0; x < enemy->getWidth(); x++) {
      for (y = 0; y < enemy->getHeight(); y++) {
        
        // If an enemy is standing on the item
        if (item->getX() == enemy->getX() + x && item->getY() == enemy->getY() + y) {
          item->collectedBy(enemy);
          items->remove(item);
          return;
        }
        
      }
    }
    
  }
  */
}


void World::updateTurn() {
  
  List *enemies = room->getEnemies();
  int index;
  
  // Determine whose turn it is next and tell them to go.
  if (currentCharacter == NULL || currentCharacter->waiting()) {
    
    if (currentCharacter == NULL) {
      currentCharacter = hero;
    } else if (currentCharacter == hero) {
      currentCharacter = (Character *)enemies->getIndex(0);
      if (currentCharacter == NULL) {
        currentCharacter = hero;
      }
    } else {
      index = enemies->findIndex(currentCharacter);
      if (index >= 0) {
        currentCharacter = (Character *)enemies->getIndex(index + 1);
      } else {
        currentCharacter = NULL;
      }
      if (currentCharacter == NULL) {
        currentCharacter = hero;
      }
    }
    
    currentCharacter->go();
    
  }
}


void World::updateHero() {
  
  List *enemies = room->getEnemies();

  hero->update();
  
  // If the hero is at an exit...
  if (
    (hero->getX() == room->getExitToNextRoomX() && hero->getY() == room->getExitToNextRoomY()) ||
    (hero->getX() == room->getExitToPrevRoomX() && hero->getY() == room->getExitToPrevRoomY())
  ) {
    
    // This prevents enemies from moving around during a change of rooms.
    if (hero->waiting()) {
      hero->go();
    }
    
    if (!hero->moving()) {
      this->changeRooms();
      currentCharacter = hero;
    }
    
  }
  
  if (hero->isDead()) {
    game_over();
  }
}


void World::updateEnemies() {
  
  List *enemies = room->getEnemies();
  Enemy *enemy;
  
  // Update the enemies and remove any that are dead.
  enemies->iterate();
  while ((enemy = (Enemy *)enemies->getNext()) != NULL) {
    
    enemy->update();
    
    if (enemy->isDead()) {
      enemy->dropItem();
      enemies->remove(enemy);
    }
    
  }
}


void World::update() {
  
  switch (state) {
  
  case WORLD_UPDATE_STATE:
    this->updateRoom();
    this->updateItems();
    this->updateTurn();
    this->updateHero();
    this->updateEnemies();
    break;
    
  case WORLD_ROOM_TRANSITION_STATE:
    prevRoomSnapshot->update();
    nextRoomSnapshot->update();
    if (!nextRoomSnapshot->moving()) {
      state = WORLD_UPDATE_STATE;
    }
    break;
  
  case WORLD_SHAKING_STATE:
    this->updateRoom();
    this->updateItems();
    this->updateTurn();
    this->updateHero();
    this->updateEnemies();
    prevRoomSnapshot->update();
    if (!prevRoomSnapshot->moving()) {
      if (prevRoomSnapshot->getY() == 10) {
        prevRoomSnapshot->moveY(-8);
      } else if (prevRoomSnapshot->getY() == -8) {
        prevRoomSnapshot->moveY(6);
      } else if (prevRoomSnapshot->getY() == 6) {
        prevRoomSnapshot->moveY(-4);
      } else if (prevRoomSnapshot->getY() == -4) {
        prevRoomSnapshot->moveY(2);
      } else if (prevRoomSnapshot->getY() == 2) {
        prevRoomSnapshot->moveY(0);
      } else if (prevRoomSnapshot->getY() == 0) {
        state = WORLD_UPDATE_STATE;
      }
    }
    break;
  
  }
}


void World::addItem(Item *anItem) {
  if (anItem != NULL) {
    items->append(anItem);
  }
}


void World::addHelpTile(HelpTile *aHelpTile) {
  if (aHelpTile != NULL) {
    helpTiles->append(aHelpTile);
  }
}


Character * World::getTarget() {
  return hero;
}


bool World::isAttackable(int team, int x, int y) {
  
  List *enemies = room->getEnemies();
  Enemy *enemy;
  int i, j;
  int m, n;
  
  int w, h;
  
  w = 1;
  h = 1;
  
  for (i = 0; i < w; i++) {
    for (j = 0; j < h; j++) {
      
      for (m = 0; m < hero->getWidth(); m++) {
        for (n = 0; n < hero->getHeight(); n++) {
          
          if (team != hero->getTeam() && x + i == hero->getX() + m && y + j == hero->getY() + n) {
            return true;
          }
          
        }
      }
      
      enemies->iterate();
      while ((enemy = (Enemy *)enemies->getNext()) != NULL) {
        for (m = 0; m < enemy->getWidth(); m++) {
          for (n = 0; n < enemy->getHeight(); n++) {
            if (team != enemy->getTeam() && x + i == enemy->getX() + m && y + j == enemy->getY() + n) {
              return true;
            }
          }
        }
      }
      
    }
  }
  
  return false;
}


void World::attackFromTeam(int team, int x, int y) {
  
  List *enemies = room->getEnemies();
  Enemy *enemy;
  int m, n;
  
  for (m = 0; m < hero->getWidth(); m++) {
    for (n = 0; n < hero->getHeight(); n++) {
      if (team != hero->getTeam() && x == hero->getX() + m && y == hero->getY() + n) {
        hero->hurt();
      }
    }
  }
  
  enemies->iterate();
  while ((enemy = (Enemy *)enemies->getNext()) != NULL) {
    for (m = 0; m < enemy->getWidth(); m++) {
      for (n = 0; n < enemy->getHeight(); n++) {
        if (team != enemy->getTeam() && x == enemy->getX() + m && y == enemy->getY() + n) {
          enemy->hurt();
        }
      }
    }
  }
}


bool World::isSwimmable(int x, int y) {
  return room->isSwimmable(x, y);
}


bool World::isWalkable(int x, int y) {
  return room->isWalkable(x, y);
}


bool World::isJumpable(int x, int y) {
  return room->isJumpable(x, y);
}


bool World::isFlyable(int x, int y) {
  return room->isFlyable(x, y);
}


bool World::isSoarable(int x, int y) {
  return room->isSoarable(x, y);
}


bool World::isInhabited(int x, int y) {
  
  List *enemies = room->getEnemies();
  Enemy *enemy;
  int i, j;
  int m, n;
  
  int w, h;
  
  w = 1;
  h = 1;
  
  for (i = 0; i < w; i++) {
    for (j = 0; j < h; j++) {
      
      for (m = 0; m < hero->getWidth(); m++) {
        for (n = 0; n < hero->getHeight(); n++) {
          
          if (x + i == hero->getX() + m && y + j == hero->getY() + n) {
            return true;
          }
          
        }
      }
      
      enemies->iterate();
      while ((enemy = (Enemy *)enemies->getNext()) != NULL) {
        for (m = 0; m < enemy->getWidth(); m++) {
          for (n = 0; n < enemy->getHeight(); n++) {
            if (x + i == enemy->getX() + m && y + j == enemy->getY() + n) {
              return true;
            }
          }
        }
      }
      
    }
  }
  
  return false;
}


int World::getRoomNumber() {
  return room->getNumber();
}


int World::getMoney() {
  return hero->getMoney();
}


void World::shake() {
  state = WORLD_SHAKING_STATE;
  prevRoomSnapshot->setX(0);
  prevRoomSnapshot->setY(0);
  prevRoomSnapshot->moveY(10);
  prevRoomSnapshot->setSpeed(getWindowHeight());
  this->drawTerrain(prevRoomSnapshot->getCanvas());
  this->drawCharacters(prevRoomSnapshot->getCanvas());
}


Room * World::createNextRoom() {
  
  int number;
  
  if (room != NULL) {
    number = room->getNumber() + 1;
  } else {
    number = 1;
  }
  
  if (number % 20 == 0) {
    roomFactory->setType(ROOM_UNDERGROUND);
    roomFactory->setTerrain(ROOM_NO_WATER);
    roomFactory->setDifficulty(0);
  } else if (number / 20 % 2 == 0) {
    roomFactory->setType(ROOM_FOREST);
    roomFactory->setTerrain(ROOM_RANDOM);
    roomFactory->setDifficulty(difficulty);
  } else {
    roomFactory->setType(ROOM_SNOW);
    roomFactory->setTerrain(ROOM_RANDOM);
    roomFactory->setDifficulty(difficulty);
  }
  
  roomFactory->setNumber(number);
  
  return roomFactory->createRoom();
}


void World::changeRooms() {
  
  Room *nextRoom;
  Room *firstRoom;
  int entranceX;
  int entranceY;
  
  // Prepare the room transition.
  if (hero->getX() < 0) {
    prevRoomSnapshot->setX(0);
    prevRoomSnapshot->setY(0);
    prevRoomSnapshot->moveX(getWindowWidth());
    prevRoomSnapshot->setSpeed(getWindowWidth());
    nextRoomSnapshot->setX(-getWindowWidth());
    nextRoomSnapshot->setY(0);
    nextRoomSnapshot->moveX(0);
    nextRoomSnapshot->setSpeed(getWindowWidth());
  } else if (hero->getX() > COLS - 1) {
    prevRoomSnapshot->setX(0);
    prevRoomSnapshot->setY(0);
    prevRoomSnapshot->moveX(-getWindowWidth());
    prevRoomSnapshot->setSpeed(getWindowWidth());
    nextRoomSnapshot->setX(getWindowWidth());
    nextRoomSnapshot->setY(0);
    nextRoomSnapshot->moveX(0);
    nextRoomSnapshot->setSpeed(getWindowWidth());
  } else if (hero->getY() < 0) {
    prevRoomSnapshot->setX(0);
    prevRoomSnapshot->setY(0);
    prevRoomSnapshot->moveY(getWindowHeight());
    prevRoomSnapshot->setSpeed(getWindowHeight());
    nextRoomSnapshot->setX(0);
    nextRoomSnapshot->setY(-getWindowHeight());
    nextRoomSnapshot->moveY(0);
    nextRoomSnapshot->setSpeed(getWindowHeight());
  } else if (hero->getY() > ROWS - 1) {
    prevRoomSnapshot->setX(0);
    prevRoomSnapshot->setY(0);
    prevRoomSnapshot->moveY(-getWindowHeight());
    prevRoomSnapshot->setSpeed(getWindowHeight());
    nextRoomSnapshot->setX(0);
    nextRoomSnapshot->setY(getWindowHeight());
    nextRoomSnapshot->moveY(0);
    nextRoomSnapshot->setSpeed(getWindowHeight());
  } else {
    prevRoomSnapshot->setX(0);
    prevRoomSnapshot->setY(0);
    nextRoomSnapshot->setX(0);
    nextRoomSnapshot->setY(0);
  }
  
  this->drawTerrain(prevRoomSnapshot->getCanvas());
  this->drawCharacters(prevRoomSnapshot->getCanvas());
  
  // If the hero is at the exit that leads to the next room...
  if (hero->getX() == room->getExitToNextRoomX() && hero->getY() == room->getExitToNextRoomY()) {
    
    room->storeItems(items);
    room->storeHelpTiles(helpTiles);
    
    nextRoom = (Room *)rooms->getIndex(rooms->findIndex(room) + 1);
    
    // Create the next room here, if necessary.
    if (nextRoom != NULL) {
      
      room = nextRoom;
      
    } else {
      
      entranceX = ((Room *)rooms->getTail())->getExitToNextRoomX();
      entranceY = ((Room *)rooms->getTail())->getExitToNextRoomY();
      
      // Bound the entrance.
      if (entranceX < 0) {
        entranceX = 0;
      } else if (entranceX > COLS - 1) {
        entranceX = COLS - 1;
      }
      if (entranceY < 0) {
        entranceY = 0;
      } else if (entranceY > ROWS - 1) {
        entranceY = ROWS - 1;
      }
      
      // Flip the side of the screen that the entrance is on.
      if (entranceX == 0) {
        entranceX = COLS - 1;
      } else if (entranceX == COLS - 1) {
        entranceX = 0;
      }
      if (entranceY == 0) {
        entranceY = ROWS - 1;
      } else if (entranceY == ROWS - 1) {
        entranceY = 0;
      }
      
      roomFactory->setPathBeginX(entranceX);
      roomFactory->setPathBeginY(entranceY);
      nextRoom = this->createNextRoom();
      rooms->append(nextRoom);
      
      room = nextRoom;
      
      // Delete the oldest room.
      if (rooms->getSize() > 2) {
        firstRoom = (Room *)rooms->getHead();
        rooms->remove(rooms->getHead());
        delete firstRoom;
        firstRoom = (Room *)rooms->getHead();
        firstRoom->removeExitToPrevRoom();
      }
      
    }
    
    hero->setX(room->getEntranceFromPrevRoomX());
    hero->setY(room->getEntranceFromPrevRoomY());
    
    items = room->retrieveItems();
    helpTiles = room->retrieveHelpTiles();
    
  } else if (hero->getX() == room->getExitToPrevRoomX() && hero->getY() == room->getExitToPrevRoomY()) {
    
    room->storeItems(items);
    room->storeHelpTiles(helpTiles);
    
    // Go to the previous room.
    room = (Room *)rooms->getIndex(rooms->findIndex(room) - 1);
    hero->setX(room->getEntranceFromNextRoomX());
    hero->setY(room->getEntranceFromNextRoomY());
    
    items = room->retrieveItems();
    helpTiles = room->retrieveHelpTiles();
    
  }
  
  this->drawTerrain(nextRoomSnapshot->getCanvas());
  this->drawCharacters(nextRoomSnapshot->getCanvas());
  
  state = WORLD_ROOM_TRANSITION_STATE;
}


void World::drawTerrain(BITMAP * buffer) {
  
  HelpTile *helpTile;
  
  room->draw(buffer);
  
  // Draw help tiles.
  helpTiles->iterate();
  while ((helpTile = (HelpTile *)helpTiles->getNext()) != NULL) {
    helpTileAnimation->drawTo(buffer, helpTile->getX() * getTileSize(), helpTile->getY() * getTileSize());
  }
}


void World::drawCharacters(BITMAP *buffer) {
  
  List *enemies = room->getEnemies();
  Enemy *enemy;
  Item *item;
  
  items->iterate();
  while ((item = (Item *)items->getNext()) != NULL) {
    item->draw(buffer);
  }
  
  enemies->iterate();
  while ((enemy = (Enemy *)enemies->getNext()) != NULL) {
    enemy->draw(buffer);
  }
  
  hero->draw(buffer);
}


void World::drawUserInterface(BITMAP * buffer) {
  
  HelpTile *helpTile;
  char moneyLine[256];
  int i;
  
  // Put the hero's health on the screen.
  for (i = 0; i < hero->getMaxHealth(); i++) {
    if (i < hero->getHealth()) {
      heartAnimation->drawTo(buffer, getWindowWidth() - (MAX_HERO_HEALTH + 1) * (getTileSize() / 2) + (i * (getTileSize() / 2)), 0);
    } else {
      heartEmptyAnimation->drawTo(buffer, getWindowWidth() - (MAX_HERO_HEALTH + 1) * (getTileSize() / 2) + (i * (getTileSize() / 2)), 0);
    }
  }
  
  sprintf(moneyLine, "$%d", hero->getMoney());
  resizedTextOut(buffer, getWindowWidth() - (getTileSize() * 2), getTileSize(), 2, WHITE, moneyLine);
  
  // Draw help information.
  helpTiles->iterate();
  
  while ((helpTile = (HelpTile *)helpTiles->getNext()) != NULL) {
    if (helpTile->getX() == hero->getX() && helpTile->getY() == hero->getY()) {
      helpTile->draw(buffer);
    }
  }
}


void World::draw(BITMAP * buffer) {
  
  switch (state) {
  
  case WORLD_UPDATE_STATE:
    this->drawTerrain(buffer);
    this->drawCharacters(buffer);
    this->drawUserInterface(buffer);
    break;
  
  case WORLD_ROOM_TRANSITION_STATE:
    prevRoomSnapshot->draw(buffer);
    nextRoomSnapshot->draw(buffer);
    this->drawUserInterface(buffer);
    break;
  
  case WORLD_SHAKING_STATE:
    this->drawTerrain(prevRoomSnapshot->getCanvas());
    this->drawCharacters(prevRoomSnapshot->getCanvas());
    prevRoomSnapshot->draw(buffer);
    this->drawUserInterface(buffer);
    break;
    
  }
  
  // Put the current room number on the screen.
  textprintf_ex(buffer, font, getWindowWidth() - (getTileSize() * 3), getWindowHeight() - (getTileSize() / 2), WHITE, -1, "Room %d", room->getNumber());
}

