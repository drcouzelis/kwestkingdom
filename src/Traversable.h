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
#ifndef __TRAVERSABLE_H
#define __TRAVERSABLE_H


class Traversable
{
public:
  virtual bool isSwimmable(int x, int y) = 0;
  virtual bool isWalkable(int x, int y) = 0;
  virtual bool isJumpable(int x, int y) = 0;
  virtual bool isFlyable(int x, int y) = 0;
  virtual bool isSoarable(int x, int y) = 0;
};


#endif // __TRAVERSABLE
