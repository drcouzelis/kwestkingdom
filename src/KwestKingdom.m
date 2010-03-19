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
#import "KwestKingdom.h"


typedef enum {
  GAME_MENU_STATE,
  GAME_PLAY_STATE,
  GAME_OVER_STATE,
  GAME_HIGH_SCORES_STATE,
  GAME_QUIT_STATE,
  GAME_ENTER_INITIALS_STATE
} GAME_STATE;


typedef enum {
  NEW_GAME_SELECTION = 0,
  SURVIVAL_MODE_SELECTION,
  RESUME_GAME_SELECTION,
  HIGH_SCORES_SELECTION,
  //FULLSCREEN_SELECTION,
  //SOUND_SELECTION,
  MAX_MENU_SELECTIONS
} MENU_SELECTION;


@implementation KwestKingdom


- init {
  
  self = [super init];
  
  if (self) {
    
    world = nil;
    menuSelection = NEW_GAME_SELECTION;
    strcpy(playerInitials, "\0");
    
    [HighScoreLibrary initInstance];
    
    titleAnimation = [[Animation alloc] init];
    [titleAnimation addFrame: getImage(TITLE_01_BMP)];
    
    gameOverAnimation = [[Animation alloc] init];
    [gameOverAnimation addFrame: getImage(GAME_OVER_01_BMP)];
    
    escapeKey = [[KeyControl alloc] initWithKey: KEY_ESC];
    [escapeKey setDelay: GAME_TICKER];
    // The keys to toggle fullscreen and sound are loaded in "setState".
    fullscreenKey = nil;
    soundKey = nil;
    
    upKey = [[KeyControl alloc] initWithKey: KEY_UP];
    downKey = [[KeyControl alloc] initWithKey: KEY_DOWN];
    selectKey = [[KeyControl alloc] initWithKey: KEY_ENTER];
    [upKey setDelay: GAME_TICKER];
    [downKey setDelay: GAME_TICKER];
    [selectKey setDelay: GAME_TICKER];
    
    menuBackground = [[Snapshot alloc] init];
    highScoresBackground = [[Snapshot alloc] init];
    
    menuPointer = [[Animation alloc] init];
    [menuPointer addFrame: getImage(SWORD_01_BMP)];
    [menuPointer addFrame: getImage(SWORD_02_BMP)];
    [menuPointer addFrame: getImage(SWORD_03_BMP)];
    [menuPointer addFrame: getImage(SWORD_04_BMP)];
    [menuPointer rotate: YES];
    [menuPointer setLoop: YES];
    [menuPointer setSpeed: 6];
    
    [self setState: GAME_MENU_STATE];
    
  }
  
  return self;
  
}


- free {
  [world free];
  [titleAnimation free];
  [gameOverAnimation free];
  [fullscreenKey free];
  [soundKey free];
  [escapeKey free];
  [upKey free];
  [downKey free];
  [selectKey free];
  [menuBackground free];
  [highScoresBackground free];
  [menuPointer free];
  [HighScoreLibrary freeInstance];
  return [super free];
}


- readPlayerInitials {
  
  int key;
  int length;
  
  if (keypressed()) {
    key = readkey();
    length = strlen(playerInitials);
    // If the player pressed "backspace" or "delete" then delet a character.
    if ((key >> 8) == KEY_BACKSPACE || (key >> 8) == KEY_DEL) {
      if (length > 0) {
        playerInitials[length - 1] = '\0';
      }
    } else if (((key >> 8) >= KEY_A && (key >> 8) <= KEY_Z) || ((key >> 8) >= KEY_0 && (key >> 8) <= KEY_9)) {
      // The player pressed a letter or number key! Add it to the initials.
      if (length < 3) {
        playerInitials[length] = key & 0xFF;
        playerInitials[length + 1] = '\0';
      }
    }
  }
  
  return self;
  
}


- update {
  
  if (fullscreenKey != nil && [fullscreenKey isPressed]) {
    if (toggleFullscreen() == 0) {
      [self setState: GAME_QUIT_STATE];
    }
  }
  
  if (soundKey != nil && [soundKey isPressed]) {
    toggleSound();
  }
  
  switch (state) {
  
  case GAME_MENU_STATE:
    if ([escapeKey isPressed]) {
      [self setState: GAME_QUIT_STATE];
    } else if ([upKey isPressed]) {
      menuSelection--;
      if (menuSelection == RESUME_GAME_SELECTION && world == nil) {
        menuSelection--;
      }
      if (menuSelection < 0) {
        menuSelection++;
      }
    } else if ([downKey isPressed]) {
      menuSelection++;
      if (menuSelection == RESUME_GAME_SELECTION && world == nil) {
        menuSelection++;
      }
      if (menuSelection == MAX_MENU_SELECTIONS) {
        menuSelection--;
      }
    } else if ([selectKey isPressed]) {
      [self activateMenuSelection];
    }
    [menuPointer update];
    break;
  
  case GAME_PLAY_STATE:
    if ([escapeKey isPressed]) {
      [self setState: GAME_MENU_STATE];
    }
    [world update];
    break;
  
  case GAME_HIGH_SCORES_STATE:
    if ([escapeKey isPressed]) {
      [self setState: GAME_MENU_STATE];
    }
    break;
  
  case GAME_ENTER_INITIALS_STATE:
    [self readPlayerInitials];
    if (strlen(playerInitials) > 0 && [selectKey isPressed]) {
      [self setState: GAME_MENU_STATE];
      [HighScoreLibrary addHighScoreWithInitials: playerInitials andRoom: [world getRoomNumber] andCoins: [world getMoney]];
      [world free];
      world = nil;
      strcpy(playerInitials, "\0");
    }
    break;
  
  case GAME_OVER_STATE:
    if ([selectKey isPressed]) {
      menuSelection = NEW_GAME_SELECTION;
      if ([HighScoreLibrary highScorePositionWithRoom: [world getRoomNumber] andCoins: [world getMoney]] == -1) {
        [self setState: GAME_MENU_STATE];
        [world free];
        world = nil;
      } else {
        [self setState: GAME_ENTER_INITIALS_STATE];
      }
    }
    break;
  
  case GAME_QUIT_STATE:
    // Do nothing.
    break;
    
  }
  
  return self;
  
}


- drawMenu: (BITMAP *) buffer {
  
  int x;
  int y;
  int w;
  int h;
  int lineSpacing;
  int hTextOffset;
  int vTextOffset;
  
  x = (SCREEN_WIDTH / 2) - 160;
  y = (SCREEN_HEIGHT / 2) - 20;
  w = 160 * 2;
  h = 200;
  lineSpacing = TILE_SIZE / 2;
  hTextOffset = TILE_SIZE;
  vTextOffset = lineSpacing;
  
  [menuBackground draw: buffer];
  drawBox(buffer, x, y, w, h);
  [titleAnimation drawTo: buffer atX: 54 andY: 54];
  
  // New Game
  resizedTextOut(buffer, x + hTextOffset, y + vTextOffset + (lineSpacing * NEW_GAME_SELECTION), 2, WHITE, "New Game");
  // Survival Mode
  resizedTextOut(buffer, x + hTextOffset, y + vTextOffset + (lineSpacing * SURVIVAL_MODE_SELECTION), 2, WHITE, "Survival Mode");
  
  // Resume Game
  if (world == nil) {
    resizedTextOut(buffer, x + hTextOffset, y + vTextOffset + (lineSpacing * RESUME_GAME_SELECTION), 2, GRAY, "Resume Game");
  } else {
    resizedTextOut(buffer, x + hTextOffset, y + vTextOffset + (lineSpacing * RESUME_GAME_SELECTION), 2, WHITE, "Resume Game");
  }
  
  // High Scores
  resizedTextOut(buffer, x + hTextOffset, y + vTextOffset + (lineSpacing * HIGH_SCORES_SELECTION), 2, WHITE, "High Scores");
  
  // Quit
  resizedTextOut(buffer, x + hTextOffset - lineSpacing, y + vTextOffset + (lineSpacing * (MAX_MENU_SELECTIONS + 1)), 2, WHITE, "Press ESC To Quit");
  
  // Fullscreen
  if (isFullscreen()) {
    resizedTextOut(buffer, x + hTextOffset - lineSpacing, y + vTextOffset + (lineSpacing * (MAX_MENU_SELECTIONS + 2)), 2, WHITE, "F for Windowed");
  } else {
    resizedTextOut(buffer, x + hTextOffset - lineSpacing, y + vTextOffset + (lineSpacing * (MAX_MENU_SELECTIONS + 2)), 2, WHITE, "F for Fullscreen");
  }
  
  // Sound
  if (soundEnabled()) {
    resizedTextOut(buffer, x + hTextOffset - lineSpacing, y + vTextOffset + (lineSpacing * (MAX_MENU_SELECTIONS + 3)), 2, WHITE, "S for Sound (On)");
  } else {
    resizedTextOut(buffer, x + hTextOffset - lineSpacing, y + vTextOffset + (lineSpacing * (MAX_MENU_SELECTIONS + 3)), 2, WHITE, "S for Sound (Off)");
  }
  
  [menuPointer drawTo: buffer atX: x - 4 andY: y + vTextOffset + (lineSpacing * menuSelection) - 1];
  
  return self;
  
}


- drawHighScores: (BITMAP *) buffer {
  
  int x;
  int y;
  int w;
  int h;
  int lineSpacing;
  int vTextOffset;
  
  char initials[4];
  int room;
  int coins;
  
  char line[256];
  int i;
  
  x = (SCREEN_WIDTH / 2) - 200;
  y = (SCREEN_HEIGHT / 2) - 200;
  w = 200 * 2;
  h = 200 * 2;
  lineSpacing = TILE_SIZE / 2;
  vTextOffset = lineSpacing;
  
  [highScoresBackground draw: buffer];
  drawBox(buffer, x, y, w, h);
  
  // Title
  resizedTextOut(buffer, x + 120, y + vTextOffset, 2, WHITE, "High Scores");
  
  // Header
  resizedTextOut(buffer, x + 50, y + vTextOffset + (lineSpacing * 2), 2, WHITE, "        Room  Coins");
  
  // High scores
  for (i = 0; i < MAX_NUM_OF_HIGH_SCORES; i++) {
    if ([HighScoreLibrary getHighScoreNumber: i returnInitials: initials andRoom: &room andCoins: &coins] == YES) {
      sprintf(line, "#%d %3s %4d %6d", i + 1, initials, room, coins);
    } else {
      sprintf(line, "#%d", i + 1);
    }
    resizedTextOut(buffer, x + 50, y + vTextOffset + (lineSpacing * 3) + (lineSpacing * i), 2, WHITE, line);
  }
  
  // Return
  resizedTextOut(buffer, x + 50, y + h - (lineSpacing * 2), 2, WHITE, "Press ESC to RETURN");
  
  return self;
  
}


- drawEnterInitials: (BITMAP *) buffer {
  
  int x;
  int y;
  int w;
  int h;
  
  int lineSpacing;
  int vTextOffset;
  
  x = (SCREEN_WIDTH / 2) - 280;
  y = (SCREEN_HEIGHT / 2) - 40;
  w = 280 * 2;
  h = 90;
  lineSpacing = TILE_SIZE / 2;
  vTextOffset = lineSpacing;
  
  [world draw: buffer];
  
  drawBox(buffer, x, y, w, h);
  
  // Title
  resizedTextOut(buffer, x + 160, y + vTextOffset, 2, WHITE, "Congratulations!");
  resizedTextOut(buffer, x + 110, y + vTextOffset + (lineSpacing * 1), 2, WHITE, "You got a high score!");
  resizedTextOut(buffer, x + 40, y + vTextOffset + (lineSpacing * 2), 2, WHITE, "Please enter your initials: ");
  
  // Initials
  resizedTextOut(buffer, x + 480, y + vTextOffset + (lineSpacing * 2), 2, WHITE, playerInitials);
  
  return self;
  
}


- draw: (BITMAP *) buffer {
  
  switch (state) {
  
  case GAME_MENU_STATE:
    [self drawMenu: buffer];
    break;
  
  case GAME_PLAY_STATE:
    [world draw: buffer];
    break;
  
  case GAME_OVER_STATE:
    [world draw: buffer];
    [gameOverAnimation drawTo: buffer atX: 0 andY: 0];
    break;
    
  case GAME_ENTER_INITIALS_STATE:
    [self drawEnterInitials: buffer];
    break;
    
  case GAME_HIGH_SCORES_STATE:
    [self drawHighScores: buffer];
    break;
  
  case GAME_QUIT_STATE:
    // Do nothing.
    break;
    
  }
  
  return self;
  
}


- activateMenuSelection {
  switch (menuSelection) {
  case NEW_GAME_SELECTION:
    [world free];
    world = [[StoryWorld alloc] init];
    [self setState: GAME_PLAY_STATE];
    menuSelection = RESUME_GAME_SELECTION;
    break;
  case SURVIVAL_MODE_SELECTION:
    [world free];
    world = [[EndlessWorld alloc] init];
    [self setState: GAME_PLAY_STATE];
    menuSelection = RESUME_GAME_SELECTION;
    break;
  case RESUME_GAME_SELECTION:
    if (world != nil) {
      [self setState: GAME_PLAY_STATE];
    }
    break;
  case HIGH_SCORES_SELECTION:
    [self setState: GAME_HIGH_SCORES_STATE];
    break;
  }
  return self;
}


- setState: (int) aState {
  
  RoomFactory *roomFactory;
  Room *tempRoom;
  
  state = aState;
  
  switch (state) {
  
  case GAME_MENU_STATE:
    roomFactory = [[RoomFactory alloc] init];
    [roomFactory setType: ROOM_FOREST];
    [roomFactory setTerrain: ROOM_NO_WATER];
    tempRoom = [roomFactory createRoom];
    [tempRoom draw: [menuBackground getCanvas]];
    [tempRoom free];
    [roomFactory free];
    // Load the fullscreen and sound keys.
    // They are disabled so the player could enter initials.
    if (fullscreenKey == nil) {
      fullscreenKey = [[KeyControl alloc] initWithKey: KEY_F];
      [fullscreenKey setDelay: GAME_TICKER];
    }
    if (soundKey == nil) {
      soundKey = [[KeyControl alloc] initWithKey: KEY_S];
      [soundKey setDelay: GAME_TICKER];
    }
    break;
    
  case GAME_HIGH_SCORES_STATE:
    roomFactory = [[RoomFactory alloc] init];
    [roomFactory setType: ROOM_UNDERGROUND];
    [roomFactory setTerrain: ROOM_NO_WATER];
    tempRoom = [roomFactory createRoom];
    [tempRoom draw: [highScoresBackground getCanvas]];
    [tempRoom free];
    [roomFactory free];
    break;
    
  case GAME_ENTER_INITIALS_STATE:
    clear_keybuf();
    // Disable the fullscreen and sound keys so the player could enter initials.
    [fullscreenKey free];
    fullscreenKey = nil;
    [soundKey free];
    soundKey = nil;
    break;
    
  }
  
  return self;
  
}


- (BOOL) continuePlaying {
  if (state == GAME_QUIT_STATE) {
    return NO;
  }
  return YES;
}


- gameOver {
  [self setState: GAME_OVER_STATE];
  return self;
}


@end
