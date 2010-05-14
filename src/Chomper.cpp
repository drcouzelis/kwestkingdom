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
#include "Chomper.h"
#include "World.h"


typedef enum {
  CHOMPER_STAND_STATE,
  CHOMPER_ATTACK_STATE,
  CHOMPER_MOVE_STATE
} CHOMPER_STATE;


Chomper::Chomper()
{
  prevDirection = UP;
  
  standAnimation = new Animation(6, true);
  standAnimation->addFrame(get_image(IMG_CHOMPER_STAND_1));
  standAnimation->addFrame(get_image(IMG_CHOMPER_STAND_2));
  standAnimation->addFrame(get_image(IMG_CHOMPER_STAND_3));
  standAnimation->addFrame(get_image(IMG_CHOMPER_STAND_2));
  
  attackAnimation = new Animation(20, false);
  attackAnimation->addFrame(get_image(IMG_CHOMPER_BITE_1));
  attackAnimation->addFrame(get_image(IMG_CHOMPER_BITE_2));
  attackAnimation->addFrame(get_image(IMG_CHOMPER_BITE_3));
  attackAnimation->addFrame(get_image(IMG_CHOMPER_BITE_4));
  attackAnimation->addFrame(get_image(IMG_CHOMPER_BITE_5));
  attackAnimation->addFrame(get_image(IMG_CHOMPER_BITE_4));
  attackAnimation->addFrame(get_image(IMG_CHOMPER_BITE_3));
  attackAnimation->addFrame(get_image(IMG_CHOMPER_BITE_2));
  attackAnimation->addFrame(get_image(IMG_CHOMPER_BITE_1));
  
  animation = standAnimation;
  state = CHOMPER_STAND_STATE;
  
  wait();
}


Chomper::~Chomper()
{
  delete standAnimation;
  delete attackAnimation;
}


void
Chomper::update()
{
  int dir;
  int toX;
  int toY;
  Positionable* target;
  
  Enemy::update();
  
  if (isWaiting()) {
    return;
  }
  
  if (health == 0) {
    return;
  }
  
  target = world->getTarget();
  
  switch (state) {
  
  case CHOMPER_STAND_STATE:
    
    // If the target has a walking distance of one...
    if (abs(x - target->getX()) + abs(y - target->getY()) == 1) {
      
      state = CHOMPER_ATTACK_STATE;
      animation = attackAnimation;
      animation->reset();
      play_sound(SND_CHOMP);
      
    } else {
      
      if (abs(x - target->getX()) < 4 && abs(y - target->getY()) < 4) {
        if (abs(x - target->getX()) < abs(y - target->getY())) {
          if (y - target->getY() > 0) {
            dir = UP;
          } else {
            dir = DOWN;
          }
        } else if (abs(x - target->getX()) > abs(y - target->getY())) {
          if (x - target->getX() > 0) {
            dir = LEFT;
          } else {
            dir = RIGHT;
          }
        } else {
          if (x - target->getX() < 0 && y - target->getY() > 0) { // NE
            if (prevDirection == UP) {
              dir = RIGHT;
            } else {
              dir = UP;
            }
          } else if (x - target->getX() < 0 && y - target->getY() < 0) { // SE
            if (prevDirection == DOWN) {
              dir = RIGHT;
            } else {
              dir = DOWN;
            }
          } else if (x - target->getX() > 0 && y - target->getY() > 0) { // NW
            if (prevDirection == UP) {
              dir = LEFT;
            } else {
              dir = UP;
            }
          } else { // SW
            if (prevDirection == DOWN) {
              dir = LEFT;
            } else {
              dir = DOWN;
            }
          }
        }
      } else {
        dir = random_number(UP, LEFT);
      }
      
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
        state = CHOMPER_MOVE_STATE;
      }
      
      // Bound him so he doesn't wander right out of the screen!
      bound(1, ROWS - 2, 1, COLS - 2);
      
      prevDirection = dir;
      
      wait();
      
    }
    
    break;
    
  case CHOMPER_MOVE_STATE:
    if (!isMoving()) {
      state = CHOMPER_STAND_STATE;
    }
    break;
    
  case CHOMPER_ATTACK_STATE:
    if (animation->isFinished()) {
      world->attack(team, target->getX(), target->getY());
      state = CHOMPER_STAND_STATE;
      animation = standAnimation;
      animation->reset();
      wait();
    }
    break;
    
  }
  
}
