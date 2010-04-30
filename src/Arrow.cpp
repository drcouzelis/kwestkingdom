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
#include "Arrow.h"
#include "World.h"


typedef enum {
  ARROW_HOLD_STATE,
  ARROW_FLYING_STATE,
  ARROW_STOPPED_STATE
} ARROW_STATE;


Arrow::Arrow()
{
  setSpeed(getWalkSpeed() * 4);
  
  flyRightAnimation = new Animation();
  flyRightAnimation->addFrame(get_image(IMG_ARROW));
  
  flyLeftAnimation = flyRightAnimation;
  flyLeftAnimation->setHorizontalFlip(true);
  
  flyDownAnimation = flyRightAnimation;
  flyDownAnimation->setRotate(true);
  
  flyUpAnimation = flyRightAnimation;
  flyUpAnimation->setHorizontalFlip(true);
  flyUpAnimation->setRotate(true);
  
  direction = UP;
  
  toHoldState();
  
}


Arrow::~Arrow()
{
  delete flyUpAnimation;
  delete flyDownAnimation;
  delete flyLeftAnimation;
  delete flyRightAnimation;
}


void
Arrow::update()
{
  Character::update();
  
  switch (state) {
  case ARROW_HOLD_STATE:
    // There's just not much going on when it's being held.
    break;
    
  case ARROW_FLYING_STATE:
    
    if (!isMoving()) {
      
      if (direction == LEFT) {
        world->attack(team, x - 1, y);
      } else if (direction == RIGHT) {
        world->attack(team, x + 1, y);
      } else if (direction == UP) {
        world->attack(team, x, y - 1);
      } else {
        world->attack(team, x, y + 1);
      }
      
      toStoppedState();
      
    }
    
    break;
    
  case ARROW_STOPPED_STATE:
    // There's not much going on when it's stopped.
    break;
  }
  
}


bool
Arrow::isInsideScreen()
{
  if (x < 0 || x > COLS - 1 || y < 0 || y > ROWS - 1) {
    return false;
  }
  return true;
}


void
Arrow::findTarget()
{
  if (direction == LEFT) {
    while (world->isFlyable(x - 1, y) && !world->isAttackable(team, x - 1, y) && isInsideScreen()) {
      x--;
    }
  } else if (direction == RIGHT) {
    while (world->isFlyable(x + 1, y) && !world->isAttackable(team, x + 1, y) && isInsideScreen()) {
      x++;
    }
  } else if (direction == UP) {
    while (world->isFlyable(x, y - 1) && !world->isAttackable(team, x, y - 1) && isInsideScreen()) {
      y--;
    }
  } else {
    while (world->isFlyable(x, y + 1) && !world->isAttackable(team, x, y + 1) && isInsideScreen()) {
      y++;
    }
  }
}


void
Arrow::setDirection(int direction)
{
  this->direction = direction;
  if (direction == UP) {
    animation = flyUpAnimation;
  } else if (direction == DOWN) {
    animation = flyDownAnimation;
  } else if (direction == LEFT) {
    animation = flyLeftAnimation;
  } else {
    animation = flyRightAnimation;
  }
}


void
Arrow::toHoldState()
{
  int visualOffset = (getTileSize() / 3) + (getTileSize() / 10);
  
  state = ARROW_HOLD_STATE;
  
  setDirection(direction);
  
  // Offset the animation a little bit to make it look like
  // the arrow is in the bow string.
  flyUpAnimation->setHorizontalOffset(0);
  flyUpAnimation->setVerticalOffset(visualOffset);
  flyDownAnimation->setHorizontalOffset(0);
  flyDownAnimation->setVerticalOffset(-visualOffset);
  flyLeftAnimation->setHorizontalOffset(visualOffset);
  flyLeftAnimation->setVerticalOffset(0);
  flyRightAnimation->setHorizontalOffset(-visualOffset);
  flyRightAnimation->setVerticalOffset(0);
}


void
Arrow::toFlyingState()
{
  state = ARROW_FLYING_STATE;
  setDirection(direction);
  findTarget();
  // Put the animation back to where it's supposed to be.
  flyUpAnimation->setHorizontalOffset(0);
  flyUpAnimation->setVerticalOffset(0);
  flyDownAnimation->setHorizontalOffset(0);
  flyDownAnimation->setVerticalOffset(0);
  flyLeftAnimation->setHorizontalOffset(0);
  flyLeftAnimation->setVerticalOffset(0);
  flyRightAnimation->setHorizontalOffset(0);
  flyRightAnimation->setVerticalOffset(0);
  play_sound(SND_ARROW_FLY);
}


void
Arrow::toStoppedState(){
  state = ARROW_STOPPED_STATE;
  setDirection(direction);
  play_sound(SND_ARROW_HIT);
}


bool
Arrow::isStopped()
{
  if (state == ARROW_STOPPED_STATE) {
    return true;
  }
  return false;
}

