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
#include "Character.h"
#include "MoneyBag.h"


MoneyBag::MoneyBag()
: amount(1)
{
  animation = new Animation;
  animation->addFrame(get_image(IMG_ITEMS_MONEYBAG));
}


void
MoneyBag::collectedBy(Character* character)
{
  character->setMoney(character->getMoney() + amount);
  play_sound(SND_MONEY);
}


int
MoneyBag::getAmount()
{
  return amount;
}


void
MoneyBag::setAmount(int amount)
{
  this->amount = amount;
  if (amount < 0) {
    amount = 0;
  }
}
