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
#ifndef __BOW_H
#define __BOW_H


#include "Arrow.h"
#include "Sprite.h"


class World;


class Bow : public Sprite
{
public:
  Bow();

  virtual void   setArrow(Arrow* arrow);
  virtual Arrow* getArrow();

  virtual void setArrow(int x, int y, int direction, int team, World* world);

  virtual bool isHeld();

  // State control
  virtual void toHoldState();
  virtual void toAwayState();
  virtual void toAttackUpState();
  virtual void toAttackDownState();
  virtual void toAttackLeftState();
  virtual void toAttackRightState();

protected:
  Arrow* arrow;
  
  Animation* holdAnimation;
  Animation* attackUpAnimation;
  Animation* attackDownAnimation;
  Animation* attackLeftAnimation;
  Animation* attackRightAnimation;
};


#endif // __BOW_H
