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
#ifndef __HAMMER_H
#define __HAMMER_H


#include "Sprite.h"


typedef enum {

  HAMMER_HOLD_STATE,
  HAMMER_AWAY_STATE,

  HAMMER_ATTACK_UP_STATE,
  HAMMER_ATTACK_DOWN_STATE,
  HAMMER_ATTACK_LEFT_STATE,
  HAMMER_ATTACK_RIGHT_STATE,

  HAMMER_END_ATTACK_STATE

} HAMMER_STATE;


class Hammer : public Sprite
{
public:
  Hammer();

  virtual bool isHeld();
  
protected:
  Animation* holdAnimation;
  Animation* attackUpAnimation;
  Animation* attackDownAnimation;
  Animation* attackLeftAnimation;
  Animation* attackRightAnimation;
  
};


#endif // __HAMMER_H
