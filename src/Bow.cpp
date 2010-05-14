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
#include "Bow.h"


typedef enum {
  BOW_HOLD_STATE,
  BOW_AWAY_STATE
} BOW_STATE;


Bow::Bow()
{
  arrow = NULL;
  
  holdAnimation = new Animation(6, true);
  holdAnimation->addFrame(get_image(IMG_BOW_HOLD_1));
  holdAnimation->addFrame(get_image(IMG_BOW_HOLD_2));
  holdAnimation->addFrame(get_image(IMG_BOW_HOLD_3));
  holdAnimation->addFrame(get_image(IMG_BOW_HOLD_4));
  
  attackRightAnimation = new Animation(12, false);
  attackRightAnimation->addFrame(get_image(IMG_BOW_DRAW_1));
  attackRightAnimation->addFrame(get_image(IMG_BOW_DRAW_2));
  attackRightAnimation->addFrame(get_image(IMG_BOW_DRAW_3));
  
  attackLeftAnimation = attackRightAnimation;
  attackLeftAnimation->setHorizontalFlip(true);
  
  attackDownAnimation = attackRightAnimation;
  attackDownAnimation->setRotate(true);
  
  attackUpAnimation = attackRightAnimation;
  attackUpAnimation->setHorizontalFlip(true);
  attackUpAnimation->setRotate(true);
  
  toAwayState();
}


Bow::~Bow()
{
  delete holdAnimation;
  delete attackUpAnimation;
  delete attackDownAnimation;
  delete attackLeftAnimation;
  delete attackRightAnimation;
  delete arrow;
}


void
Bow::update()
{
  Sprite::update();
  arrow->update();
}


void
Bow::draw(BITMAP* buffer)
{
  Sprite::draw(buffer);
  arrow->draw(buffer);
}


void
Bow::setArrow(Arrow* arrow)
{
  this->arrow = arrow;
}


Arrow*
Bow::getArrow()
{
  return arrow;
}


void
Bow::setArrow(int x, int y, int direction, int team, World* world)
{
  arrow = new Arrow();
  arrow->setTeam(team);
  arrow->setX(x);
  arrow->setY(y);
  arrow->setWorld(world);
  arrow->setDirection(direction);
  arrow->toHoldState();
}


void
Bow::toHoldState()
{
  state = BOW_HOLD_STATE;
  animation = holdAnimation;
}


void
Bow::toAwayState()
{
  state = BOW_AWAY_STATE;
  animation = NULL;
}


void
Bow::toAttackUpState(){
  animation = attackUpAnimation;
  animation->reset();
}


void
Bow::toAttackDownState()
{
  animation = attackDownAnimation;
  animation->reset();
}


void
Bow::toAttackLeftState()
{
  animation = attackLeftAnimation;
  animation->reset();
}


void
Bow::toAttackRightState()
{
  animation = attackRightAnimation;
  animation->reset();
}


bool
Bow::isHeld()
{
  if (state != BOW_AWAY_STATE) {
    return true;
  }
  return false;
}
