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
#import "World.h"


typedef enum {
  WORLD_UPDATE_STATE,
  WORLD_ROOM_TRANSITION_STATE,
  WORLD_SHAKING_STATE
} WORLD_STATE;


@implementation World


- init {
  
  self = [super init];
  
  if (self) {
    
    difficulty = 0;
    
    hero = [[Hero alloc] init];
    [hero setMaxHealth: MAX_HERO_HEALTH];
    [hero setHealth: MAX_HERO_HEALTH];
    [hero setWorld: self];
    [hero setX: COLS / 2 - 1];
    [hero setY: ROWS - 2];
    
    // Create the starting room.
    roomFactory = [[RoomFactory alloc] init];
    [roomFactory setWorld: self];
    [roomFactory setType: ROOM_FOREST];
    [roomFactory setTerrain: ROOM_NO_WATER];
    [roomFactory setNumber: 1];
    [roomFactory setDifficulty: difficulty];
    [roomFactory setPathBeginX: [hero getX]];
    [roomFactory setPathBeginY: [hero getY]];
    
    room = [self createNextRoom];
    [room setExitToPrevRoomX: -1]; // Remove the entrance to the first room.
    [room setExitToPrevRoomY: -1];
    
    rooms = [[List alloc] init];
    [rooms append: room];
    
    enemies = [[List alloc] init];
    items = [[List alloc] init];
    helpTiles = [[List alloc] init];
    
    heartAnimation = [[Animation alloc] init];
    [heartAnimation addFrame: getImage(IMG_ITEMS_HEART)];
    heartEmptyAnimation = [[Animation alloc] init];
    [heartEmptyAnimation addFrame: getImage(IMG_ITEMS_EMPTYHEART)];
    helpTileAnimation = [[Animation alloc] init];
    [helpTileAnimation addFrame: getImage(IMG_HELP)];
    
    prevRoomSnapshot = [[Snapshot alloc] init];
    nextRoomSnapshot = [[Snapshot alloc] init];
    
    currentCharacter = nil;
    
    state = WORLD_UPDATE_STATE;
    
  }
  
  return self;
  
}


- free {
  [rooms free];
  [roomFactory free];
  [hero free];
  [enemies free];
  [items free];
  [helpTiles free];
  [heartAnimation free];
  [heartEmptyAnimation free];
  [helpTileAnimation free];
  [prevRoomSnapshot free];
  [nextRoomSnapshot free];
  return [super free];
}


- updateRoom {
  [room update];
  return self;
}


- updateItems {
  
  id<Collectable, Positionable, Updatable> item;
  //Enemy *enemy;
  int x;
  int y;
  
  [items iterate];
  while ((item = (id<Collectable, Positionable, Updatable>)[items next]) != nil) {
    
    [item update];
    
    // For the entire size of the hero
    // see if he is standing on an item
    for (x = 0; x < [hero getWidth]; x++) {
      for (y = 0; y < [hero getHeight]; y++) {
        
        // Hero is standing on the item
        if ([item getX] == [hero getX] + x && [item getY] == [hero getY] + y) {
          [item collectedBy: hero];
          [items remove: item];
          return self;
        }
        
      }
    }
    
    /*
    // Enemies can not collect items.
    [enemies iterate];
    while ((enemy = (Enemy *)[enemies next]) != nil) {
      
      // For the entire size of the hero
      // see if he is standing on an item
      for (x = 0; x < [enemy getWidth]; x++) {
        for (y = 0; y < [enemy getHeight]; y++) {
          
          // If an enemy is standing on the item
          if ([item getX] == [enemy getX] + x && [item getY] == [enemy getY] + y) {
            [item collectedBy: enemy];
            [items remove: item];
            return self;
          }
          
        }
      }
      
    }
    */
    
  }
  
  return self;
  
}


- updateTurn {
  
  int index;
  
  // Determine whose turn it is next and tell them to go.
  if (currentCharacter == nil || [currentCharacter waiting]) {
    
    if (currentCharacter == nil) {
      currentCharacter = hero;
    } else if (currentCharacter == hero) {
      currentCharacter = (Character *)[enemies getIndex: 0];
      if (currentCharacter == nil) {
        currentCharacter = hero;
      }
    } else {
      index = [enemies findIndex: currentCharacter];
      if (index >= 0) {
        currentCharacter = [enemies getIndex: index + 1];
      } else {
        currentCharacter = nil;
      }
      if (currentCharacter == nil) {
        currentCharacter = hero;
      }
    }
    
    [currentCharacter go];
    
  }
  
  return self;
  
}


- updateHero {
  
  [hero update];
  
  // If the hero is at an exit...
  if (
    ([hero getX] == [room getExitToNextRoomX] && [hero getY] == [room getExitToNextRoomY]) ||
    ([hero getX] == [room getExitToPrevRoomX] && [hero getY] == [room getExitToPrevRoomY])
  ) {
    
    // This prevents enemies from moving around during a change of rooms.
    if ([hero waiting]) {
      [hero go];
    }
    
    if (![hero moving]) {
      [self changeRooms];
      currentCharacter = hero;
    }
    
  }
  
  if ([hero isDead]) {
    KK_quit_game();
  }
  
  return self;
  
}


- updateEnemies {
  
  Enemy *enemy;
  
  // Update the enemies and remove any that are dead.
  [enemies iterate];
  while ((enemy = (Enemy *)[enemies next]) != nil) {
    
    [enemy update];
    
    if ([enemy isDead]) {
      [enemy dropItem];
      [enemies remove: enemy];
    }
    
  }
  
  return self;
  
}


- update {
  
  switch (state) {
  
  case WORLD_UPDATE_STATE:
    [self updateRoom];
    [self updateItems];
    [self updateTurn];
    [self updateHero];
    [self updateEnemies];
    break;
    
  case WORLD_ROOM_TRANSITION_STATE:
    [prevRoomSnapshot update];
    [nextRoomSnapshot update];
    if (![nextRoomSnapshot moving]) {
      state = WORLD_UPDATE_STATE;
    }
    break;
  
  case WORLD_SHAKING_STATE:
    [self updateRoom];
    [self updateItems];
    [self updateTurn];
    [self updateHero];
    [self updateEnemies];
    [prevRoomSnapshot update];
    if (![prevRoomSnapshot moving]) {
      if ([prevRoomSnapshot getY] == 10) {
        [prevRoomSnapshot moveY: -8];
      } else if ([prevRoomSnapshot getY] == -8) {
        [prevRoomSnapshot moveY: 6];
      } else if ([prevRoomSnapshot getY] == 6) {
        [prevRoomSnapshot moveY: -4];
      } else if ([prevRoomSnapshot getY] == -4) {
        [prevRoomSnapshot moveY: 2];
      } else if ([prevRoomSnapshot getY] == 2) {
        [prevRoomSnapshot moveY: 0];
      } else if ([prevRoomSnapshot getY] == 0) {
        state = WORLD_UPDATE_STATE;
      }
    }
    break;
  
  }
  
  return self;
}


- addCharacter: (id) aCharacter {
  if (aCharacter != nil) {
    [aCharacter setWorld: self];
    [enemies append: aCharacter];
  }
  return self;
}


- addItem: (id) anItem {
  if (anItem != nil) {
    [items append: anItem];
  }
  return self;
}


- addHelpTile: (id) aHelpTile {
  if (aHelpTile != nil) {
    [helpTiles append: aHelpTile];
  }
  return self;
}


- (id<Positionable>) getTarget {
  return hero;
}


- (BOOL) isAttackableFromTeam: (int) team atX: (int) x andY: (int) y {
  
  Enemy *enemy;
  int i, j;
  int m, n;
  
  int w, h;
  
  w = 1;
  h = 1;
  
  for (i = 0; i < w; i++) {
    for (j = 0; j < h; j++) {
      
      for (m = 0; m < [hero getWidth]; m++) {
        for (n = 0; n < [hero getHeight]; n++) {
          
          if (team != [hero getTeam] && x + i == [hero getX] + m && y + j == [hero getY] + n) {
            return YES;
          }
          
        }
      }
      
      [enemies iterate];
      while ((enemy = (Enemy *)[enemies next]) != nil) {
        for (m = 0; m < [enemy getWidth]; m++) {
          for (n = 0; n < [enemy getHeight]; n++) {
            if (team != [enemy getTeam] && x + i == [enemy getX] + m && y + j == [enemy getY] + n) {
              return YES;
            }
          }
        }
      }
      
    }
  }
  
  return NO;
  
}


- attackFromTeam: (int) team atX: (int) x andY: (int) y {
  
  Enemy *enemy;
  int m, n;
  
  for (m = 0; m < [hero getWidth]; m++) {
    for (n = 0; n < [hero getHeight]; n++) {
      if (team != [hero getTeam] && x == [hero getX] + m && y == [hero getY] + n) {
        [hero hurt];
      }
    }
  }
  
  [enemies iterate];
  while ((enemy = (Enemy *)[enemies next]) != nil) {
    for (m = 0; m < [enemy getWidth]; m++) {
      for (n = 0; n < [enemy getHeight]; n++) {
        if (team != [enemy getTeam] && x == [enemy getX] + m && y == [enemy getY] + n) {
          [enemy hurt];
        }
      }
    }
  }
  
  return self;
  
}


- (BOOL) isSwimmableAtX: (int) x andY: (int) y {
  return [room isSwimmableAtX: x andY: y];
}


- (BOOL) isWalkableAtX: (int) x andY: (int) y {
  return [room isWalkableAtX: x andY: y];
}


- (BOOL) isJumpableAtX: (int) x andY: (int) y {
  return [room isJumpableAtX: x andY: y];
}


- (BOOL) isFlyableAtX: (int) x andY: (int) y {
  return [room isFlyableAtX: x andY: y];
}


- (BOOL) isSoarableAtX: (int) x andY: (int) y {
  return [room isSoarableAtX: x andY: y];
}


- (BOOL) isInhabitedAtX: (int) x andY: (int) y {
  
  Enemy *enemy;
  int i, j;
  int m, n;
  
  int w, h;
  
  w = 1;
  h = 1;
  
  for (i = 0; i < w; i++) {
    for (j = 0; j < h; j++) {
      
      for (m = 0; m < [hero getWidth]; m++) {
        for (n = 0; n < [hero getHeight]; n++) {
          
          if (x + i == [hero getX] + m && y + j == [hero getY] + n) {
            return YES;
          }
          
        }
      }
      
      [enemies iterate];
      while ((enemy = (Enemy *)[enemies next]) != nil) {
        for (m = 0; m < [enemy getWidth]; m++) {
          for (n = 0; n < [enemy getHeight]; n++) {
            if (x + i == [enemy getX] + m && y + j == [enemy getY] + n) {
              return YES;
            }
          }
        }
      }
      
    }
  }
  
  return NO;
  
}


- (int) getRoomNumber {
  return [room getNumber];
}


- (int) getMoney {
  return [hero getMoney];
}


- shake {
  state = WORLD_SHAKING_STATE;
  [prevRoomSnapshot setX: 0];
  [prevRoomSnapshot setY: 0];
  [prevRoomSnapshot moveY: 10];
  [prevRoomSnapshot setSpeed: getWindowHeight()];
  [self drawTerrain: [prevRoomSnapshot getCanvas]];
  [self drawCharacters: [prevRoomSnapshot getCanvas]];
  return self;
}


- (Room *) createNextRoom {
  
  int number;
  
  number = [room getNumber] + 1;
  
  if (number % 20 == 0) {
    [roomFactory setType: ROOM_UNDERGROUND];
    [roomFactory setTerrain: ROOM_NO_WATER];
    [roomFactory setDifficulty: 0];
  } else if (number / 20 % 2 == 0) {
    [roomFactory setType: ROOM_FOREST];
    [roomFactory setTerrain: ROOM_RANDOM];
    [roomFactory setDifficulty: difficulty];
  } else {
    [roomFactory setType: ROOM_SNOW];
    [roomFactory setTerrain: ROOM_RANDOM];
    [roomFactory setDifficulty: difficulty];
  }
  
  [roomFactory setNumber: number];
  
  return [roomFactory createRoom];
  
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
    if (nextRoom != nil) {
      
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


- drawTerrain: (BITMAP *) buffer {
  
  HelpTile *helpTile;
  
  [room draw: buffer];
  
  // Draw help tiles.
  [helpTiles iterate];
  while ((helpTile = (HelpTile *)[helpTiles next]) != nil) {
    [helpTileAnimation drawTo: buffer atX: [helpTile getX] * KK_tile_size() andY: [helpTile getY] * KK_tile_size()];
  }
  
  return self;
  
}


- drawCharacters: (BITMAP *) buffer{
  
  Enemy *enemy;
  id<Collectable, Drawable> item;
  
  [items iterate];
  while ((item = (id<Collectable, Drawable>)[items next]) != nil) {
    [item draw: buffer];
  }
  
  [enemies iterate];
  while ((enemy = (Enemy *)[enemies next]) != nil) {
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
      [heartAnimation drawTo: buffer atX: getWindowWidth() - (MAX_HERO_HEALTH + 1) * (KK_tile_size() / 2) + (i * (KK_tile_size() / 2)) andY: 0];
    } else {
      [heartEmptyAnimation drawTo: buffer atX: getWindowWidth() - (MAX_HERO_HEALTH + 1) * (KK_tile_size() / 2) + (i * (KK_tile_size() / 2)) andY: 0];
    }
  }
  
  sprintf(moneyLine, "$%d", [hero getMoney]);
  resizedTextOut(buffer, getWindowWidth() - (KK_tile_size() * 2), KK_tile_size(), 2, WHITE, moneyLine);
  
  // Draw help information.
  [helpTiles iterate];
  
  while ((helpTile = (HelpTile *)[helpTiles next]) != nil) {
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
  textprintf_ex(buffer, font, getWindowWidth() - (KK_tile_size() * 3), getWindowHeight() - (KK_tile_size() / 2), WHITE, -1, "Room %d", [room getNumber]);
  
  return self;
  
}


@end

