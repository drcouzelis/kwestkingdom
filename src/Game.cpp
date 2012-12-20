#include <stdio.h>

#include "Animation.h"
#include "EndlessWorld.h"
#include "Game.h"
#include "highscore.h"
#include "KeyControl.h"
#include "KwestKingdom.h"
#include "Resources.h"
#include "resources.h"
#include "RoomFactory.h"
#include "screen.h"
#include "Snapshot.h"
#include "StoryWorld.h"
#include "text.h"
#include "World.h"


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





Game::Game() {
  
  world = NULL;
  menuSelection = NEW_GAME_SELECTION;
  strcpy(playerInitials, "\0");
  
  titleAnimation = new Animation();
  titleAnimation->addFrame(getImage(IMAGES_TITLE));
  
  gameOverAnimation = new Animation();
  gameOverAnimation->addFrame(IMG("gameover.bmp"));
  
  escapeKey = new KeyControl(KEY_ESC);
  escapeKey->setDelay(GAME_TICKER);
  // The keys to toggle fullscreen and sound are loaded in "setState".
  fullscreenKey = NULL;
  soundKey = NULL;
  
  upKey = new KeyControl(KEY_UP);
  downKey = new KeyControl(KEY_DOWN);
  selectKey = new KeyControl(KEY_ENTER);
  upKey->setDelay(GAME_TICKER);
  downKey->setDelay(GAME_TICKER);
  selectKey->setDelay(GAME_TICKER);
  
  menuBackground = new Snapshot();
  highScoresBackground = new Snapshot();
  
  menuPointer = new Animation();
  menuPointer->addFrame(getImage(IMAGES_SWORD_HOLD_1));
  menuPointer->addFrame(getImage(IMAGES_SWORD_HOLD_2));
  menuPointer->addFrame(getImage(IMAGES_SWORD_HOLD_3));
  menuPointer->addFrame(getImage(IMAGES_SWORD_HOLD_4));
  menuPointer->setRotate(true);
  menuPointer->setLoop(true);
  menuPointer->setSpeed(6);
  
  this->setState(GAME_MENU_STATE);
}


Game::~Game() {
  delete world;
  delete titleAnimation;
  delete gameOverAnimation;
  delete fullscreenKey;
  delete soundKey;
  delete escapeKey;
  delete upKey;
  delete downKey;
  delete selectKey;
  delete menuBackground;
  delete highScoresBackground;
  delete menuPointer;
}


void Game::readPlayerInitials() {
  
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
  

  
}


void Game::update() {
  
  if (fullscreenKey != NULL && fullscreenKey->isPressed()) {
    if (init_screen(-1, -1, is_windowed_mode()) == false) {
      this->setState(GAME_QUIT_STATE);
    }
    setPalette();
  }
  
  if (soundKey != NULL && soundKey->isPressed()) {
    toggleSound();
  }
  
  switch (state) {
  
  case GAME_MENU_STATE:
    if (escapeKey->isPressed()) {
      this->setState(GAME_QUIT_STATE);
    } else if (upKey->isPressed()) {
      menuSelection--;
      if (menuSelection == RESUME_GAME_SELECTION && world == NULL) {
        menuSelection--;
      }
      if (menuSelection < 0) {
        menuSelection++;
      }
    } else if (downKey->isPressed()) {
      menuSelection++;
      if (menuSelection == RESUME_GAME_SELECTION && world == NULL) {
        menuSelection++;
      }
      if (menuSelection == MAX_MENU_SELECTIONS) {
        menuSelection--;
      }
    } else if (selectKey->isPressed()) {
      this->activateMenuSelection();
    }
    menuPointer->update();
    break;
  
  case GAME_PLAY_STATE:
    if (escapeKey->isPressed()) {
      this->setState(GAME_MENU_STATE);
    }
    world->update();
    break;
  
  case GAME_HIGH_SCORES_STATE:
    if (escapeKey->isPressed()) {
      this->setState(GAME_MENU_STATE);
    }
    break;
  
  case GAME_ENTER_INITIALS_STATE:
    this->readPlayerInitials();
    if (strlen(playerInitials) > 0 && selectKey->isPressed()) {
      this->setState(GAME_MENU_STATE);
      add_high_score(playerInitials, world->getRoomNumber(), world->getMoney());
      delete world;
      world = NULL;
      strcpy(playerInitials, "\0");
    }
    break;
  
  case GAME_OVER_STATE:
    if (selectKey->isPressed()) {
      menuSelection = NEW_GAME_SELECTION;
      if (high_score_pos(world->getRoomNumber(), world->getMoney()) == MAX_NUM_OF_HIGH_SCORES) {
        this->setState(GAME_MENU_STATE);
        delete world;
        world = NULL;
      } else {
        this->setState(GAME_ENTER_INITIALS_STATE);
      }
    }
    break;
  
  case GAME_QUIT_STATE:
    // Do nothing.
    break;
  }
}


void Game::drawMenu(BITMAP * buffer) {
  
  int x;
  int y;
  int w;
  int h;
  int lineSpacing;
  int hTextOffset;
  int vTextOffset;
  
  x = (get_win_w() / 2) - (getTileSize() * 4);
  y = (get_win_h() / 2) - (getTileSize() / 2);
  w = getTileSize() * 4 * 2;
  h = getTileSize() * 5;
  lineSpacing = getTileSize() / 2;
  hTextOffset = getTileSize();
  vTextOffset = lineSpacing;
  
  menuBackground->draw(buffer);
  draw_box(buffer, x, y, w, h);

  // Draw the title of the game
  titleAnimation->drawTo(
    buffer,
    (get_win_w() / 2) - (titleAnimation->width() / 2),
    (get_win_w() - titleAnimation->width()) / 2
  );
  
  // New Game
  draw_text(buffer, x + hTextOffset, y + vTextOffset + (lineSpacing * NEW_GAME_SELECTION), 2, WHITE, (char *)"New Game");

  // Survival Mode
  draw_text(buffer, x + hTextOffset, y + vTextOffset + (lineSpacing * SURVIVAL_MODE_SELECTION), 2, WHITE, (char *)"Survival Mode");
  
  // Resume Game
  if (world == NULL) {
    draw_text(buffer, x + hTextOffset, y + vTextOffset + (lineSpacing * RESUME_GAME_SELECTION), 2, GRAY, (char *)"Resume Game");
  } else {
    draw_text(buffer, x + hTextOffset, y + vTextOffset + (lineSpacing * RESUME_GAME_SELECTION), 2, WHITE, (char *)"Resume Game");
  }
  
  // High Scores
  draw_text(buffer, x + hTextOffset, y + vTextOffset + (lineSpacing * HIGH_SCORES_SELECTION), 2, WHITE, (char *)"High Scores");
  
  // Quit
  draw_text(buffer, x + hTextOffset - lineSpacing, y + vTextOffset + (lineSpacing * (MAX_MENU_SELECTIONS + 1)), 2, WHITE, (char *)"Press ESC To Quit");
  
  // Fullscreen
  if (is_windowed_mode()) {
    draw_text(buffer, x + hTextOffset - lineSpacing, y + vTextOffset + (lineSpacing * (MAX_MENU_SELECTIONS + 2)), 2, WHITE, (char *)"F for Fullscreen");
  } else {
    draw_text(buffer, x + hTextOffset - lineSpacing, y + vTextOffset + (lineSpacing * (MAX_MENU_SELECTIONS + 2)), 2, WHITE, (char *)"F for Windowed");
  }
  
  // Sound
  if (soundEnabled()) {
    draw_text(buffer, x + hTextOffset - lineSpacing, y + vTextOffset + (lineSpacing * (MAX_MENU_SELECTIONS + 3)), 2, WHITE, (char *)"S for Sound (On)");
  } else {
    draw_text(buffer, x + hTextOffset - lineSpacing, y + vTextOffset + (lineSpacing * (MAX_MENU_SELECTIONS + 3)), 2, WHITE, (char *)"S for Sound (Off)");
  }
  
  menuPointer->drawTo(buffer, x - 4, y + vTextOffset + (lineSpacing * menuSelection) - 1);
}


void Game::drawHighScores(BITMAP * buffer) {
  
  HIGH_SCORE high_score;
  int x;
  int y;
  int w;
  int h;
  int lineSpacing;
  int vTextOffset;
  
  char line[256];
  int i;
  
  x = getTileSize() * 3;
  y = getTileSize() * 2;
  w = getTileSize() * 10;
  h = getTileSize() * 8;
  lineSpacing = getTileSize() / 2;
  vTextOffset = lineSpacing;
  
  highScoresBackground->draw(buffer);
  draw_box(buffer, x, y, w, h);
  
  // Title
  draw_text(buffer, x + getTileSize() * 3, y + vTextOffset, 2, WHITE, (char *)"High Scores");
  
  // Header
  draw_text(buffer, x + getTileSize() + (getTileSize() / 4), y + vTextOffset + (lineSpacing * 2), 2, WHITE, (char *)"        Room  Coins");
  
  // High scores
  for (i = 0; i < MAX_NUM_OF_HIGH_SCORES; i++) {
    if (get_high_score(i, &high_score) == true) {
      sprintf(line, "#%d %3s %4d %6d", i + 1, high_score.initials, high_score.room, high_score.money);
    } else {
      sprintf(line, "#%d", i + 1);
    }
    draw_text(buffer, x + getTileSize() + (getTileSize() / 4), y + vTextOffset + (lineSpacing * 3) + (lineSpacing * i), 2, WHITE, line);
  }
  
  // Return
  draw_text(buffer, x + getTileSize() + (getTileSize() / 4), y + h - (lineSpacing * 2), 2, WHITE, (char *)"Press ESC to RETURN");
  

  
}


void Game::drawEnterInitials(BITMAP * buffer) {
  
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
  
  world->draw(buffer);
  
  draw_box(buffer, x, y, w, h);
  
  // Title
  draw_text(buffer, x + (getTileSize() * 4), y + vTextOffset, 2, WHITE, (char *)"Congratulations!");
  draw_text(buffer, x + (getTileSize() * 3), y + vTextOffset + (lineSpacing * 1), 2, WHITE, (char *)"You got a high score!");
  draw_text(buffer, x + getTileSize(), y + vTextOffset + (lineSpacing * 2), 2, WHITE, (char *)"Please enter your initials: ");
  
  // Initials
  draw_text(buffer, x + (getTileSize() * 12), y + vTextOffset + (lineSpacing * 2), 2, WHITE, playerInitials);
}


void Game::draw(BITMAP * buffer) {
  
  switch (state) {
  
  case GAME_MENU_STATE:
    this->drawMenu(buffer);
    break;
  
  case GAME_PLAY_STATE:
    world->draw(buffer);
    break;
  
  case GAME_OVER_STATE:
    world->draw(buffer);
    gameOverAnimation->drawTo(
      buffer,
      (get_win_w() / 2) - (gameOverAnimation->width() / 2),
      (get_win_h() / 2) - (gameOverAnimation->height() / 2)
    );
    break;
    
  case GAME_ENTER_INITIALS_STATE:
    this->drawEnterInitials(buffer);
    break;
    
  case GAME_HIGH_SCORES_STATE:
    this->drawHighScores(buffer);
    break;
  
  case GAME_QUIT_STATE:
    // Do nothing.
    break;
    
  }
  

  
}


void Game::activateMenuSelection() {
  switch (menuSelection) {
  case NEW_GAME_SELECTION:
    delete world;
    world = new StoryWorld();
    this->setState(GAME_PLAY_STATE);
    menuSelection = RESUME_GAME_SELECTION;
    break;
  case SURVIVAL_MODE_SELECTION:
    delete world;
    world = new EndlessWorld();
    this->setState(GAME_PLAY_STATE);
    menuSelection = RESUME_GAME_SELECTION;
    break;
  case RESUME_GAME_SELECTION:
    if (world != NULL) {
      this->setState(GAME_PLAY_STATE);
    }
    break;
  case HIGH_SCORES_SELECTION:
    this->setState(GAME_HIGH_SCORES_STATE);
    break;
  }

}


void Game::setState(int aState) {
  
  RoomFactory *roomFactory;
  Room *tempRoom;
  
  state = aState;
  
  switch (state) {
  
  case GAME_MENU_STATE:
    roomFactory = new RoomFactory();
    roomFactory->setType(ROOM_FOREST);
    roomFactory->setTerrain(ROOM_NO_WATER);
    tempRoom = roomFactory->createRoom();
    tempRoom->draw(menuBackground->getCanvas());
    delete tempRoom;
    delete roomFactory;
    // Load the fullscreen and sound keys.
    // They are disabled so the player could enter initials.
    if (fullscreenKey == NULL) {
      fullscreenKey = new KeyControl(KEY_F);
      fullscreenKey->setDelay(GAME_TICKER);
    }
    if (soundKey == NULL) {
      soundKey = new KeyControl(KEY_S);
      soundKey->setDelay(GAME_TICKER);
    }
    break;
    
  case GAME_HIGH_SCORES_STATE:
    roomFactory = new RoomFactory();
    roomFactory->setType(ROOM_UNDERGROUND);
    roomFactory->setTerrain(ROOM_NO_WATER);
    tempRoom = roomFactory->createRoom();
    tempRoom->draw(highScoresBackground->getCanvas());
    delete tempRoom;
    delete roomFactory;
    break;
    
  case GAME_ENTER_INITIALS_STATE:
    clear_keybuf();
    // Disable the fullscreen and sound keys so the player could enter initials.
    delete fullscreenKey;
    fullscreenKey = NULL;
    delete soundKey;
    soundKey = NULL;
    break;
    
  }
  

  
}


bool Game::continuePlaying() {
  if (state == GAME_QUIT_STATE) {
    return false;
  }
  return true;
}


void Game::gameOver() {
  this->setState(GAME_OVER_STATE);

}



