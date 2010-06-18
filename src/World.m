#import "Animation.h"
#import "Character.h"
#import "Enemy.h"
#import "HelpTile.h"
#import "Hero.h"
#import "List.h"
#import "Powerup.h"
#import "Room.h"
#import "RoomFactory.h"
#import "Snapshot.h"
#import "Text.h"
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
    [rooms add: room];
    
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
  
  int x;
  int y;
  
  Iterator *iterator = [[Iterator alloc] initList: items];
  
  while ([iterator hasNext]) {
    
    Powerup *item = (Powerup *)[iterator next]; 
    
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
    
  }
  
  [iterator free];
  
  return self;
}


- updateTurn {
  
  int index;
  
  // Determine whose turn it is next and tell them to go.
  if (currentCharacter == nil || [currentCharacter waiting]) {
    
    if (currentCharacter == nil) {
      currentCharacter = hero;
    } else if (currentCharacter == hero) {
      currentCharacter = (Character *)[enemies itemAtIndex: 0];
      if (currentCharacter == nil) {
        currentCharacter = hero;
      }
    } else {
      index = [enemies findIndexOf: currentCharacter];
      if (index >= 0) {
        currentCharacter = [enemies itemAtIndex: index + 1];
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
    game_over();
  }
  
  return self;
  
}


- updateEnemies {
  
  // Update the enemies and remove any that are dead.
  Iterator *iterator = [[Iterator alloc] initList:enemies];
  
  while ([iterator hasNext]) {
    
    Enemy *enemy = (Enemy *)[iterator next];
    
    [enemy update];
    
    if ([enemy isDead]) {
      [enemy dropItem];
      [enemies remove: enemy];
    }
    
  }
  
  [iterator free];
  
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


- addCharacter: (Character *) aCharacter {
  if (aCharacter != nil) {
    [aCharacter setWorld: self];
    [enemies add: aCharacter];
  }
  return self;
}


- addItem: (Powerup *) anItem {
  if (anItem != nil) {
    [items add: anItem];
  }
  return self;
}


- addHelpTile: (id) aHelpTile {
  if (aHelpTile != nil) {
    [helpTiles add: aHelpTile];
  }
  return self;
}


- (Character *)getTarget {
  return hero;
}


- (BOOL) isAttackableFromTeam: (int) team atX: (int) x andY: (int) y {
  
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
      
      Iterator *iterator = [[Iterator alloc] initList:enemies];
      
      while ([iterator hasNext]) {
        Enemy *enemy = (Enemy *)[iterator next]; 
        for (m = 0; m < [enemy getWidth]; m++) {
          for (n = 0; n < [enemy getHeight]; n++) {
            if (team != [enemy getTeam] && x + i == [enemy getX] + m && y + j == [enemy getY] + n) {
              return YES;
            }
          }
        }
      }
      
      [iterator free];
      
    }
  }
  
  return NO;
  
}


- attackFromTeam: (int) team atX: (int) x andY: (int) y {
  
  int m, n;
  
  for (m = 0; m < [hero getWidth]; m++) {
    for (n = 0; n < [hero getHeight]; n++) {
      if (team != [hero getTeam] && x == [hero getX] + m && y == [hero getY] + n) {
        [hero hurt];
      }
    }
  }
  
  Iterator *iterator = [[Iterator alloc] initList:enemies];
  
  while ([iterator hasNext]) {
    Enemy *enemy = (Enemy *)[iterator next];
    for (m = 0; m < [enemy getWidth]; m++) {
      for (n = 0; n < [enemy getHeight]; n++) {
        if (team != [enemy getTeam] && x == [enemy getX] + m && y == [enemy getY] + n) {
          [enemy hurt];
        }
      }
    }
  }
  
  [iterator free];
  
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
      
      Iterator *iterator = [[Iterator alloc] initList:enemies];
      
      while ([iterator hasNext]) {
        Enemy *enemy = (Enemy *)[iterator next];
        for (m = 0; m < [enemy getWidth]; m++) {
          for (n = 0; n < [enemy getHeight]; n++) {
            if (x + i == [enemy getX] + m && y + j == [enemy getY] + n) {
              return YES;
            }
          }
        }
      }
      
      [iterator free];
      
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
    
    nextRoom = (Room *)[rooms itemAtIndex: [rooms findIndexOf: room] + 1];
    
    // Create the next room here, if necessary.
    if (nextRoom != nil) {
      
      room = nextRoom;
      
    } else {
      
      entranceX = [(Room *)[rooms tail] getExitToNextRoomX];
      entranceY = [(Room *)[rooms tail] getExitToNextRoomY];
      
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
      [rooms add: nextRoom];
      
      room = nextRoom;
      
      // Delete the oldest room.
      if ([rooms size] > 2) {
        firstRoom = (Room *)[rooms head];
        [rooms remove: [rooms head]];
        [firstRoom free];
        firstRoom = (Room *)[rooms head];
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
    room = (Room *)[rooms itemAtIndex: [rooms findIndexOf: room] - 2];
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
  
  [room draw: buffer];
  
  // Draw help tiles.
  Iterator *iterator = [[Iterator alloc] initList:helpTiles];
  while ([iterator hasNext]) {
    HelpTile *helpTile = (HelpTile *)[iterator next];
    [helpTileAnimation draw: buffer atX: [helpTile getX] * getTileSize() andY: [helpTile getY] * getTileSize()];
  }
  [iterator free];
  
  return self;
}


- drawCharacters: (BITMAP *) buffer {
  
  Iterator *iterator = [[Iterator alloc] initList:items];
  while ([iterator hasNext]) {
    Powerup *item = (Powerup *)[iterator next];
    [item draw: buffer];
  }
  [iterator free];
  
  iterator = [[Iterator alloc] initList:enemies];
  while ([iterator hasNext]) {
    Enemy *enemy = (Enemy *)[iterator next];
    [enemy draw: buffer];
  }
  [iterator free];
  
  [hero draw: buffer];
  
  return self;
}


- drawUserInterface: (BITMAP *) buffer {
  
  char moneyLine[256];
  int i;
  
  // Put the hero's health on the screen.
  for (i = 0; i < [hero getMaxHealth]; i++) {
    if (i < [hero getHealth]) {
      [heartAnimation draw: buffer atX: getWindowWidth() - (MAX_HERO_HEALTH + 1) * (getTileSize() / 2) + (i * (getTileSize() / 2)) andY: 0];
    } else {
      [heartEmptyAnimation draw: buffer atX: getWindowWidth() - (MAX_HERO_HEALTH + 1) * (getTileSize() / 2) + (i * (getTileSize() / 2)) andY: 0];
    }
  }
  
  sprintf(moneyLine, "$%d", [hero getMoney]);
  resizedTextOut(buffer, getWindowWidth() - (getTileSize() * 2), getTileSize(), 2, WHITE, moneyLine);
  
  // Draw help information.
  Iterator *iterator = [[Iterator alloc] initList:helpTiles];
  while ([iterator hasNext]) {
    HelpTile *helpTile = (HelpTile *)[iterator next];
    if ([helpTile getX] == [hero getX] && [helpTile getY] == [hero getY]) {
      [helpTile draw: buffer];
    }
  }
  [iterator free];
  
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


@end

