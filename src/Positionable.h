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
#ifndef __POSITIONABLE_H
#define __POSITIONABLE_H


class Positionable
{
public:
  virtual void setX(int x) = 0;
  virtual void setY(int y) = 0;
  virtual int  getX() = 0;
  virtual int  getY() = 0;
  virtual void moveX(int x) = 0;
  virtual void moveY(int y) = 0;
  virtual void setSpeed(int speed) = 0;
  virtual void bound(int top, int bottom, int left, int right) = 0;
};


#endif // __POSITIONABLE_H
