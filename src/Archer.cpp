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
#include "Archer.h"
#include "World.h"


typedef enum {
  ARCHER_STAND_STATE,
  ARCHER_ATTACK_STATE,
  ARCHER_MOVE_STATE,
  ARCHER_DRAW_BOW_STATE,
  ARCHER_SHOOT_ARROW_STATE
} ARCHER_STATE;


Archer::Archer()
{
  x = 0;
  y = 0;
  
  speed = getWalkSpeed();
  team = ENEMY_TEAM;
  
  bow = new Bow();
  bow->setSpeed(speed);
  bow->toHoldState();
  
  standAnimation = new Animation(3, true);
  standAnimation->addFrame(get_image(IMG_ARCHER_1));
  standAnimation->addFrame(get_image(IMG_ARCHER_2));
  standAnimation->addFrame(get_image(IMG_ARCHER_3));
  standAnimation->addFrame(get_image(IMG_ARCHER_2));
  
  beginAttackAnimation = new Animation(12, false);
  beginAttackAnimation->addFrame(get_image(IMG_ARCHER_1));
  beginAttackAnimation->addFrame(get_image(IMG_ARCHER_2));
  beginAttackAnimation->addFrame(get_image(IMG_ARCHER_2));
  beginAttackAnimation->addFrame(get_image(IMG_ARCHER_3));
  
  endAttackAnimation = new Animation(12, false);
  endAttackAnimation->addFrame(get_image(IMG_ARCHER_3));
  endAttackAnimation->addFrame(get_image(IMG_ARCHER_2));
  endAttackAnimation->addFrame(get_image(IMG_ARCHER_2));
  
  animation = standAnimation;
  state = ARCHER_STAND_STATE;
  direction = UP;
  
  wait();
}


Archer::~Archer()
{
  delete bow;
  delete standAnimation;
  delete beginAttackAnimation;
  delete endAttackAnimation;
}


void
Archer::update()
{
  int dir;
  int toX;
  int toY;
  Positionable* target;
  
  Sprite::update();
  bow->update();
  
  if (isWaiting()) {
    return;
  }
  
  if (health == 0) {
    return;
  }
  
  target = world->getTarget();
  
  switch (state) {
  
  case ARCHER_STAND_STATE:
    
    if (x == target->getX()) {
      
      if (y > target->getY()) { // Hero is up.
        direction = UP;
      } else { // Hero is down.
        direction = DOWN;
      }
      
      toDrawBowState();
      wait();
      
    } else if (y == target->getY()) {
      
      if (x > target->getX()) { // Hero is left.
        direction = LEFT;
      } else { // Hero is right.
        direction = RIGHT;
      }
      
      toDrawBowState();
      wait();
      
    } else if ((x == target->getX() - 1 || x == target->getX() + 1) && random_number(0, 1) == 1) {
      
      if (y > target->getY()) { // Hero is up.
        direction = UP;
      } else { // Hero is down.
        direction = DOWN;
      }
      
      toDrawBowState();
      wait();
      
    } else if ((y == target->getY() - 1 || y == target->getY() + 1) && random_number(0, 1) == 1) {
      
      if (x > target->getX()) { // Hero is left.
        direction = LEFT;
      } else { // Hero is right.
        direction = RIGHT;
      }
      
      toDrawBowState();
      wait();
      
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
        toMoveState();
      }
      
      wait();
      
    }
    
    // Bound him so he doesn't wander right out of the screen!
    bound(1, ROWS - 2, 1, COLS - 2);
    
    break;
    
  case ARCHER_MOVE_STATE:
    if (!isMoving()) {
      toStandState();
    }
    break;
    
  case ARCHER_DRAW_BOW_STATE:
    if (animation->isFinished()) {
      toShootArrowState();
    }
    break;
    
  case ARCHER_SHOOT_ARROW_STATE:
    if (animation->isFinished()) {
      animation = standAnimation;
      bow->toHoldState();
    }
    if (bow->getArrow()->isStopped()) {
      delete bow->getArrow();
      bow->setArrow(NULL);
      toStandState();
      wait();
    }
    break;
    
  }
  
}


void
Archer::draw(BITMAP* buffer)
{
  Sprite::draw(buffer);
  bow->draw(buffer);
}


void
Archer::toStandState()
{
  state = ARCHER_STAND_STATE;
  animation = standAnimation;
}


void
Archer::toMoveState()
{
  state = ARCHER_MOVE_STATE;
  animation = standAnimation;
}


void
Archer::toDrawBowState()
{
  state = ARCHER_DRAW_BOW_STATE;
  animation = beginAttackAnimation;
  animation->reset();
  
  switch (direction) {
  case UP:
    bow->toAttackUpState();
    break;
  case DOWN:
    bow->toAttackDownState();
    break;
  case LEFT:
    bow->toAttackLeftState();
    break;
  case RIGHT:
    bow->toAttackRightState();
    break;
  }
  
  bow->setArrow(x, y, direction, team, world);
  
}


void
Archer::toShootArrowState()
{
  state = ARCHER_SHOOT_ARROW_STATE;
  animation = endAttackAnimation;
  animation->reset();
  bow->getArrow()->toFlyingState();
  bow->toHoldState();
}


void
Archer::setX(int x)
{
  Sprite::setX(x);
  bow->setX(x);
}


void
Archer::setY(int y)
{
  Sprite::setY(y);
  bow->setY(y);
}


void
Archer::moveX(int x)
{
  Sprite::moveX(x);
  bow->moveX(x);
}


void
Archer::moveY(int y)
{
  Sprite::moveY(y);
  bow->moveY(y);
}
