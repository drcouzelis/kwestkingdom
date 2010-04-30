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
#ifndef __GAME_H
#define __GAME_H


#include "Animation.h"
#include "Drawable.h"
#include "EndlessWorld.h"
#include "HighScoreLibrary.h"
#include "KeyControl.h"
#include "KwestKingdom.h"
#include "Resources.h"
#include "RoomFactory.h"
#include "Snapshot.h"
#include "StoryWorld.h"
#include "Text.h"
#include "Updatable.h"


class Game : public virtual Drawable, public virtual Updatable
{
public:
  Game();

  virtual void readPlayerInitials();
  virtual bool continuePlaying();
  virtual void activateMenuSelection();
  
  virtual void drawMenu(BITMAP* buffer);
  virtual void drawHighScores(BITMAP* buffer);
  virtual void drawEnterInitials(BITMAP* buffer);
  
  virtual void setState(int state);

  virtual void gameOver();
  
protected:
  World* world;
  
  int state;
  
  Animation* titleAnimation;
  Animation* gameOverAnimation;
  
  KeyControl* fullscreenKey;
  KeyControl* soundKey;
  KeyControl* escapeKey;
  
  KeyControl* upKey;
  KeyControl* downKey;
  KeyControl* selectKey;
  
  int menuSelection;
  Snapshot* menuBackground;
  Snapshot* highScoresBackground;
  Animation* menuPointer;
  
  char playerInitials[4];
};


#endif // __GAME_H
