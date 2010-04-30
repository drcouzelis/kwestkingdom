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
#ifndef __LIVABLE_H
#define __LIVABLE_H


class Livable
{
public:
  virtual bool isDead() = 0;
  virtual void setHealth(int health) = 0;
  virtual int  getHealth() = 0;
  virtual void setMaxHealth(int health) = 0;
  virtual int  getMaxHealth() = 0;
  virtual void hurt() = 0;
};


#endif // __LIVABLE_H

