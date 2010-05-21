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
#include "Ninja.h"
#include "World.h"


typedef enum {
  NINJA_STAND_STATE,
  NINJA_ATTACK_STATE,
  NINJA_MOVE_STATE,
  NINJA_DASH_STATE
} NINJA_STATE;


Ninja::Ninja()
{
  x = 0;
  y = 0;
  
  setSpeed(getWalkSpeed());
  team = ENEMY_TEAM;
  
  //sword = [[Sword alloc] init];
  sword.setSpeed(speed);
  sword.toHoldState();
  
  standAnimation = new Animation(6, true);
  standAnimation->addFrame(get_image(IMG_NINJA_1));
  standAnimation->addFrame(get_image(IMG_NINJA_2));
  standAnimation->addFrame(get_image(IMG_NINJA_3));
  standAnimation->addFrame(get_image(IMG_NINJA_2));
  
  dashAnimation = standAnimation;
  dashAnimation->setSpeed(24);
  
  attackAnimation = new Animation(12, false);
  attackAnimation->addFrame(get_image(IMG_NINJA_1));
  attackAnimation->addFrame(get_image(IMG_NINJA_2));
  attackAnimation->addFrame(get_image(IMG_NINJA_2));
  attackAnimation->addFrame(get_image(IMG_NINJA_3));
  attackAnimation->addFrame(get_image(IMG_NINJA_3));
  attackAnimation->addFrame(get_image(IMG_NINJA_2));
  attackAnimation->addFrame(get_image(IMG_NINJA_2));
  
  animation = standAnimation;
  state = NINJA_STAND_STATE;
  wait();
}


Ninja::~Ninja()
{
  delete standAnimation;
  delete dashAnimation;
  delete attackAnimation;
}


void
Ninja::update()
{
  int dir;
  int toX;
  int toY;
  Positionable* target;
  
  Enemy::update();
  sword.update();
  
  if (isWaiting()) {
    return;
  }
  
  if (health == 0) {
    return;
  }
  
  target = world->getTarget();

  switch (state) {
  
  case NINJA_STAND_STATE:
    
    // If the target has a walking distance of one...
    if (abs(x - target->getX()) + abs(y - target->getY()) == 1) {
      
      state = NINJA_ATTACK_STATE;
      animation = attackAnimation;
      animation->reset();
      // Change the state of the sword.
      if (x == target->getX() && y == target->getY() + 1) { // Up
        sword.toAttackUpState();
      } else if (x == target->getX() && y == target->getY() - 1) { // Down
        sword.toAttackDownState();
      } else if (x == target->getX() + 1 && y == target->getY()) { // Left
        sword.toAttackLeftState();
      } else if (x == target->getX() - 1 && y == target->getY()) { // Right
        sword.toAttackRightState();
      }
      
    } else if (x == target->getX()) {
      
      if (y > target->getY()) { // Hero is directly up.
        while (y - 1 != target->getY() && world->isWalkable(x, y - 1) && !world->isInhabited(x, y - 1)) {
          moveY(y - 1);
        }
      } else { // Hero is directly down.
        while (y + 1 != target->getY() && world->isWalkable(x, y + 1) && !world->isInhabited(x, y + 1)) {
          moveY(y + 1);
        }
      }
      
      state = NINJA_DASH_STATE;
      setSpeed(getWalkSpeed() + (getWalkSpeed() / 5));
      animation = dashAnimation;
      animation->reset();
      
    } else if (y == target->getY()) {
      
      if (x > target->getX()) { // Hero is directly left.
        while (x - 1 != target->getX() && world->isWalkable(x - 1, y) && !world->isInhabited(x - 1, y)) {
          moveX(x - 1);
        }
      } else { // Hero is directly right.
        while (x + 1 != target->getX() && world->isWalkable(x + 1, y) && !world->isInhabited(x + 1, y)) {
          moveX(x + 1);
        }
      }
      
      state = NINJA_DASH_STATE;
      setSpeed(getWalkSpeed() + (getWalkSpeed() / 5));
      animation = dashAnimation;
      animation->reset();
      
    } else {
      
      // Wander aimlessly
      dir = random_number(UP, /*DOWN, LEFT,*/ RIGHT);
      
      toX = x;
      toY = y;
      
      if (dir == UP) {
        toY--;
      } else if (dir == DOWN) {
        toY++;
      } else if (dir == RIGHT) {
        toX++;
      } else if (dir == LEFT) {
        toX--;
      }
      
      if (world->isWalkable(toX, toY) && !world->isInhabited(toX, toY)) {
        moveX(toX);
        moveY(toY);
        state = NINJA_MOVE_STATE;
      }
      
      wait();
      
    }
    
    // Bound him so he doesn't wander right out of the screen!
    bound(1, ROWS - 2, 1, COLS - 2);
    
    break;
    
  case NINJA_MOVE_STATE:
    if (!isMoving()) {
      state = NINJA_STAND_STATE;
    }
    break;
    
  case NINJA_DASH_STATE:
    if (!isMoving()) {
      setSpeed(getWalkSpeed());
      // If the target has a walking distance of one...
      if (abs(x - target->getX()) + abs(y - target->getY()) == 1) {
        state = NINJA_ATTACK_STATE;
        animation = attackAnimation;
        animation->reset();
        // Change the state of the sword.
        if (x == target->getX() && y == target->getY() + 1) { // Up
          sword.toAttackUpState();
        } else if (x == target->getX() && y == target->getY() - 1) { // Down
          sword.toAttackDownState();
        } else if (x == target->getX() + 1 && y == target->getY()) { // Left
          sword.toAttackLeftState();
        } else if (x == target->getX() - 1 && y == target->getY()) { // Right
          sword.toAttackRightState();
        }
      } else {
        state = NINJA_STAND_STATE;
        animation = standAnimation;
        animation->reset();
        wait();
      }
    }
    break;
    
  case NINJA_ATTACK_STATE:
    if (animation->isFinished()) {
      world->attack(team, target->getX(), target->getY());
      state = NINJA_STAND_STATE;
      animation = standAnimation;
      animation->reset();
      sword.toHoldState();
      wait();
    }
	break;
	
  }
  
}


void
Ninja::draw(BITMAP* buffer)
{
  Enemy::draw(buffer);
  sword.draw(buffer);
}


void
Ninja::setX(int x)
{
  Enemy::setX(x);
  sword.setX(x);
}


void
Ninja::setY(int y)
{
  Enemy::setY(y);
  sword.setY(y);
}


void
Ninja::moveX(int x)
{
  Enemy::moveX(x);
  sword.moveX(x);
}


void
Ninja::moveY(int y)
{
  Enemy::moveY(y);
  sword.moveY(y);
}


void
Ninja::setSpeed(int speed)
{
  this->speed = speed;
  sword.setSpeed(speed);
}
