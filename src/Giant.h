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
#ifndef __GIANT_H
#define __GIANT_H


#include "Enemy.h"
#include "Hammer.h"


class Giant : public Enemy
{
public:
  Giant();
  ~Giant();

  virtual void draw(BITMAP* buffer); // Drawable
  
  virtual void dropItem(); // Enemy
  
  virtual void setX(int x);  // Positionable
  virtual void setY(int y);  // Positionable
  virtual void moveX(int x); // Positionable
  virtual void moveY(int y); // Positionable
  
  virtual void setWorld(World* world); // Sprite
  
  virtual void update(); // Updatable
  
  virtual bool inRange(Positionable* target, int range);
  virtual int  directionToTarget(Positionable* target);
  virtual bool isMe(int x, int y);
  virtual bool canWalkTo(int x, int y);
  
protected:
  Hammer* hammer;
  
  Animation* standAnimation;
  Animation* attackAnimation;
};


#endif // __GIANT_H
