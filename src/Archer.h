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
#ifndef __ARCHER_H
#define __ARCHER_H


#include "Bow.h"
#include "Enemy.h"
#include "Resources.h"


class Archer : public Enemy
{
public:
  Archer();
  ~Archer();
  
  virtual void draw(BITMAP* buffer); // Drawable
  
  virtual void setX(int x);  // Positionable
  virtual void setY(int y);  // Positionable
  virtual void moveX(int x); // Positionable
  virtual void moveY(int y); // Positionable
  
  virtual void update(); // Updatable
  
  // State control
  virtual void toStandState();
  virtual void toMoveState();
  virtual void toDrawBowState();
  virtual void toShootArrowState();
  
protected:
  Bow* bow;
  
  Animation* standAnimation;
  Animation* beginAttackAnimation;
  Animation* endAttackAnimation;
  
  int direction;
};


#endif // __ARCHER_H
