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
#ifndef __SNAPSHOT_H
#define __SNAPSHOT_H


#include <allegro.h>

#include "Sprite.h"


class Snapshot : public Sprite
{
public:
  Snapshot();
  ~Snapshot();
  
  virtual void draw(BITMAP* buffer); // Drawable

  virtual void setX(int x); // Positionable
  virtual void setY(int y); // Positionable

  virtual bool isMoving(); // Sprite

  virtual void update(); // Updatable

  BITMAP* getCanvas();
  
protected:
  BITMAP* canvas;
};


#endif // __SNAPSHOT_H
