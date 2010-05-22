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
#include "RoomFactory.h"
#include "World.h"


typedef enum {
  WORLD_UPDATE_STATE,
  WORLD_ROOM_TRANSITION_STATE,
  WORLD_SHAKING_STATE
} WORLD_STATE;


World::World()
{
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
  
  room = createNextRoom();
  room->setExitToPrevRoomX(-1); // Remove the entrance to the first room.
  room->setExitToPrevRoomY(-1);
  
  rooms.push_back(room);
  
  enemies = new std::vector<Enemy*>;
  items = new std::vector<Collectable*>;
  helpTiles = new std::vector<HelpTile*>;
  
  heartAnimation = new Animation();
  heartAnimation->addFrame(get_image(IMG_ITEMS_HEART));
  heartEmptyAnimation = new Animation();
  heartEmptyAnimation->addFrame(get_image(IMG_ITEMS_EMPTYHEART));
  helpTileAnimation = new Animation();
  helpTileAnimation->addFrame(get_image(IMG_HELP));
  
  prevRoomSnapshot = new Snapshot();
  nextRoomSnapshot = new Snapshot();
  
  currentCharacter = NULL;
  
  state = WORLD_UPDATE_STATE;
}


World::~World()
{
  delete roomFactory;
  delete hero;
  delete enemies;
  delete items;
  delete helpTiles;
  delete heartAnimation;
  delete heartEmptyAnimation;
  delete helpTileAnimation;
  delete prevRoomSnapshot;
  delete nextRoomSnapshot;
}


void
World::updateRoom()
{
  room->update();
}


void
World::updateItems()
{
  Collectable* item;
  //Enemy *enemy;
  
  
  for (unsigned int i = 0; i < items->size(); i++) {
    
    item = (*items)[i];
    
    ((Updatable*)item)->update();
    
    // For the entire size of the hero
    // see if he is standing on an item
    for (int x = 0; x < hero->getWidth(); x++) {
      for (int y = 0; y < hero->getHeight(); y++) {
        
        // Hero is standing on the item
        if (((Positionable*)item)->getX() == hero->getX() + x && ((Positionable*)item)->getY() == hero->getY() + y) {
          item->collectedBy(hero);
          // YOU LEFT OFF HERE!!
          // Figure out how to erase items
          //items->erase(item);
        }
        
      }
    }
    
  }
  
}


void
World::updateTurn()
{
  int index;
  
  // Determine whose turn it is next and tell them to go.
  if (currentCharacter == NULL || currentCharacter->isWaiting()) {
    
    if (currentCharacter == NULL) {
      currentCharacter = hero;
    } else if (currentCharacter == hero) {
      currentCharacter = enemies[0];
      if (currentCharacter == NULL) {
        currentCharacter = hero;
      }
    } else {
      /*
      // YOU LEFT OFF HERE!!
      // Figure out to find these characters
      index = [enemies findIndex: currentCharacter];
      if (index >= 0) {
        currentCharacter = [enemies getIndex: index + 1];
      } else {
        currentCharacter = NULL;
      }
      if (currentCharacter == NULL) {
        currentCharacter = hero;
      }
      */
    }
    
    currentCharacter->go();
    
  }
}


void
World::updateHero()
{
  hero->update();
  
  // If the hero is at an exit...
  if (
    (hero->getX() == room->getExitToNextRoomX() && hero->getY() == room->getExitToNextRoomY()) ||
    (hero->getX() == room->getExitToPrevRoomX() && hero->getY() == room->getExitToPrevRoomY())
  ) {
    
    // This prevents enemies from moving around during a change of rooms.
    if (hero->isWaiting()) {
      hero->go();
    }
    
    if (!hero->isMoving()) {
      changeRooms();
      currentCharacter = hero;
    }
    
  }
  
  if (hero->isDead()) {
    game_over();
  }
}


void
World::updateEnemies()
{
  Enemy *enemy;
  
  // Update the enemies and remove any that are dead.
  for (int i = 0; i < enemies->size(); i++) {
    
    Enemy* enemy = enemies[i];
    
    [enemy update];
    
    if (enemy->isDead()) {
      enemy->dropItem();
      // YOU LEFT OFF HERE!!
      // Figure out how to remove an enemy
      //[enemies remove: enemy];
    }
    
  }
}


void
World::update()
{
  switch (state) {
  
  case WORLD_UPDATE_STATE:
    updateRoom();
    updateItems();
    updateTurn();
    updateHero();
    updateEnemies();
    break;
    
  case WORLD_ROOM_TRANSITION_STATE:
    prevRoomSnapshot->update();
    nextRoomSnapshot->update();
    if (!nextRoomSnapshot->isMoving()) {
      state = WORLD_UPDATE_STATE;
    }
    break;
  
  case WORLD_SHAKING_STATE:
    updateRoom();
    updateItems();
    updateTurn();
    updateHero();
    updateEnemies();
    prevRoomSnapshot->update();
    if (!prevRoomSnapshot->isMoving()) {
      if (prevRoomSnapshot->getY() == 10) {
        prevRoomSnapshot->moveY(-8);
      } else if (prevRoomSnapshot->getY() == -8) {
        prevRoomSnapshot->moveY(6];
      } else if (prevRoomSnapshot->getY() == 6) {
        prevRoomSnapshot->moveY(-4);
      } else if (prevRoomSnapshot->getY() == -4) {
        prevRoomSnapshot->moveY(2);
      } else if (prevRoomSnapshot->getY() == 2) {
        prevRoomSnapshot->moveY(0);
      } else if (prevRoomSnapshot getY() == 0) {
        state = WORLD_UPDATE_STATE;
      }
    }
    break;
  
  }
}


void
World::addCharacter(Character* character)
{
  if (character != NULL) {
    character->setWorld(this);
    enemies->push_back(character);
  }
}


void
World::addItem(Collectable* item)
{
  if (item != NULL) {
    items->push_back(anItem);
  }
}


void
World::addHelpTile(HelpTile* helpTile)
{
  if (helpTile != NULL) {
    helpTiles->push_back(helpTile);
  }
}


Positionable*
World::getTarget(){
  return hero;
}


bool
World::isAttackable(int team, int x, int y)
{
  int w = 1;
  int h = 1;
  
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      
      for (int m = 0; m < hero->getWidth(); m++) {
        for (int n = 0; n < hero->getHeight(); n++) {
          
          if (team != hero->getTeam() && x + i == hero->getX() + m && y + j == hero->getY() + n) {
            return true;
          }
          
        }
      }
      
      for (int e = 0; e < enemies->size(); e++) {
      	Enemy* enemy = enemies[e];
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


void
World::attack(int team, int x, int y)
{
  for (int m = 0; m < hero->getWidth(); m++) {
    for (int n = 0; n < hero->getHeight(); n++) {
      if (team != hero->getTeam() && x == hero->getX() + m && y == hero->getY() + n) {
        hero->hurt();
      }
    }
  }
  
  for (int e = 0; e < enemies->size(); e++) {
    Enemy* enemy = enemies[e];
    for (int m = 0; m < enemy->getWidth(); m++) {
      for (int n = 0; n < enemy->getHeight(); n++) {
        if (team != enemy->getTeam() && x == enemy->getX() + m && y == enemy->getY() + n) {
          enemy->hurt();
        }
      }
    }
  }
}


bool
World::isSwimmable(int x, int y)
{
  return room->isSwimmable(x, y);
}


bool
World::isWalkable(int x, int y)
{
  return room->isWalkable(x, y);
}


bool
World::isJumpable(int x, int y)
{
  return room->isJumpable(x, y);
}


bool
World::isFlyable(int x, int y)
{
  return room->isFlyable(x, y);
}


bool
World::isSoarable(int x, int y)
{
  return room->isSoarable(x, y);
}


bool
World::isInhabited(int x, int y)
{
  int w = 1;
  int h = 1;
  
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      
      for (int m = 0; m < hero->getWidth(); m++) {
        for (int n = 0; n < hero->getHeight(); n++) {
          
          if (x + i == hero->getX() + m && y + j == hero->getY() + n) {
            return true;
          }
          
        }
      }
      
      for (int e = 0; e < enemies->size(); e++) {
      	Enemy* enemy = enemies[e];
        for (int m = 0; m < enemy->getWidth(); m++) {
          for (int n = 0; n < enemy->getHeight(); n++) {
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


int
World::getRoomNumber()
{
  return room->getNumber();
}


int
World::getMoney()
{
  return hero->getMoney();
}


void
World::shake(){
  state = WORLD_SHAKING_STATE;
  prevRoomSnapshot->setX(0);
  prevRoomSnapshot->setY(0);
  prevRoomSnapshot->moveY(10);
  prevRoomSnapshot->setSpeed(getWindowHeight());
  drawTerrain(prevRoomSnapshot->getCanvas());
  drawCharacters(prevRoomSnapshot->getCanvas());
}


Room*
World::createNextRoom()
{
  int number = room->getNumber() + 1;
  
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


- changeRooms {
  
  Room *nextRoom;
  Room *firstRoom;
  int entranceX;
  int entranceY;
  
  // Prepare the room transition.
  if ([hero getX] < 0) {
    [prevRoomSnapshot setX: 0];
    [prevRoomSnapshot setY: 0];
    [prevRoomSnapshot moveX: getWindowWidth()];
    [prevRoomSnapshot setSpeed: getWindowWidth()];
    [nextRoomSnapshot setX: -getWindowWidth()];
    [nextRoomSnapshot setY: 0];
    [nextRoomSnapshot moveX: 0];
    [nextRoomSnapshot setSpeed: getWindowWidth()];
  } else if ([hero getX] > COLS - 1) {
    [prevRoomSnapshot setX: 0];
    [prevRoomSnapshot setY: 0];
    [prevRoomSnapshot moveX: -getWindowWidth()];
    [prevRoomSnapshot setSpeed: getWindowWidth()];
    [nextRoomSnapshot setX: getWindowWidth()];
    [nextRoomSnapshot setY: 0];
    [nextRoomSnapshot moveX: 0];
    [nextRoomSnapshot setSpeed: getWindowWidth()];
  } else if ([hero getY] < 0) {
    [prevRoomSnapshot setX: 0];
    [prevRoomSnapshot setY: 0];
    [prevRoomSnapshot moveY: getWindowHeight()];
    [prevRoomSnapshot setSpeed: getWindowHeight()];
    [nextRoomSnapshot setX: 0];
    [nextRoomSnapshot setY: -getWindowHeight()];
    [nextRoomSnapshot moveY: 0];
    [nextRoomSnapshot setSpeed: getWindowHeight()];
  } else if ([hero getY] > ROWS - 1) {
    [prevRoomSnapshot setX: 0];
    [prevRoomSnapshot setY: 0];
    [prevRoomSnapshot moveY: -getWindowHeight()];
    [prevRoomSnapshot setSpeed: getWindowHeight()];
    [nextRoomSnapshot setX: 0];
    [nextRoomSnapshot setY: getWindowHeight()];
    [nextRoomSnapshot moveY: 0];
    [nextRoomSnapshot setSpeed: getWindowHeight()];
  } else {
    [prevRoomSnapshot setX: 0];
    [prevRoomSnapshot setY: 0];
    [nextRoomSnapshot setX: 0];
    [nextRoomSnapshot setY: 0];
  }
  
  [self drawTerrain: [prevRoomSnapshot getCanvas]];
  [self drawCharacters: [prevRoomSnapshot getCanvas]];
  
  // If the hero is at the exit that leads to the next room...
  if ([hero getX] == [room getExitToNextRoomX] && [hero getY] == [room getExitToNextRoomY]) {
    
    [room storeEnemies: enemies];
    [room storeItems: items];
    [room storeHelpTiles: helpTiles];
    
    nextRoom = (Room *)[rooms getIndex: [rooms findIndex: room] + 1];
    
    // Create the next room here, if necessary.
    if (nextRoom != NULL) {
      
      room = nextRoom;
      
    } else {
      
      entranceX = [(Room *)[rooms getTail] getExitToNextRoomX];
      entranceY = [(Room *)[rooms getTail] getExitToNextRoomY];
      
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
      
      [roomFactory setPathBeginX: entranceX];
      [roomFactory setPathBeginY: entranceY];
      nextRoom = [self createNextRoom];
      [rooms append: nextRoom];
      
      room = nextRoom;
      
      // Delete the oldest room.
      if ([rooms size] > 2) {
        firstRoom = (Room *)[rooms getHead];
        [rooms remove: [rooms getHead]];
        [firstRoom free];
        firstRoom = (Room *)[rooms getHead];
        [firstRoom removeExitToPrevRoom];
      }
      
    }
    
    [hero setX: [room getEntranceFromPrevRoomX]];
    [hero setY: [room getEntranceFromPrevRoomY]];
    
    enemies = [room retrieveEnemies];
    items = [room retrieveItems];
    helpTiles = [room retrieveHelpTiles];
    
  } else if ([hero getX] == [room getExitToPrevRoomX] && [hero getY] == [room getExitToPrevRoomY]) {
    
    [room storeEnemies: enemies];
    [room storeItems: items];
    [room storeHelpTiles: helpTiles];
    
    // Go to the previous room.
    room = (Room *)[rooms getIndex: [rooms findIndex: room] - 1];
    [hero setX: [room getEntranceFromNextRoomX]];
    [hero setY: [room getEntranceFromNextRoomY]];
    
    enemies = [room retrieveEnemies];
    items = [room retrieveItems];
    helpTiles = [room retrieveHelpTiles];
    
  }
  
  [self drawTerrain: [nextRoomSnapshot getCanvas]];
  [self drawCharacters: [nextRoomSnapshot getCanvas]];
  
  state = WORLD_ROOM_TRANSITION_STATE;
  
  return self;
  
}


void
World::drawTerrain(BITMAP* buffer)
{
  HelpTile *helpTile;
  
  room->draw(buffer);
  
  // Draw help tiles.
  for (int i = 0; i < helpTiles->size(); i++) {
  	HelpTile* helpTile = helpTiles[i];
    helpTileAnimation->draw(buffer, helpTile->getX() * getTileSize(), helpTile->getY() * getTileSize());
  }
}


- drawCharacters: (BITMAP *) buffer{
  
  Enemy *enemy;
  id<Collectable, Drawable> item;
  
  [items iterate];
  while ((item = (id<Collectable, Drawable>)[items next]) != NULL) {
    [item draw: buffer];
  }
  
  [enemies iterate];
  while ((enemy = (Enemy *)[enemies next]) != NULL) {
    [enemy draw: buffer];
  }
  
  [hero draw: buffer];
  
  return self;
  
}


- drawUserInterface: (BITMAP *) buffer {
  
  HelpTile *helpTile;
  char moneyLine[256];
  int i;
  
  // Put the hero's health on the screen.
  for (i = 0; i < [hero getMaxHealth]; i++) {
    if (i < [hero getHealth]) {
      [heartAnimation drawTo: buffer atX: getWindowWidth() - (MAX_HERO_HEALTH + 1) * (getTileSize() / 2) + (i * (getTileSize() / 2)) andY: 0];
    } else {
      [heartEmptyAnimation drawTo: buffer atX: getWindowWidth() - (MAX_HERO_HEALTH + 1) * (getTileSize() / 2) + (i * (getTileSize() / 2)) andY: 0];
    }
  }
  
  sprintf(moneyLine, "$%d", [hero getMoney]);
  resizedTextOut(buffer, getWindowWidth() - (getTileSize() * 2), getTileSize(), 2, WHITE, moneyLine);
  
  // Draw help information.
  [helpTiles iterate];
  
  while ((helpTile = (HelpTile *)[helpTiles next]) != NULL) {
    if ([helpTile getX] == [hero getX] && [helpTile getY] == [hero getY]) {
      [helpTile draw: buffer];
    }
  }
  
  return self;
  
}


- draw: (BITMAP *) buffer {
  
  switch (state) {
  
  case WORLD_UPDATE_STATE:
    [self drawTerrain: buffer];
    [self drawCharacters: buffer];
    [self drawUserInterface: buffer];
    break;
  
  case WORLD_ROOM_TRANSITION_STATE:
    [prevRoomSnapshot draw: buffer];
    [nextRoomSnapshot draw: buffer];
    [self drawUserInterface: buffer];
    break;
  
  case WORLD_SHAKING_STATE:
    [self drawTerrain: [prevRoomSnapshot getCanvas]];
    [self drawCharacters: [prevRoomSnapshot getCanvas]];
    [prevRoomSnapshot draw: buffer];
    [self drawUserInterface: buffer];
    break;
    
  }
  
  // Put the current room number on the screen.
  textprintf_ex(buffer, font, getWindowWidth() - (getTileSize() * 3), getWindowHeight() - (getTileSize() / 2), WHITE, -1, "Room %d", [room getNumber]);
  
  return self;
  
}
