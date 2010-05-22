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
#include "Screen.h"
#include "Snapshot.h"


Snapshot::Snapshot()
{
  canvas = create_bitmap(window_width(), window_height());
}


Snapshot::~Snapshot()
{
  destroy_bitmap(canvas);
}


void
Snapshot::update()
{
  if (isMoving()) {
    
    if (speed > 0) {
      
      fudge += speed;
      
      while (fudge >= GAME_TICKER) {
        if (visualX != x) {
          if (visualX < x) {
            visualX++;
          } else {
            visualX--;
          }
        }
        if (visualY != y) {
          if (visualY < y) {
            visualY++;
          } else {
            visualY--;
          }
        }
        fudge -= GAME_TICKER;
      }
      
    } else {
      visualX = x;
      visualY = y;
    }
    
    if (!isMoving()) {
      fudge = 0;
    }
    
  }
}


void
Snapshot::draw(BITMAP* buffer)
{
  draw_sprite(buffer, getCanvas(), visualX, visualY);
}


BITMAP*
Snapshot::getCanvas()
{
  return canvas;
}


bool
Snapshot::isMoving(){
  if (visualX != x || visualY != y) {
    return true;
  }
  return false;
}


void
Snapshot::setX(int x)
{
  this->x = x;
  visualX = x;
}


void
Snapshot::setY(int y)
{
  this->y = y;
  visualY = y;
}

