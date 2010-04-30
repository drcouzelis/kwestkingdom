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
#ifndef __SWORD_H
#define __SWORD_H


#include "Sprite.h"


class Sword : public Sprite
{
public:
  Sword();
  
  virtual bool isHeld();
  
  virtual void toHoldState();
  virtual void toAwayState();
  
  // Deprecated
  virtual void toAttackUpState();
  virtual void toAttackDownState();
  virtual void toAttackLeftState();
  virtual void toAttackRightState();
  
protected:
  Animation* holdAnimation;
  Animation* attackUpAnimation;
  Animation* attackDownAnimation;
  Animation* attackLeftAnimation;
  Animation* attackRightAnimation;
};


#endif // __SWORD_H
