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
#import "Game.h"


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


@implementation Game


- init {
  
  self = [super init];
  
  if (self) {
    
    world = nil;
    menuSelection = NEW_GAME_SELECTION;
    strcpy(playerInitials, "\0");
    
    [HighScoreLibrary initInstance];
    
    titleAnimation = [[Animation alloc] init];
    [titleAnimation addFrame: getImage(IMAGES_TITLE)];
    
    gameOverAnimation = [[Animation alloc] init];
    [gameOverAnimation addFrame: getImage(IMAGES_GAMEOVER)];
    
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
    [menuPointer addFrame: getImage(IMAGES_SWORD_HOLD_1)];
    [menuPointer addFrame: getImage(IMAGES_SWORD_HOLD_2)];
    [menuPointer addFrame: getImage(IMAGES_SWORD_HOLD_3)];
    [menuPointer addFrame: getImage(IMAGES_SWORD_HOLD_4)];
    [menuPointer setRotate: YES];
    [menuPointer setLoop: YES];
    [menuPointer setSpeed: 6];
    
    [self setState: GAME_MENU_STATE];
    
  }
  
  return self;
  
}


- (void) dealloc {
  [world release];
  [titleAnimation release];
  [gameOverAnimation release];
  [fullscreenKey release];
  [soundKey release];
  [escapeKey release];
  [upKey release];
  [downKey release];
  [selectKey release];
  [menuBackground release];
  [highScoresBackground release];
  [menuPointer release];
  [HighScoreLibrary deallocInstance];
  [super dealloc];
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
    if (initializeScreen(-1, -1, is_windowed_mode()) == NO) {
      [self setState: GAME_QUIT_STATE];
    }
    setPalette();
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
      [world release];
      world = nil;
      strcpy(playerInitials, "\0");
    }
    break;
  
  case GAME_OVER_STATE:
    if ([selectKey isPressed]) {
      menuSelection = NEW_GAME_SELECTION;
      if ([HighScoreLibrary highScorePositionWithRoom: [world getRoomNumber] andCoins: [world getMoney]] == -1) {
        [self setState: GAME_MENU_STATE];
        [world release];
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
  
  x = (getWindowWidth() / 2) - (getTileSize() * 4);
  y = (getWindowHeight() / 2) - (getTileSize() / 2);
  w = getTileSize() * 4 * 2;
  h = getTileSize() * 5;
  lineSpacing = getTileSize() / 2;
  hTextOffset = getTileSize();
  vTextOffset = lineSpacing;
  
  [menuBackground draw: buffer];
  drawBox(buffer, x, y, w, h);

  // Draw the title of the game
  [titleAnimation drawTo: buffer
    atX: (getWindowWidth() / 2) - ([titleAnimation width] / 2)
    andY: (getWindowWidth() - [titleAnimation width]) / 2
  ];
  
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
  if (is_windowed_mode()) {
    resizedTextOut(buffer, x + hTextOffset - lineSpacing, y + vTextOffset + (lineSpacing * (MAX_MENU_SELECTIONS + 2)), 2, WHITE, "F for Fullscreen");
  } else {
    resizedTextOut(buffer, x + hTextOffset - lineSpacing, y + vTextOffset + (lineSpacing * (MAX_MENU_SELECTIONS + 2)), 2, WHITE, "F for Windowed");
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
  
  x = getTileSize() * 3;
  y = getTileSize() * 2;
  w = getTileSize() * 10;
  h = getTileSize() * 8;
  lineSpacing = getTileSize() / 2;
  vTextOffset = lineSpacing;
  
  [highScoresBackground draw: buffer];
  drawBox(buffer, x, y, w, h);
  
  // Title
  resizedTextOut(buffer, x + getTileSize() * 3, y + vTextOffset, 2, WHITE, "High Scores");
  
  // Header
  resizedTextOut(buffer, x + getTileSize() + (getTileSize() / 4), y + vTextOffset + (lineSpacing * 2), 2, WHITE, "        Room  Coins");
  
  // High scores
  for (i = 0; i < MAX_NUM_OF_HIGH_SCORES; i++) {
    if ([HighScoreLibrary getHighScoreNumber: i returnInitials: initials andRoom: &room andCoins: &coins] == YES) {
      sprintf(line, "#%d %3s %4d %6d", i + 1, initials, room, coins);
    } else {
      sprintf(line, "#%d", i + 1);
    }
    resizedTextOut(buffer, x + getTileSize() + (getTileSize() / 4), y + vTextOffset + (lineSpacing * 3) + (lineSpacing * i), 2, WHITE, line);
  }
  
  // Return
  resizedTextOut(buffer, x + getTileSize() + (getTileSize() / 4), y + h - (lineSpacing * 2), 2, WHITE, "Press ESC to RETURN");
  
  return self;
  
}


- drawEnterInitials: (BITMAP *) buffer {
  
  int x;
  int y;
  int w;
  int h;
  
  int lineSpacing;
  int vTextOffset;
  
  x = getTileSize();
  y = getTileSize() * 5;
  w = getTileSize() * 14;
  h = (getTileSize() * 2) + (getTileSize() / 2);
  lineSpacing = getTileSize() / 2;
  vTextOffset = lineSpacing;
  
  [world draw: buffer];
  
  drawBox(buffer, x, y, w, h);
  
  // Title
  resizedTextOut(buffer, x + (getTileSize() * 4), y + vTextOffset, 2, WHITE, "Congratulations!");
  resizedTextOut(buffer, x + (getTileSize() * 3), y + vTextOffset + (lineSpacing * 1), 2, WHITE, "You got a high score!");
  resizedTextOut(buffer, x + getTileSize(), y + vTextOffset + (lineSpacing * 2), 2, WHITE, "Please enter your initials: ");
  
  // Initials
  resizedTextOut(buffer, x + (getTileSize() * 12), y + vTextOffset + (lineSpacing * 2), 2, WHITE, playerInitials);
  
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
    [gameOverAnimation drawTo: buffer
      atX: (getWindowWidth() / 2) - ([gameOverAnimation width] / 2)
      andY: (getWindowHeight() / 2) - ([gameOverAnimation height] / 2)];
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
    [world release];
    world = [[StoryWorld alloc] init];
    [self setState: GAME_PLAY_STATE];
    menuSelection = RESUME_GAME_SELECTION;
    break;
  case SURVIVAL_MODE_SELECTION:
    [world release];
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
    [tempRoom release];
    [roomFactory release];
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
    [tempRoom release];
    [roomFactory release];
    break;
    
  case GAME_ENTER_INITIALS_STATE:
    clear_keybuf();
    // Disable the fullscreen and sound keys so the player could enter initials.
    [fullscreenKey release];
    fullscreenKey = nil;
    [soundKey release];
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
