#include <stdio.h>

#include "Enemy.h"
#include "HelpTile.h"
#include "Hero.h"
#include "Item.h"
#include "KwestKingdom.h"
#include "resources.h"
#include "RoomFactory.h"
#include "screen.h"
#include "Snapshot.h"
#include "text.h"
#include "World.h"


typedef enum {
  WORLD_UPDATE_STATE,
  WORLD_ROOM_TRANSITION_STATE,
  WORLD_SHAKING_STATE
} WORLD_STATE;


typedef enum
{
  HERO_TURN = 0,
  ENEMY_TURN = 4
} CHARACTER_TURN;


Room *curr_room(World *world)
{
  if (world->room_idx < 0 || world->room_idx => world->num_rooms) {
    return NULL;
  }

  return world->rooms[world->room_idx];
}


void add_room(World *world, Room *room)
{
  if (world->num_rooms < MAX_ROOMS) {
    world->rooms[world->num_rooms] = room;
    world->num_rooms++;
  }
}


void crop_rooms(World *world, int amount)
{
  if (amount < 0) {
    return;
  }

  while (world->num_rooms > amount) {
    // Remove oldest room
    delete world->rooms[0];

    for (i = 1; i < world->num_rooms; i++) {
      world->rooms[i - 1] = world->rooms[i];
    }

    if (i < MAX_ROOMS) {
      world->rooms[i] = NULL;
    }

    world->num_rooms--;

    if (world->room_idx > 0) {
      world->room_idx--;
    }

    // Remove entrance to the new first room
    world->rooms[0]->removeExitToPrevRoom();
  }
}


World::World() {
  
  Room *room;
  int i;

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
  
  room = this->createNextRoom();
  room->setExitToPrevRoomX(-1); // Remove the entrance to the first room.
  room->setExitToPrevRoomY(-1);
  
  for (i = 0; i < MAX_ROOMS; i++) {
    rooms[i] = NULL;
  }
  num_rooms = 0;
  room_idx = 0;

  add_room(this, room);
  
  init_anim(&heart_anim, OFF, 0);
  add_frame(&heart_anim, IMG("heart.bmp"));
  init_anim(&heart_empty_anim, OFF, 0);
  add_frame(&heart_empty_anim, IMG("emptyheart.bmp"));
  init_anim(&help_tile_anim, OFF, 0);
  add_frame(&help_tile_anim, IMG("help.bmp"));
  
  prevRoomSnapshot = new Snapshot();
  nextRoomSnapshot = new Snapshot();
  
  whose_turn = HERO_TURN;
  
  state = WORLD_UPDATE_STATE;
}


World::~World() {
  delete rooms;
  delete roomFactory;
  delete hero;
  delete prevRoomSnapshot;
  delete nextRoomSnapshot;
}


void World::updateRoom() {
  rooms[room_idx]->update();
}


void World::updateItems() {
  
  Item *item;
  int item_counter;
  int x;
  int y;
  
  for (item_counter = 0; item_counter < curr_room(this)->num_items; item_counter++) {

    item = curr_room(this)->items[item_counter];
    
    item->update();
    
    // For the entire size of the hero
    // see if he is standing on an item
    for (x = 0; x < hero->getWidth(); x++) {
      for (y = 0; y < hero->getHeight(); y++) {
        
        // Hero is standing on the item
        if (item->getX() == hero->getX() + x && item->getY() == hero->getY() + y) {
          item->collectedBy(hero);
          remove_item(curr_room(this), item_counter);
          item_counter--;
        }
        
      }
    }
  }
}


Character *get_active_character(World *world)
{
  if (world->whose_turn == HERO_TURN) {
    return world->hero;
  } else {
    return curr_room(world)->enemies[world->whose_turn - ENEMY_TURN];
  }
}


void cycle_active_character(World *world)
{
  if (world->whose_turn == HERO_TURN) {
    if (curr_room(world)->num_enemies > 0) {
      world->whose_turn = ENEMY_TURN;
    }
  } else {
    // Cycle through the list of enemies
    world->whose_turn++;
    if (world->whose_turn - ENEMY_TURN == curr_room(world)->num_enemies) {
      world->whose_turn = HERO_TURN;
    }
  }
}


void World::updateTurn() {
  
  // Determine whose turn it is next and tell them to go.
  if (get_active_character(this)->waiting()) {
    cycle_active_character(this);
    get_active_character(this)->go();
  }
}


void World::updateHero() {
  
  hero->update();
  
  // If the hero is at an exit...
  if (
    (hero->getX() == curr_room(this)->getExitToNextRoomX() && hero->getY() == curr_room(this)->getExitToNextRoomY()) ||
    (hero->getX() == curr_room(this)->getExitToPrevRoomX() && hero->getY() == curr_room(this)->getExitToPrevRoomY())
  ) {
    
    // This prevents enemies from moving around during a change of rooms.
    if (hero->waiting()) {
      hero->go();
    }
    
    if (!hero->moving()) {
      this->changeRooms();
      whose_turn = HERO_TURN;
    }
    
  }
  
  if (hero->isDead()) {
    game_over();
  }
}


void World::updateEnemies() {
  
  Enemy *enemy;
  int enemy_counter;
  
  // Update the enemies and remove any that are dead.
  for (enemy_counter = 0; enemy_counter < curr_room(this)->num_enemies; enemy_counter++) {
    
    enemy = curr_room(this)->enemies[enemy_counter];
    enemy->update();
    
    if (enemy->isDead()) {
      enemy->dropItem();
      remove_enemy(curr_room(this), enemy_counter);
      enemy_counter--;
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
    add_item(curr_room(this), anItem);
  }
}


void World::addHelpTile(HelpTile *aHelpTile) {
  if (aHelpTile != NULL) {
    add_help(curr_room(this), aHelpTile);
  }
}


Character * World::getTarget() {
  return hero;
}


FLAG World::isAttackable(int team, int x, int y) {
  
  Enemy *enemy;
  int enemy_counter;
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
            return ON;
          }
          
        }
      }
      
      for (enemy_counter = 0; enemy_counter < curr_room(this)->num_enemies; enemy_counter++) {
        enemy = curr_room(this)->enemies[enemy_counter];
        for (m = 0; m < enemy->getWidth(); m++) {
          for (n = 0; n < enemy->getHeight(); n++) {
            if (team != enemy->getTeam() && x + i == enemy->getX() + m && y + j == enemy->getY() + n) {
              return ON;
            }
          }
        }
      }
      
    }
  }
  
  return OFF;
}


void World::attackFromTeam(int team, int x, int y) {
  
  Enemy *enemy;
  int enemy_counter;
  int m, n;
  
  for (m = 0; m < hero->getWidth(); m++) {
    for (n = 0; n < hero->getHeight(); n++) {
      if (team != hero->getTeam() && x == hero->getX() + m && y == hero->getY() + n) {
        hero->hurt();
      }
    }
  }
  
  for (enemy_counter = 0; enemy_counter < curr_room(this)->num_enemies; enemy_counter++) {
    enemy = curr_room(this)->enemies[enemy_counter];
    for (m = 0; m < enemy->getWidth(); m++) {
      for (n = 0; n < enemy->getHeight(); n++) {
        if (team != enemy->getTeam() && x == enemy->getX() + m && y == enemy->getY() + n) {
          enemy->hurt();
        }
      }
    }
  }
}


FLAG World::isSwimmable(int x, int y) {
  if (x >= 0 && x <= COLS - 1 && y >= 0 && y <= ROWS - 1) {
    return curr_room(this)->isSwimmable(x, y);
  }
  return OFF;
}


FLAG World::isWalkable(int x, int y) {
  if (x >= 0 && x <= COLS - 1 && y >= 0 && y <= ROWS - 1) {
    return curr_room(this)->isWalkable(x, y);
  }
  // Areas outside of the room are walkable
  // This allows the hero to walk to the door
  return ON;
}


FLAG World::isJumpable(int x, int y) {
  if (x >= 0 && x <= COLS - 1 && y >= 0 && y <= ROWS - 1) {
    return curr_room(this)->isJumpable(x, y);
  }
  return ON;
}


FLAG World::isFlyable(int x, int y) {
  if (x >= 0 && x <= COLS - 1 && y >= 0 && y <= ROWS - 1) {
    return curr_room(this)->isFlyable(x, y);
  }
  return ON;
}


FLAG World::isSoarable(int x, int y) {
  if (x >= 0 && x <= COLS - 1 && y >= 0 && y <= ROWS - 1) {
    return curr_room(this)->isSoarable(x, y);
  }
  return ON;
}


FLAG World::isInhabited(int x, int y) {
  
  Enemy *enemy;
  int enemy_counter;
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
            return ON;
          }
          
        }
      }
      
      for (enemy_counter = 0; enemy_counter < curr_room(this)->num_enemies; enemy_counter++) {
        enemy = curr_room(this)->enemies[enemy_counter];
        for (m = 0; m < enemy->getWidth(); m++) {
          for (n = 0; n < enemy->getHeight(); n++) {
            if (x + i == enemy->getX() + m && y + j == enemy->getY() + n) {
              return ON;
            }
          }
        }
      }
      
    }
  }
  
  return OFF;
}


int World::getRoomNumber() {
  return curr_room(this)->getNumber();
}


int World::getMoney() {
  return hero->getMoney();
}


void World::shake() {
  state = WORLD_SHAKING_STATE;
  prevRoomSnapshot->setX(0);
  prevRoomSnapshot->setY(0);
  prevRoomSnapshot->moveY(10);
  prevRoomSnapshot->setSpeed(get_win_h());
  this->drawTerrain(prevRoomSnapshot->getCanvas());
  this->drawCharacters(prevRoomSnapshot->getCanvas());
}


Room * World::createNextRoom() {
  
  int number;
  
  if (curr_room(this) != NULL) {
    number = curr_room(this)->getNumber() + 1;
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
  
  Room *room;
  int entranceX;
  int entranceY;
  
  // Prepare the room transition.
  if (hero->getX() < 0) {
    prevRoomSnapshot->setX(0);
    prevRoomSnapshot->setY(0);
    prevRoomSnapshot->moveX(get_win_w());
    prevRoomSnapshot->setSpeed(get_win_w());
    nextRoomSnapshot->setX(-get_win_w());
    nextRoomSnapshot->setY(0);
    nextRoomSnapshot->moveX(0);
    nextRoomSnapshot->setSpeed(get_win_w());
  } else if (hero->getX() > COLS - 1) {
    prevRoomSnapshot->setX(0);
    prevRoomSnapshot->setY(0);
    prevRoomSnapshot->moveX(-get_win_w());
    prevRoomSnapshot->setSpeed(get_win_w());
    nextRoomSnapshot->setX(get_win_w());
    nextRoomSnapshot->setY(0);
    nextRoomSnapshot->moveX(0);
    nextRoomSnapshot->setSpeed(get_win_w());
  } else if (hero->getY() < 0) {
    prevRoomSnapshot->setX(0);
    prevRoomSnapshot->setY(0);
    prevRoomSnapshot->moveY(get_win_h());
    prevRoomSnapshot->setSpeed(get_win_h());
    nextRoomSnapshot->setX(0);
    nextRoomSnapshot->setY(-get_win_h());
    nextRoomSnapshot->moveY(0);
    nextRoomSnapshot->setSpeed(get_win_h());
  } else if (hero->getY() > ROWS - 1) {
    prevRoomSnapshot->setX(0);
    prevRoomSnapshot->setY(0);
    prevRoomSnapshot->moveY(-get_win_h());
    prevRoomSnapshot->setSpeed(get_win_h());
    nextRoomSnapshot->setX(0);
    nextRoomSnapshot->setY(get_win_h());
    nextRoomSnapshot->moveY(0);
    nextRoomSnapshot->setSpeed(get_win_h());
  } else {
    prevRoomSnapshot->setX(0);
    prevRoomSnapshot->setY(0);
    nextRoomSnapshot->setX(0);
    nextRoomSnapshot->setY(0);
  }
  
  this->drawTerrain(prevRoomSnapshot->getCanvas());
  this->drawCharacters(prevRoomSnapshot->getCanvas());
  
  // If the hero is at the exit that leads to the next room...
  if (hero->getX() == curr_room(this)->getExitToNextRoomX() && hero->getY() == curr_room(this)->getExitToNextRoomY()) {
    
    // Move the room index to point to the next room
    room_idx++;

    if (room_idx >= num_rooms) {

      // Delete the oldest room.
      crop_rooms(this, MAX_ROOMS);
      
      // Create the next room
      entranceX = rooms[room_idx - 1]->getExitToNextRoomX();
      entranceY = rooms[room_idx - 1]->getExitToNextRoomY();
      
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
      room = this->createNextRoom();
      rooms->append(room);
    }
    
    hero->setX(curr_room(this)->getEntranceFromPrevRoomX());
    hero->setY(curr_room(this)->getEntranceFromPrevRoomY());
    
  } else if (hero->getX() == curr_room(this)->getExitToPrevRoomX() && hero->getY() == curr_room(this)->getExitToPrevRoomY()) {
    
    // Go to the previous room.
    room_idx--;
    hero->setX(curr_room(this)->getEntranceFromNextRoomX());
    hero->setY(curr_room(this)->getEntranceFromNextRoomY());
    
  }
  
  this->drawTerrain(nextRoomSnapshot->getCanvas());
  this->drawCharacters(nextRoomSnapshot->getCanvas());
  
  state = WORLD_ROOM_TRANSITION_STATE;
}


void World::drawTerrain(IMAGE * canvas) {
  
  HelpTile *helpTile;
  int i;
  
  curr_room(this)->draw(canvas);
  
  // Draw help tiles.
  for (i = 0; i < curr_room(this)->num_helps; i++) {
    helpTile = curr_room(this)->helps[i];
    draw_anim(&help_tile_anim, canvas, helpTile->getX() * getTileSize(), helpTile->getY() * getTileSize());
  }
}


void World::drawCharacters(IMAGE *canvas) {
  
  Enemy *enemy;
  Item *item;
  int counter;
  
  for (counter = 0; counter < curr_room(this)->num_items; counter++) {
    item = curr_room(this)->items[counter];
    item->draw(canvas);
  }
  
  for (counter = 0; counter < curr_room(this)->num_enemies; counter++) {
    enemy = curr_room(this)->enemies[counter];
    enemy->draw(canvas);
  }
  
  hero->draw(canvas);
}


void World::drawUserInterface(IMAGE * canvas) {
  
  HelpTile *helpTile;
  int counter;
  char moneyLine[256];
  int i;
  
  // Put the hero's health on the screen.
  for (i = 0; i < hero->getMaxHealth(); i++) {
    if (i < hero->getHealth()) {
      draw_anim(&heart_anim, canvas, get_win_w() - (MAX_HERO_HEALTH + 1) * (getTileSize() / 2) + (i * (getTileSize() / 2)), 0);
    } else {
      draw_anim(&heart_empty_anim, canvas, get_win_w() - (MAX_HERO_HEALTH + 1) * (getTileSize() / 2) + (i * (getTileSize() / 2)), 0);
    }
  }
  
  sprintf(moneyLine, "$%d", hero->getMoney());
  draw_text(canvas, get_win_w() - (getTileSize() * 2), getTileSize(), 2, WHITE, moneyLine);
  
  // Draw help information.
  for (counter = 0; counter < curr_room(this)->num_helps; counter++) {
    helpTile = curr_room(this)->helps[counter];
    if (helpTile->getX() == hero->getX() && helpTile->getY() == hero->getY()) {
      helpTile->draw(canvas);
    }
  }
}


void World::draw(IMAGE * canvas) {

  char text[9];
  
  switch (state) {
  
  case WORLD_UPDATE_STATE:
    this->drawTerrain(canvas);
    this->drawCharacters(canvas);
    this->drawUserInterface(canvas);
    break;
  
  case WORLD_ROOM_TRANSITION_STATE:
    prevRoomSnapshot->draw(canvas);
    nextRoomSnapshot->draw(canvas);
    this->drawUserInterface(canvas);
    break;
  
  case WORLD_SHAKING_STATE:
    this->drawTerrain(prevRoomSnapshot->getCanvas());
    this->drawCharacters(prevRoomSnapshot->getCanvas());
    prevRoomSnapshot->draw(canvas);
    this->drawUserInterface(canvas);
    break;
    
  }
  
  // Put the current room number on the screen.
  sprintf(text, "Room %d", curr_room(this)->getNumber());
  draw_text(canvas, get_win_w() - (getTileSize() * 3), get_win_h() - (getTileSize() / 2), 1, WHITE, text);
}

