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
#include "Hammer.h"
#include "World.h"


Hammer::Hammer()
{
  holdAnimation = new Animation(6, true);
  holdAnimation->addFrame(get_image(IMG_HAMMER_HOLD_1));
  holdAnimation->addFrame(get_image(IMG_HAMMER_HOLD_2));
  holdAnimation->addFrame(get_image(IMG_HAMMER_HOLD_3));
  holdAnimation->addFrame(get_image(IMG_HAMMER_HOLD_4));
  holdAnimation->setVerticalOffset(TILE_SIZE);
  
  attackRightAnimation = new Animation(24, false);
  attackRightAnimation->addFrame(get_image(IMG_HAMMER_SWING_1));
  attackRightAnimation->addFrame(get_image(IMG_HAMMER_SWING_2));
  attackRightAnimation->addFrame(get_image(IMG_HAMMER_SWING_3));
  attackRightAnimation->addFrame(get_image(IMG_HAMMER_SWING_4));
  attackRightAnimation->addFrame(get_image(IMG_HAMMER_SWING_4));
  attackRightAnimation->addFrame(get_image(IMG_HAMMER_SWING_4));
  attackRightAnimation->addFrame(get_image(IMG_HAMMER_SWING_4));
  attackRightAnimation->addFrame(get_image(IMG_HAMMER_SWING_3));
  attackRightAnimation->addFrame(get_image(IMG_HAMMER_SWING_2));
  attackRightAnimation->addFrame(get_image(IMG_HAMMER_SWING_1));
  attackRightAnimation->setHorizontalOffset(TILE_SIZE);
  
  attackLeftAnimation = attackRightAnimation;
  attackLeftAnimation->setHorizontalFlip(true);
  attackLeftAnimation->setHorizontalOffset(-TILE_SIZE * 2);

  attackDownAnimation = attackRightAnimation;
  attackDownAnimation->setRotate(true);
  attackDownAnimation->setHorizontalOffset(0);
  attackDownAnimation->setVerticalOffset(TILE_SIZE);

  attackUpAnimation = attackRightAnimation;
  attackUpAnimation->setHorizontalFlip(true);
  attackUpAnimation->setVerticalFlip(true);
  attackUpAnimation->setRotate(true);
  attackUpAnimation->setHorizontalOffset(-TILE_SIZE);
  attackUpAnimation->setVerticalOffset(-TILE_SIZE * 2);
  
  setState(HAMMER_AWAY_STATE);
}


Hammer::~Hammer()
{
  delete holdAnimation; 
  delete attackUpAnimation; 
  delete attackDownAnimation; 
  delete attackLeftAnimation; 
  delete attackRightAnimation; 
}


void
Hammer::update()
{
  Sprite::update();
  
  switch (state) {
  case HAMMER_ATTACK_UP_STATE:
  case HAMMER_ATTACK_DOWN_STATE:
  case HAMMER_ATTACK_LEFT_STATE:
  case HAMMER_ATTACK_RIGHT_STATE:
    if (animation->getCurrentFrameNumber() == 3) {
      setState(HAMMER_END_ATTACK_STATE);
    }
    break;
  }
}


void
Hammer::setState(int state)
{
  this->state = state;
  
  switch (state) {
  
  case HAMMER_HOLD_STATE:
    animation = holdAnimation;
    break;
    
  case HAMMER_AWAY_STATE:
    animation = NULL;
    break;
    
  case HAMMER_ATTACK_UP_STATE:
    animation = attackUpAnimation;
    animation->reset();
    break;
    
  case HAMMER_ATTACK_DOWN_STATE:
    animation = attackDownAnimation;
    animation->reset();
    break;
    
  case HAMMER_ATTACK_LEFT_STATE:
    animation = attackLeftAnimation;
    animation->reset();
    break;
    
  case HAMMER_ATTACK_RIGHT_STATE:
    animation = attackRightAnimation;
    animation->reset();
    break;
    
  case HAMMER_END_ATTACK_STATE:
    play_sound(SND_HAMMER);
    world->shake();
    break;
    
  }
}


bool
Hammer::isHeld()
{
  if (state == HAMMER_HOLD_STATE) {
    return true;
  }
  return false;
}

