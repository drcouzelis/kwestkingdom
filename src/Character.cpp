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


Character::Character()
  : health(1),
    maxHealth(3),
    money(0),
    team(NO_TEAM),
    turns(0)
{
  setSpeed(getWalkSpeed());
}


bool
Character::isDead()
{
  if (health == 0) {
    return true;
  }
  return false;
}


void
Character::setHealth(int health)
{
  this->health = health;
  if (this->health < 0) {
    this->health = 0;
  } else if (this->health > maxHealth) {
    this->health = maxHealth;
  }
}


int
Character::getHealth()
{
  return health;
}


void
Character::setMaxHealth(int health) {
  maxHealth = health;
}


int
Character::getMaxHealth()
{
  return maxHealth;
}


void
Character::hurt()
{
  health--;
  if (health < 0) {
    health = 0;
  }
}


bool
Character::isWaiting()
{
  if (turns > 0) {
    return true;
  }
  return false;
}


void
Character::go()
{
  turns--;
  if (turns < 0) {
    turns = 0;
  }
}


void
Character::wait()
{
  turns++;
}


void
Character::setTeam(int team)
{
  this->team = team;
}


int
Character::getTeam()
{
  return team;
}


int
Character::getMoney()
{
  return money;
}


void
Character::setMoney(int amount)
{
  money = amount;
  if (money < 0) {
    money = 0;
  } else if (money > 999) {
    money = 999;
  }
}
