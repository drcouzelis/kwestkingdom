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
#include "Sprite.h"


Sprite::Sprite()
: x(0)
, y(0)
, w(0)
, h(0)
, visualX(0)
, visualY(0)
, fudge(0)
, speed(0)
, animation(NULL)
, world(NULL)
, state(0)
{
  // Empty  
}


void
Sprite::update()
{
  animation->animate();
  
  // This will make the visual position of the sprite match up
  // with the actual position of the sprite at the right speed.
  if (isMoving()) {
    
    if (speed > 0) {
      
      fudge += speed;
      
      while (fudge >= GAME_TICKER) {
        if (visualX != x * getTileSize()) {
          if (visualX < x * getTileSize()) {
            visualX++;
          } else {
            visualX--;
          }
        }
        if (visualY != y * getTileSize()) {
          if (visualY < y * getTileSize()) {
            visualY++;
          } else {
            visualY--;
          }
        }
        fudge -= GAME_TICKER;
      }
      
    } else {
      visualX = x * getTileSize();
      visualY = y * getTileSize();
    }
    
    if (!isMoving()) {
      fudge = 0;
    }
    
  }
  
}


void
Sprite::draw(BITMAP* buffer)
{
  // Add a shadow.
  /*
  hline(buffer, visualX + 6, visualY + 30, visualX + 33, BLACK);
  hline(buffer, visualX + 6, visualY + 31, visualX + 33, BLACK);
  hline(buffer, visualX + 4, visualY + 32, visualX + 35, BLACK);
  hline(buffer, visualX + 4, visualY + 33, visualX + 35, BLACK);
  hline(buffer, visualX + 6, visualY + 34, visualX + 33, BLACK);
  hline(buffer, visualX + 6, visualY + 35, visualX + 33, BLACK);
  */
  
  animation->draw(buffer, visualX, visualY);
  
}


bool
Sprite::isMoving()
{
  if (visualX != x * getTileSize() || visualY != y * getTileSize()) {
    return true;
  }
  return false;
}


void
Sprite::bound(int top, int bottom, int left, int right)
{
  if (x < left) {
    moveX(left);
  } else if (x + w - 1 > right) {
    moveX(right);
  }
  
  if (y < top) {
    moveY(top);
  } else if (y + h - 1 > bottom) {
    moveY(bottom);
  }
}


int
Sprite::getX()
{
  return x;
}


int
Sprite::getY()
{
  return y;
}


void
Sprite::setX(int x)
{
  this->x = x;
  visualX = x * getTileSize();
}


void
Sprite::setY(int y)
{
  this->y = y;
  visualY = y * getTileSize();
}


void
Sprite::moveX(int x)
{
  this->x = x;
}


void
Sprite::moveY(int y)
{
  this->y = y;
}


int
Sprite::getWidth()
{
  return w;
}


int
Sprite::getHeight()
{
  return h;
}


void
Sprite::setWorld(World* world)
{
  this->world = world;
}


void
Sprite::setState(int state)
{
  this->state = state;
}


void
Sprite::setSpeed(int speed)
{
  this->speed = speed;
}
