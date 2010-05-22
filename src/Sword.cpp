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
#include "KwestKingdom.h"
#include "Resources.h"
#include "Sword.h"


typedef enum {
  SWORD_HOLD_STATE,
  SWORD_AWAY_STATE
} SWORD_STATE;

typedef enum {
  SWORD_ATTACK_UP_STATE,
  SWORD_ATTACK_DOWN_STATE,
  SWORD_ATTACK_LEFT_STATE,
  SWORD_ATTACK_RIGHT_STATE
} SWORD_ATTACK_STATE;


Sword::Sword()
{
  holdAnimation = new Animation(6, true);
  holdAnimation->addFrame(get_image(IMG_SWORD_HOLD_1));
  holdAnimation->addFrame(get_image(IMG_SWORD_HOLD_2));
  holdAnimation->addFrame(get_image(IMG_SWORD_HOLD_3));
  holdAnimation->addFrame(get_image(IMG_SWORD_HOLD_4));
  
  attackRightAnimation = new Animation(12, false);
  attackRightAnimation->addFrame(get_image(IMG_SWORD_STAB_1));
  attackRightAnimation->addFrame(get_image(IMG_SWORD_STAB_2));
  attackRightAnimation->addFrame(get_image(IMG_SWORD_STAB_3));
  attackRightAnimation->addFrame(get_image(IMG_SWORD_STAB_4));
  attackRightAnimation->addFrame(get_image(IMG_SWORD_STAB_3));
  attackRightAnimation->addFrame(get_image(IMG_SWORD_STAB_2));
  attackRightAnimation->addFrame(get_image(IMG_SWORD_STAB_1));
  attackRightAnimation->setHorizontalOffset(-getTileSize());
  attackRightAnimation->setVerticalOffset(-getTileSize());
  
  attackLeftAnimation = attackRightAnimation;
  attackLeftAnimation->setHorizontalFlip(true);

  attackDownAnimation = attackRightAnimation;
  attackDownAnimation->setRotate(true);

  attackUpAnimation = attackRightAnimation;
  attackUpAnimation->setHorizontalFlip(true);
  attackUpAnimation->setRotate(true);
  
  toAwayState();
}


Sword::~Sword()
{
  delete holdAnimation;
  delete attackUpAnimation;
  delete attackDownAnimation;
  delete attackLeftAnimation;
  delete attackRightAnimation;
}


void
Sword::toHoldState()
{
  state = SWORD_HOLD_STATE;
  animation = holdAnimation;
}


void
Sword::toAwayState()
{
  state = SWORD_AWAY_STATE;
  animation = NULL;
}


void
Sword::toAttackUpState()
{
  animation = attackUpAnimation;
  animation->reset();
  play_sound(SND_SWORD);
}


void
Sword::toAttackDownState()
{
  animation = attackDownAnimation;
  animation->reset();
  play_sound(SND_SWORD);
}


void
Sword::toAttackLeftState()
{
  animation = attackLeftAnimation;
  animation->reset();
  play_sound(SND_SWORD);
}


void
Sword::toAttackRightState()
{
  animation = attackRightAnimation;
  animation->reset();
  play_sound(SND_SWORD);
}


bool
Sword::isHeld(){
  if (state == SWORD_HOLD_STATE) {
    return true;
  }
  return false;
}

