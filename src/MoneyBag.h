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
#ifndef __MONEY_BAG_H
#define __MONEY_BAG_H


#include "Collectable.h"
#include "Resources.h"
#include "Sprite.h"


class MoneyBag : public Sprite, public virtual Collectable
{
public:
  MoneyBag();
  
  virtual void collectedBy(Character* character); // Collectable
  
  virtual int  getAmount();
  virtual void setAmount(int amount);

protected:
  int amount;
};


#endif // __MONEY_BAG_H
