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
#ifndef __HERO_H
#define __HERO_H


#include "Arrow.h"
#include "Bow.h"
#include "Character.h"
#include "KeyControl.h"
#include "Resources.h"
#include "Shield.h"
#include "Sword.h"


#define MAX_HERO_HEALTH 3


class World;


class Hero : public Character
{
public:
  Hero();
  ~Hero();
  
  virtual void draw(BITMAP* buffer); // Drawable
  
  virtual bool isDead();                 // Livable
  //virtual void setHealth(int health);    // Livable
  //virtual int  getHealth();              // Livable
  //virtual void setMaxHealth(int health); // Livable
  //virtual int  getMaxHealth();           // Livable
  virtual void hurt();                   // Livable
  
  virtual void setX(int x);         // Positionable
  virtual void setY(int y);         // Positionable
  //virtual int  getX();              // Positionable
  //virtual int  getY();              // Positionable
  virtual void moveX(int x);        // Positionable
  virtual void moveY(int y);        // Positionable
  
  virtual void update(); // Updatable
  
  virtual void emptyHands();
  
  // Updates
  virtual void updateStandState();
  
  // State control
  virtual void toStandState();
  virtual void toMoveState();
  virtual void toAttackState();
  virtual void toHurtState();
  virtual void toDeadState();
  virtual void toPushSwordState();
  virtual void toPullSwordState();
  virtual void toDrawBowState();
  virtual void toShootArrowState();

protected:
  Shield shield;
  Sword sword;
  Bow bow;
  
  Animation* standAnimation;
  Animation* beginAttackAnimation;
  Animation* endAttackAnimation;
  Animation* hurtAnimation;
  Animation* deadAnimation;
  
  KeyControl upKey;
  KeyControl downKey;
  KeyControl rightKey;
  KeyControl leftKey;
  KeyControl waitKey;
  KeyControl attackKey;
  KeyControl handKey;
  KeyControl shieldKey;
  KeyControl swordKey;
  KeyControl bowKey;
  
  int direction;
};


#endif // __HERO_H
