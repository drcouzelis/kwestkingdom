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
#ifndef __CHARACTER_H
#define __CHARACTER_H


#include "Livable.h"
#include "KwestKingdom.h"
#include "Moneyable.h"
#include "MoneyBag.h"
#include "Screen.h"
#include "Sprite.h"
#include "Targetable.h"


typedef enum {
  NO_TEAM,
  HERO_TEAM,
  ENEMY_TEAM
} TEAM;


class Character : public Sprite, public virtual Livable, public virtual Moneyable
{
public:
  Character();
  
  virtual bool isDead();                 // Livable
  virtual void setHealth(int health);    // Livable
  virtual int  getHealth();              // Livable
  virtual void setMaxHealth(int health); // Livable
  virtual int  getMaxHealth();           // Livable
  virtual void hurt();                   // Livable
  
  virtual int  getMoney();           // Moneyable
  virtual void setMoney(int amount); // Moneyable
  
  virtual bool isWaiting();
  virtual void wait();
  virtual void go();

  virtual void setTeam(int team);
  virtual int  getTeam();
  
protected:  
  int health;
  int maxHealth;
  int money;
  int team; // Characters on the same team can't hurt each other.
  
  int turns;
};


#endif // __CHARACTER_H
