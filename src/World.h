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
#import "Collectable.h"
#import "Drawable.h"
#import "Enemy.h"
#import "HelpTile.h"
#import "Hero.h"
#import "Inhabitable.h"
#import "List.h"
#import "Room.h"
#import "RoomFactory.h"
#import "Snapshot.h"
#import "Targetable.h"
#import "Traversable.h"
#import "Updatable.h"


@interface World : Object <Drawable, Inhabitable, Targetable, Traversable, Updatable> {
  
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
  
}


- updateRoom;
- updateItems;
- updateTurn;
- updateHero;
- updateEnemies;

- (Room *) createNextRoom;
- changeRooms;

- drawTerrain: (BITMAP *) buffer;
- drawCharacters: (BITMAP *) buffer;
- drawUserInterface: (BITMAP *) buffer;

- (int) getRoomNumber;
- (int) getMoney;

- addHelpTile: (id) aHelpTile;


@end

