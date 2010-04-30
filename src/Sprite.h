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
#ifndef __SPRITE_H
#define __SPRITE_H


#include <allegro.h>

#include "Animation.h"
#include "Drawable.h"
#include "Positionable.h"
#include "Updatable.h"


class World;


class Sprite
: public virtual Drawable
, public virtual Positionable
, public virtual Updatable
{
public:
  Sprite();
  
  virtual void draw(BITMAP* buffer); // Drawable
  
  virtual void update(); // Updatable
  
  virtual void setX(int x);         // Positionable
  virtual void setY(int y);         // Positionable
  virtual int  getX();              // Positionable
  virtual int  getY();              // Positionable
  virtual void moveX(int x);        // Positionable
  virtual void moveY(int y);        // Positionable
  virtual void setSpeed(int speed); // Positionable
  virtual void bound(int top, int bottom, int left, int right); // Positionable
  
  virtual bool isMoving();
  virtual int  getWidth();
  virtual int  getHeight();

  virtual void setWorld(World* world);
  virtual void setState(int state);
  
protected:
  
  /**
   * Position on the map.
   */
  int x; // Horizontal, from 0 to COLS - 1
  int y; // Vertical, from 0 to ROWS - 1
  int w; // Width of the sprite, or, how many square it occupies horizontally
  int h; // Height of the sprite
  
  /**
   * Where the image is on the screen.
   */
  int visualX; // Screen width
  int visualY; // Screen height
  int fudge;
  
  int speed; // In FPS
  
  Animation *animation;
  
  World* world;
  
  int state;
};


#endif // __SPRITE_H
