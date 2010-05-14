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
#include "Enemy.h"
#include "World.h"


Enemy::Enemy()
{
  team = ENEMY_TEAM;
  money = 1;
}


void
Enemy::dropItem()
{
  //Heart *heart;
  MoneyBag* bag;
  //int num;
  
  //num = random_number(1, 3);
  
  //if (num == 1) {
    //heart = [[Heart alloc] init];
    //[heart setX: x];
    //[heart setY: y];
    //[world addItem: heart];
  //} else {
    bag = new MoneyBag();
    bag->setX(x);
    bag->setY(y);
    bag->setAmount(money);
    world->addItem(bag);
  //}
  
}
