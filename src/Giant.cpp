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
#include "Giant.h"
#include "World.h"


typedef enum {
  GIANT_STAND_STATE,
  GIANT_ATTACK_STATE,
  GIANT_MOVE_STATE
} GIANT_STATE;


Giant::Giant()
{
  x = 0;
  y = 0;
  
  w = 2;
  h = 2;
  
  speed = getWalkSpeed();
  maxHealth = 5;
  health = 5;
  team = ENEMY_TEAM;
  
  hammer = new Hammer();
  hammer->setSpeed(speed);
  hammer->setState(HAMMER_HOLD_STATE);
    
  standAnimation = new Animation(3, true);
  standAnimation->addFrame(get_image(IMG_GIANT_1));
  standAnimation->addFrame(get_image(IMG_GIANT_2));
  standAnimation->addFrame(get_image(IMG_GIANT_3));
  standAnimation->addFrame(get_image(IMG_GIANT_2));
  
  attackAnimation = new Animation(24, false);
  attackAnimation->addFrame(get_image(IMG_GIANT_1));
  attackAnimation->addFrame(get_image(IMG_GIANT_2));
  attackAnimation->addFrame(get_image(IMG_GIANT_2));
  attackAnimation->addFrame(get_image(IMG_GIANT_3));
  attackAnimation->addFrame(get_image(IMG_GIANT_3));
  attackAnimation->addFrame(get_image(IMG_GIANT_3));
  attackAnimation->addFrame(get_image(IMG_GIANT_3));
  attackAnimation->addFrame(get_image(IMG_GIANT_3));
  attackAnimation->addFrame(get_image(IMG_GIANT_2));
  attackAnimation->addFrame(get_image(IMG_GIANT_2));
  
  animation = standAnimation;
  state = GIANT_STAND_STATE;
  setMoney(5);
  
  wait();
}


Giant::~Giant()
{
  delete hammer;
  delete standAnimation;
  delete attackAnimation;
}


bool
Giant::inRange(Positionable* target, int range)
{
  if (
    abs(x - target->getX()) + abs(y - target->getY()) <= range ||
    abs(x + 1 - target->getX()) + abs(y - target->getY()) <= range ||
    abs(x - target->getX()) + abs(y + 1 - target->getY()) <= range ||
    abs(x + 1 - target->getX()) + abs(y + 1 - target->getY()) <= range
  ) {
    
    return true;
    
  }
  
  return false;
}


int
Giant::directionToTarget(Positionable* target)
{
  if ( // Up
    (x == target->getX() && y == target->getY() + 1) ||
    (x + 1 == target->getX() && y == target->getY() + 1)
  ) {
    
    return UP;
    
  } else if ( // Down
    (x == target->getX() && y == target->getY() - 2) ||
    (x + 1 == target->getX() && y == target->getY() - 2)
  ) {
    
    return DOWN;
    
  } else if ( // Left
    (x == target->getX() + 1 && y == target->getY()) ||
    (x == target->getX() + 1 && y + 1 == target->getY())
  ) {
    
    return LEFT;
    
  } else if ( // Right
    (x == target->getX() - 2 && y == target->getY()) ||
    (x == target->getX() - 2 && y + 1 == target->getY())
  ) {
    
    return RIGHT;
    
  }
  
  return UP;
  
}


bool
Giant::isMe(int x, int y)
{
  if (
    (this->x == x && this->y == y) ||
    (this->x + 1 == x && this->y == y) ||
    (this->x == x && this->y + 1 == y) ||
    (this->x + 1 == x && this->y + 1 == y)
  ) {
    
    return true;
    
  }
  
  return false;
  
}


bool
Giant::canWalkTo(int x, int y)
{
  if (
    !world->isWalkable(x, y) ||
    !world->isWalkable(x + 1, y) ||
    !world->isWalkable(x, y + 1) ||
    !world->isWalkable(x + 1, y + 1) ||
    (world->isInhabited(x, y) && !isMe(x, y)) ||
    (world->isInhabited(x + 1, y) && !isMe(x + 1, y)) ||
    (world->isInhabited(x, y + 1) && !isMe(x, y + 1)) ||
    (world->isInhabited(x + 1, y + 1) && !isMe(x + 1, y + 1))
  ) {
    
    return false;
    
  }
  
  return true;
  
}


void
Giant::update()
{
  int dir;
  int toX;
  int toY;
  Positionable* target;
  
  Enemy::update();
  hammer->update();
  
  if (isWaiting()) {
    return;
  }
  
  if (health == 0) {
    return;
  }
  
  target = world->getTarget();
  
  switch (state) {
  
  case GIANT_STAND_STATE:
    
    // If the target has a walking distance of one...
    if (inRange(target, 1)) {
      
      state = GIANT_ATTACK_STATE;
      animation = attackAnimation;
      animation->reset();
      
      // Change the state of the hammer.
      if (directionToTarget(target) == UP) {
        hammer->setState(HAMMER_ATTACK_UP_STATE);
      } else if (directionToTarget(target) == DOWN) {
        hammer->setState(HAMMER_ATTACK_DOWN_STATE);
      } else if (directionToTarget(target) == LEFT) {
        hammer->setState(HAMMER_ATTACK_LEFT_STATE);
      } else if (directionToTarget(target) == RIGHT) {
        hammer->setState(HAMMER_ATTACK_RIGHT_STATE);
      }
      
    } else if (/* Hero is nearby */ false) {
      
      // Then chase the hero!
      
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
      
      if (canWalkTo(toX, toY)) {
        
        moveX(toX);
        moveY(toY);
        state = GIANT_MOVE_STATE;
        
      }
      
      wait();
      
    }
    
    // Bound him so he doesn't wander right out of the screen!
    bound(1, ROWS - 2, 1, COLS - 2);
    
    break;
    
  case GIANT_MOVE_STATE:
    if (!isMoving()) {
      state = GIANT_STAND_STATE;
    }
    break;
    
  case GIANT_ATTACK_STATE:
    if (animation->isFinished()) {
      // Send the hero soaring!
      world->attack(team, target->getX(), target->getY());
      
      state = GIANT_STAND_STATE;
      animation = standAnimation;
      animation->reset();
      hammer->setState(HAMMER_HOLD_STATE);
      wait();
    }
    break;
    
  }
  
}


void
Giant::draw(BITMAP* buffer)
{
  Enemy::draw(buffer);
  hammer->draw(buffer);
}


void
Giant::setX(int x)
{
  Enemy::setX(x);
  hammer->setX(x);
}


void
Giant::setY(int y)
{
  Enemy::setY(y);
  hammer->setY(y);
}


void
Giant::moveX(int x)
{
  Enemy::moveX(x);
  hammer->moveX(x);
}


void
Giant::moveY(int y)
{
  Enemy::moveY(y);
  hammer->moveY(y);
}


void
Giant::dropItem()
{
  y++;
  Enemy::dropItem();
  y--;
}


void
Giant::setWorld(World* world)
{
  this->world = world;
  hammer->setWorld(world);
}

