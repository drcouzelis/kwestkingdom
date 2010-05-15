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
#include "Hero.h"
#include "World.h"


#define HERO_ATTACK_SPEED 12


typedef enum {
  HERO_STAND_STATE,
  HERO_MOVE_STATE,
  HERO_ATTACK_STATE,
  HERO_HURT_STATE,
  HERO_DEAD_STATE,
  HERO_PUSH_SWORD_STATE,
  HERO_PULL_SWORD_STATE,
  HERO_DRAW_BOW_STATE,
  HERO_SHOOT_ARROW_STATE
} HERO_STATE;


Hero::Hero()
: shield()
, sword()
, bow()
, upKey(KeyControl(KEY_UP))
, downKey(KeyControl(KEY_DOWN))
, rightKey(KeyControl(KEY_RIGHT))
, leftKey(KeyControl(KEY_LEFT))
, waitKey(KeyControl(KEY_SPACE))
, attackKey(KeyControl(KEY_LCONTROL))
, handKey(KeyControl(KEY_0))
, shieldKey(KeyControl(KEY_1))
, swordKey(KeyControl(KEY_2))
, bowKey(KeyControl(KEY_3))
{
  speed = getWalkSpeed(); // In FPS
  health = 3;
  maxHealth = MAX_HERO_HEALTH;
  team = HERO_TEAM;
  
  //shield = new Shield();
  //sword = new Sword();
  //bow = new Bow();
  
  shield.setSpeed(speed);
  sword.setSpeed(speed);
  bow.setSpeed(speed);
  
  standAnimation = new Animation(6, true);
  standAnimation->addFrame(get_image(IMG_HERO_STAND_1));
  standAnimation->addFrame(get_image(IMG_HERO_STAND_2));
  standAnimation->addFrame(get_image(IMG_HERO_STAND_3));
  standAnimation->addFrame(get_image(IMG_HERO_STAND_2));
  
  beginAttackAnimation = new Animation(HERO_ATTACK_SPEED, false);
  beginAttackAnimation->addFrame(get_image(IMG_HERO_ATTACK_1));
  beginAttackAnimation->addFrame(get_image(IMG_HERO_ATTACK_2));
  beginAttackAnimation->addFrame(get_image(IMG_HERO_ATTACK_3));
  beginAttackAnimation->addFrame(get_image(IMG_HERO_ATTACK_4));
  
  endAttackAnimation = new Animation(HERO_ATTACK_SPEED, false);
  endAttackAnimation->addFrame(get_image(IMG_HERO_ATTACK_3));
  endAttackAnimation->addFrame(get_image(IMG_HERO_ATTACK_2));
  endAttackAnimation->addFrame(get_image(IMG_HERO_ATTACK_1));
  
  hurtAnimation = new Animation(12, false);
  hurtAnimation->addFrame(get_image(IMG_HERO_HURT_1));
  hurtAnimation->addFrame(get_image(IMG_HERO_HURT_2));
  hurtAnimation->addFrame(get_image(IMG_HERO_HURT_3));
  hurtAnimation->addFrame(get_image(IMG_HERO_HURT_4));
  hurtAnimation->addFrame(get_image(IMG_HERO_HURT_3));
  hurtAnimation->addFrame(get_image(IMG_HERO_HURT_2));
  hurtAnimation->addFrame(get_image(IMG_HERO_HURT_1));
  
  deadAnimation = new Animation(6, false);
  deadAnimation->addFrame(get_image(IMG_HERO_DIE_1));
  deadAnimation->addFrame(get_image(IMG_HERO_DIE_2));
  deadAnimation->addFrame(get_image(IMG_HERO_DIE_3));
  deadAnimation->addFrame(get_image(IMG_HERO_DIE_4));
  deadAnimation->addFrame(get_image(IMG_HERO_DIE_5));
  
  waitKey.setDelay(GAME_TICKER);
  handKey.setDelay(GAME_TICKER);
  shieldKey.setDelay(GAME_TICKER);
  swordKey.setDelay(GAME_TICKER);
  bowKey.setDelay(GAME_TICKER);
  
  toStandState();
  sword.toHoldState();
  
  go(); // The hero doesn't wait! At least not when the game starts. ;-)
}


Hero::~Hero()
{
  delete standAnimation;
  delete beginAttackAnimation;
  delete endAttackAnimation;
}


void
Hero::updateStandState()
{
  int toX;
  int toY;
  
  // Handle item key input.
  // Update the items.
  if (shieldKey.isPressed()) {
    shield.toHoldState();
    sword.toAwayState();
    bow.toAwayState();
  } else if (swordKey.isPressed()) {
    shield.toAwayState();
    sword.toHoldState();
    bow.toAwayState();
  } else if (bowKey.isPressed()) {
    shield.toAwayState();
    sword.toAwayState();
    bow.toHoldState();
  } else if (handKey.isPressed()) {
    shield.toAwayState();
    sword.toAwayState();
    bow.toAwayState();
  }
  
  if (attackKey.isPressed()) {
    
    if (upKey.isPressed()) {
      direction = UP;
      toAttackState();
    } else if (downKey.isPressed()) {
      direction = DOWN;
      toAttackState();
    } else if (leftKey.isPressed()) {
      direction = LEFT;
      toAttackState();
    } else if (rightKey.isPressed()) {
      direction = RIGHT;
      toAttackState();
    }
    
  } else {
    
    // If you're not attacking with the attack key,
    // then maybe you are trying to walk...
    
    toX = x;
    toY = y;
    
    if (upKey.isPressed()) {
      toY--;
      if (sword.isHeld() && world->isAttackable(team, toX, toY)) {
        direction = UP;
        toAttackState();
      }
    } else if (downKey.isPressed()) {
      toY++;
      if (sword.isHeld() && world->isAttackable(team, toX, toY)) {
        direction = DOWN;
        toAttackState();
      }
    } else if (leftKey.isPressed()) {
      toX--;
      if (sword.isHeld() && world->isAttackable(team, toX, toY)) {
        direction = LEFT;
        toAttackState();
      }
    } else if (rightKey.isPressed()) {
      toX++;
      if (sword.isHeld() && world->isAttackable(team, toX, toY)) {
        direction = RIGHT;
        toAttackState();
      }
    }
    
    if (world->isWalkable(toX, toY) && !world->isInhabited(toX, toY)) {
      
      moveX(toX);
      moveY(toY);
      toMoveState();
      wait();
      
      // If the hero is holding the shield
      // then make him wait another turn.
      if (shield.isHeld()) {
        wait();
      }
      
    }
    
  }
  
}


void
Hero::update()
{
  Character::update();
  shield.update();
  sword.update();
  bow.update();
  
  if (isWaiting()) {
    return;
  }
  
  if (waitKey.isPressed()) {
    wait();
  }
  
  switch (state) {
  
  case HERO_STAND_STATE:
    updateStandState();
    break;
    
  case HERO_MOVE_STATE:
    if (!isMoving()) {
      toStandState();
    }
    break;
    
  case HERO_ATTACK_STATE:
    if (sword.isHeld()) {
      toPushSwordState();
    } else if (bow.isHeld()) {
      toDrawBowState();
      wait();
    }else {
      toStandState();
    }
    break;
  
  case HERO_HURT_STATE:
    if (animation->isFinished()) {
      if (health == 0) {
        shield.toAwayState();
        sword.toAwayState();
        bow.toAwayState();
        toDeadState();
      } else {
        toStandState();
      }
    }
    break;
  
  case HERO_DEAD_STATE:
    // You are not going to do anything once you enter
    // the state of being dead.
    break;
      
  case HERO_PUSH_SWORD_STATE:
    if (animation->isFinished()) {
      switch (direction) {
      case UP:
        world->attack(team, x, y - 1);
        break;
      case DOWN:
        world->attack(team, x, y + 1);
        break;
      case LEFT:
        world->attack(team, x - 1, y);
        break;
      case RIGHT:
        world->attack(team, x + 1, y);
        break;
      }
      toPullSwordState();
    }
    break;
    
  case HERO_PULL_SWORD_STATE:
    if (animation->isFinished()) {
      toStandState();
      sword.toHoldState();
      wait();
    }
    break;
    
  case HERO_DRAW_BOW_STATE:
    if (animation->isFinished()) {
      toShootArrowState();
    }
    break;
    
  case HERO_SHOOT_ARROW_STATE:
    if (animation->isFinished()) {
      animation = standAnimation;
      bow.toHoldState();
    }
    if (bow.getArrow()->isStopped()) {
      delete bow.getArrow();
      bow.setArrow(NULL);
      toStandState();
      wait();
    }
    break;
    
  }
  
}


void
Hero::draw(BITMAP* buffer)
{
  Character::draw(buffer);
  shield.draw(buffer);
  sword.draw(buffer);
  bow.draw(buffer);
}


void
Hero::emptyHands()
{
  shield.toAwayState();
  sword.toAwayState();
  bow.toAwayState();
}


void
Hero::toStandState()
{
  state = HERO_STAND_STATE;
  animation = standAnimation;
}


void
Hero::toMoveState()
{
  state = HERO_MOVE_STATE;
  animation = standAnimation;
}


void
Hero::toAttackState()
{
  state = HERO_ATTACK_STATE;
  animation = standAnimation;
}


void
Hero::toHurtState()
{
  state = HERO_HURT_STATE;
  animation = hurtAnimation;
  animation->reset();
  
  // You can't shoot an arrow if you get
  // hurt whil trying to do it.
  delete bow.getArrow();
  bow.setArrow(NULL);
  if (bow.isHeld()) {
    bow.toHoldState();
  }
  
  play_sound(SND_GASP);
  
}


void
Hero::toDeadState()
{
  state = HERO_DEAD_STATE;
  animation = deadAnimation;
  animation->reset();
}


void
Hero::toPushSwordState()
{
  state = HERO_PUSH_SWORD_STATE;
  animation = beginAttackAnimation;
  animation->reset();
  switch (direction) {
  case UP:
    sword.toAttackUpState();
    break;
  case DOWN:
    sword.toAttackDownState();
    break;
  case LEFT:
    sword.toAttackLeftState();
    break;
  case RIGHT:
    sword.toAttackRightState();
    break;
  }
}


void
Hero::toPullSwordState(){
  state = HERO_PULL_SWORD_STATE;
  animation = endAttackAnimation;
  animation->reset();
}


void
Hero::toDrawBowState()
{
  state = HERO_DRAW_BOW_STATE;
  animation = beginAttackAnimation;
  animation->reset();
  
  switch (direction) {
  case UP:
    bow.toAttackUpState();
    break;
  case DOWN:
    bow.toAttackDownState();
    break;
  case LEFT:
    bow.toAttackLeftState();
    break;
  case RIGHT:
    bow.toAttackRightState();
    break;
  }
  
  bow.setArrow(x, y, direction, team, world);
}


void
Hero::toShootArrowState()
{
  state = HERO_SHOOT_ARROW_STATE;
  animation = endAttackAnimation;
  animation->reset();
  bow.getArrow()->toFlyingState();
  bow.toHoldState();
}


void
Hero::hurt()
{
  if (!shield.isHeld()) {
    toHurtState();
    Character::hurt();
  }
}


bool
Hero::isDead()
{
  if (state == HERO_DEAD_STATE && animation->isFinished()) {
    return true;
  }
  return false;
}


void
Hero::setX(int x)
{
  Character::setX(x);
  shield.setX(x);
  sword.setX(x);
  bow.setX(x);
}


void
Hero::setY(int y)
{
  Character::setY(y);
  shield.setY(y);
  sword.setY(y);
  bow.setY(y);
}


void
Hero::moveX(int x)
{
  Character::moveX(x);
  shield.moveX(x);
  sword.moveX(x);
  bow.moveX(x);
}


void
Hero::moveY(int y)
{
  Character::moveY(y);
  shield.moveY(y);
  sword.moveY(y);
  bow.moveY(y);
}
