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
#ifndef __WORLD_H
#define __WORLD_H


#include <vector>

#include "Collectable.h"
#include "Drawable.h"
#include "Enemy.h"
#include "HelpTile.h"
#include "Hero.h"
#include "Inhabitable.h"
#include "Room.h"
#include "Snapshot.h"
#include "Targetable.h"
#include "Traversable.h"
#include "Updatable.h"
#include "Text.h"


class HelpTile;
class RoomFactory;


class World
: public virtual Drawable
, public virtual Inhabitable
, public virtual Targetable
, public virtual Traversable
, public virtual Updatable
{
public:
  World();
  ~World();
  
  virtual void draw(BITMAP* buffer); // Drawable
  
  virtual bool isInhabited(int x, int y);            // Inhabitable
  virtual bool isAttackable(int team, int x, int y); // Inhabitable
  virtual void attack(int team, int x, int y);       // Inhabitable
  virtual void addCharacter(Character* character);   // Inhabitable
  virtual void addItem(Sprite* item);                // Inhabitable
  virtual void shake();                              // Inhabitable
  
  virtual Positionable* getTarget(); // Targetable
  
  virtual bool isSwimmable(int x, int y); // Traversable
  virtual bool isWalkable(int x, int y);  // Traversable
  virtual bool isJumpable(int x, int y);  // Traversable
  virtual bool isFlyable(int x, int y);   // Traversable
  virtual bool isSoarable(int x, int y);  // Traversable
  
  virtual void update(); // Updatable
  
  virtual void updateRoom();
  virtual void updateItems();
  virtual void updateTurn();
  virtual void updateHero();
  virtual void updateEnemies();
  
  virtual Room* createNextRoom();
  virtual void changeRooms();
  
  virtual void drawTerrain(BITMAP* buffer);
  virtual void drawCharacters(BITMAP* buffer);
  virtual void drawUserInterface(BITMAP* buffer);
  
  virtual int getRoomNumber();
  virtual int getMoney();
  
  virtual void addHelpTile(HelpTile* helpTile);
  
protected:
  Hero* hero;
  std::vector<Enemy*>* enemies;
  std::vector<Room*> rooms;
  
  RoomFactory* roomFactory;
  Room* room;
  
  std::vector<Collectable*>* items;
  std::vector<HelpTile*>* helpTiles;
  
  Animation* heartAnimation;
  Animation* heartEmptyAnimation;
  Animation* helpTileAnimation;
  
  Character* currentCharacter;
  
  int difficulty;
  
  Snapshot* prevRoomSnapshot;
  Snapshot* nextRoomSnapshot;
  
  int state;
};


#endif // __WORLD_H
