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
#include "Game.h"

// TEMP
#include <cstdio>


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


Game::Game()
{
  world = NULL;
  menuSelection = NEW_GAME_SELECTION;
  strcpy(playerInitials, "\0");
  
  init_high_scores();
  
  titleAnimation = new Animation();
  titleAnimation->addFrame(get_image(IMG_TITLE));
  
  gameOverAnimation = new Animation();
  gameOverAnimation->addFrame(get_image(IMG_GAMEOVER));
  
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
  
  menuPointer = new Animation(6, true);
  menuPointer->addFrame(get_image(IMG_SWORD_HOLD_1));
  menuPointer->addFrame(get_image(IMG_SWORD_HOLD_2));
  menuPointer->addFrame(get_image(IMG_SWORD_HOLD_3));
  menuPointer->addFrame(get_image(IMG_SWORD_HOLD_4));
  menuPointer->setRotate(true);
  
  setState(GAME_MENU_STATE);
}


Game::~Game()
{
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


void
Game::readPlayerInitials()
{
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


void
Game::update()
{
  if (fullscreenKey != NULL && fullscreenKey->isPressed()) {
    if (init_screen(-1, -1, is_windowed_mode()) == false) {
      setState(GAME_QUIT_STATE);
    }
    set_palette();
  }
  
  if (soundKey != NULL && soundKey->isPressed()) {
    toggle_sound();
  }
  
  switch (state) {
  
  case GAME_MENU_STATE:
    if (escapeKey->isPressed()) {
      setState(GAME_QUIT_STATE);
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
      activateMenuSelection();
    }
    menuPointer->animate();
    break;
  
  case GAME_PLAY_STATE:
    if (escapeKey->isPressed()) {
      setState(GAME_MENU_STATE);
    }
    world->update();
    break;
  
  case GAME_HIGH_SCORES_STATE:
    if (escapeKey->isPressed()) {
      setState(GAME_MENU_STATE);
    }
    break;
  
  case GAME_ENTER_INITIALS_STATE:
    readPlayerInitials();
    if (strlen(playerInitials) > 0 && selectKey->isPressed()) {
      setState(GAME_MENU_STATE);
      add_high_score(playerInitials, world->getRoomNumber(), world->getMoney());
      delete world;
      world = NULL;
      strcpy(playerInitials, "\0");
    }
    break;
  
  case GAME_OVER_STATE:
    if (selectKey->isPressed()) {
      menuSelection = NEW_GAME_SELECTION;
      if (high_score_position(world->getRoomNumber(), world->getMoney()) == -1) {
        setState(GAME_MENU_STATE);
        delete world;
        world = NULL;
      } else {
        setState(GAME_ENTER_INITIALS_STATE);
      }
    }
    break;
  
  case GAME_QUIT_STATE:
    // Do nothing.
    break;
    
  }
  
}


void
Game::drawMenu(BITMAP* buffer)
{
  int x;
  int y;
  int w;
  int h;
  int lineSpacing;
  int hTextOffset;
  int vTextOffset;
  
  x = (window_width() / 2) - (getTileSize() * 4);
  y = (window_height() / 2) - (getTileSize() / 2);
  w = getTileSize() * 4 * 2;
  h = getTileSize() * 5;
  lineSpacing = getTileSize() / 2;
  hTextOffset = getTileSize();
  vTextOffset = lineSpacing;
  
  menuBackground->draw(buffer);
  draw_box(buffer, x, y, w, h);

  // Draw the title of the game
  titleAnimation->draw(
    buffer,
    (window_width() / 2) - (titleAnimation->getWidth() / 2),
    (window_width() - titleAnimation->getWidth()) / 2
  );
  
  // New Game
  resized_text_out(buffer, x + hTextOffset, y + vTextOffset + (lineSpacing * NEW_GAME_SELECTION), 2, WHITE, "New Game");

  // Survival Mode
  resized_text_out(buffer, x + hTextOffset, y + vTextOffset + (lineSpacing * SURVIVAL_MODE_SELECTION), 2, WHITE, "Survival Mode");
  
  // Resume Game
  if (world == NULL) {
    resized_text_out(buffer, x + hTextOffset, y + vTextOffset + (lineSpacing * RESUME_GAME_SELECTION), 2, GRAY, "Resume Game");
  } else {
    resized_text_out(buffer, x + hTextOffset, y + vTextOffset + (lineSpacing * RESUME_GAME_SELECTION), 2, WHITE, "Resume Game");
  }
  
  // High Scores
  resized_text_out(buffer, x + hTextOffset, y + vTextOffset + (lineSpacing * HIGH_SCORES_SELECTION), 2, WHITE, "High Scores");
  
  // Quit
  resized_text_out(buffer, x + hTextOffset - lineSpacing, y + vTextOffset + (lineSpacing * (MAX_MENU_SELECTIONS + 1)), 2, WHITE, "Press ESC To Quit");
  
  // Fullscreen
  if (is_windowed_mode()) {
    resized_text_out(buffer, x + hTextOffset - lineSpacing, y + vTextOffset + (lineSpacing * (MAX_MENU_SELECTIONS + 2)), 2, WHITE, "F for Fullscreen");
  } else {
    resized_text_out(buffer, x + hTextOffset - lineSpacing, y + vTextOffset + (lineSpacing * (MAX_MENU_SELECTIONS + 2)), 2, WHITE, "F for Windowed");
  }
  
  // Sound
  if (sound_enabled()) {
    resized_text_out(buffer, x + hTextOffset - lineSpacing, y + vTextOffset + (lineSpacing * (MAX_MENU_SELECTIONS + 3)), 2, WHITE, "S for Sound (On)");
  } else {
    resized_text_out(buffer, x + hTextOffset - lineSpacing, y + vTextOffset + (lineSpacing * (MAX_MENU_SELECTIONS + 3)), 2, WHITE, "S for Sound (Off)");
  }
  
  menuPointer->draw(buffer, x - 4, y + vTextOffset + (lineSpacing * menuSelection) - 1);
  
}


void
Game::drawHighScores(BITMAP* buffer)
{
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
  
  highScoresBackground->draw(buffer);
  draw_box(buffer, x, y, w, h);
  
  // Title
  resized_text_out(buffer, x + getTileSize() * 3, y + vTextOffset, 2, WHITE, "High Scores");
  
  // Header
  resized_text_out(buffer, x + getTileSize() + (getTileSize() / 4), y + vTextOffset + (lineSpacing * 2), 2, WHITE, "        Room  Coins");
  
  // High scores
  for (i = 0; i < MAX_NUM_OF_HIGH_SCORES; i++) {
    if (get_high_score(i, initials, &room, &coins) == true) {
      sprintf(line, "#%d %3s %4d %6d", i + 1, initials, room, coins);
    } else {
      sprintf(line, "#%d", i + 1);
    }
    resized_text_out(buffer, x + getTileSize() + (getTileSize() / 4), y + vTextOffset + (lineSpacing * 3) + (lineSpacing * i), 2, WHITE, line);
  }
  
  // Return
  resized_text_out(buffer, x + getTileSize() + (getTileSize() / 4), y + h - (lineSpacing * 2), 2, WHITE, "Press ESC to RETURN");
  
}


void
Game::drawEnterInitials(BITMAP* buffer)
{
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
  resized_text_out(buffer, x + (getTileSize() * 4), y + vTextOffset, 2, WHITE, "Congratulations!");
  resized_text_out(buffer, x + (getTileSize() * 3), y + vTextOffset + (lineSpacing * 1), 2, WHITE, "You got a high score!");
  resized_text_out(buffer, x + getTileSize(), y + vTextOffset + (lineSpacing * 2), 2, WHITE, "Please enter your initials: ");
  
  // Initials
  resized_text_out(buffer, x + (getTileSize() * 12), y + vTextOffset + (lineSpacing * 2), 2, WHITE, playerInitials);
  
}


void
Game::draw(BITMAP* buffer)
{
  switch (state) {
  
  case GAME_MENU_STATE:
    drawMenu(buffer);
    break;
  
  case GAME_PLAY_STATE:
    world->draw(buffer);
    break;
  
  case GAME_OVER_STATE:
    world->draw(buffer);
    gameOverAnimation->draw(
      buffer,
      (window_width() / 2) - (gameOverAnimation->getWidth() / 2),
      (window_height() / 2) - (gameOverAnimation->getHeight() / 2)
    );
    break;
    
  case GAME_ENTER_INITIALS_STATE:
    drawEnterInitials(buffer);
    break;
    
  case GAME_HIGH_SCORES_STATE:
    drawHighScores(buffer);
    break;
  
  case GAME_QUIT_STATE:
    // Do nothing.
    break;
    
  }
  
}


void
Game::activateMenuSelection()
{
  switch (menuSelection) {
  case NEW_GAME_SELECTION:
    delete world;
    world = new StoryWorld();
    setState(GAME_PLAY_STATE);
    menuSelection = RESUME_GAME_SELECTION;
    break;
  case SURVIVAL_MODE_SELECTION:
    delete world;
    world = new EndlessWorld();
    setState(GAME_PLAY_STATE);
    menuSelection = RESUME_GAME_SELECTION;
    break;
  case RESUME_GAME_SELECTION:
    if (world != NULL) {
      setState(GAME_PLAY_STATE);
    }
    break;
  case HIGH_SCORES_SELECTION:
    setState(GAME_HIGH_SCORES_STATE);
    break;
  }
}


void
Game::setState(int state)
{
  RoomFactory *roomFactory;
  Room *tempRoom;
  
  this->state = state;
  
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


bool
Game::continuePlaying()
{
  if (state == GAME_QUIT_STATE) {
    return false;
  }
  return true;
}


void
Game::gameOver()
{
  setState(GAME_OVER_STATE);
}

