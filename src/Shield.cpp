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
#include "Resources.h"
#include "Shield.h"


typedef enum {
  SHIELD_HOLD_STATE,
  SHIELD_AWAY_STATE
} SHIELD_STATE;


Shield::Shield()
{
  holdAnimation = new Animation(6, true);
  holdAnimation->addFrame(get_image(IMG_SHIELD_1));
  holdAnimation->addFrame(get_image(IMG_SHIELD_2));
  holdAnimation->addFrame(get_image(IMG_SHIELD_3));
  holdAnimation->addFrame(get_image(IMG_SHIELD_4));

  toAwayState();
}


Shield::~Shield()
{
  delete holdAnimation;
}


void
Shield::toHoldState()
{
  state = SHIELD_HOLD_STATE;
  animation = holdAnimation;
}


void
Shield::toAwayState()
{
  state = SHIELD_AWAY_STATE;
  animation = NULL;
}


bool
Shield::isHeld()
{
  if (state == SHIELD_HOLD_STATE) {
    return true;
  }
  return false;
}

