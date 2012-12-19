#include "Animation.h"
#include "Archer.h"
#include "Arrow.h"
#include "Bow.h"
#include "KwestKingdom.h"
#include "Resources.h"
#include "utilities.h"
#include "World.h"


typedef enum {
  ARCHER_STAND_STATE,
  ARCHER_ATTACK_STATE,
  ARCHER_MOVE_STATE,
  ARCHER_DRAW_BOW_STATE,
  ARCHER_SHOOT_ARROW_STATE
} ARCHER_STATE;


Archer::Archer() {
  
  x = 0;
  y = 0;
  
  speed = getWalkSpeed();
  team = ENEMY_TEAM;
  
  bow = new Bow();
  bow->setSpeed(speed);
  bow->toHoldState();
  
  standAnimation = new Animation();
  standAnimation->addFrame(getImage(IMAGES_ARCHER_1));
  standAnimation->addFrame(getImage(IMAGES_ARCHER_2));
  standAnimation->addFrame(getImage(IMAGES_ARCHER_3));
  standAnimation->addFrame(getImage(IMAGES_ARCHER_2));
  standAnimation->setLoop(true);
  standAnimation->setSpeed(3);
  
  beginAttackAnimation = new Animation();
  beginAttackAnimation->addFrame(getImage(IMAGES_ARCHER_1));
  beginAttackAnimation->addFrame(getImage(IMAGES_ARCHER_2));
  beginAttackAnimation->addFrame(getImage(IMAGES_ARCHER_2));
  beginAttackAnimation->addFrame(getImage(IMAGES_ARCHER_3));
  beginAttackAnimation->setLoop(false);
  beginAttackAnimation->setSpeed(12);
  
  endAttackAnimation = new Animation();
  endAttackAnimation->addFrame(getImage(IMAGES_ARCHER_3));
  endAttackAnimation->addFrame(getImage(IMAGES_ARCHER_2));
  endAttackAnimation->addFrame(getImage(IMAGES_ARCHER_2));
  endAttackAnimation->setLoop(false);
  endAttackAnimation->setSpeed(12);
  
  animation = standAnimation;
  state = ARCHER_STAND_STATE;
  direction = UP;
  this->wait();
}


Archer::~Archer() {
  delete bow;
  delete standAnimation;
  delete beginAttackAnimation;
  delete endAttackAnimation;
}


void
Archer::update() {
  
  int dir;
  int toX;
  int toY;
  Character *target;
  
  Enemy::update();
  bow->update();
  
  if (this->waiting()) {
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
      
      this->toDrawBowState();
      this->wait();
      
    } else if (y == target->getY()) {
      
      if (x > target->getX()) { // Hero is left.
        direction = LEFT;
      } else { // Hero is right.
        direction = RIGHT;
      }
      
      this->toDrawBowState();
      this->wait();
      
    } else if ((x == target->getX() - 1 || x == target->getX() + 1) && random_number(0, 1) == 1) {
      
      if (y > target->getY()) { // Hero is up.
        direction = UP;
      } else { // Hero is down.
        direction = DOWN;
      }
      
      this->toDrawBowState();
      this->wait();
      
    } else if ((y == target->getY() - 1 || y == target->getY() + 1) && random_number(0, 1) == 1) {
      
      if (x > target->getX()) { // Hero is left.
        direction = LEFT;
      } else { // Hero is right.
        direction = RIGHT;
      }
      
      this->toDrawBowState();
      this->wait();
      
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
        this->moveX(toX);
        this->moveY(toY);
        this->toMoveState();
      }
      
      this->wait();
    }
    
    // Bound him so he doesn't wander right out of the screen!
    this->bound(1, ROWS - 2, 1, COLS - 2);
    
    break;
    
  case ARCHER_MOVE_STATE:
    if (!this->moving()) {
      this->toStandState();
    }
    break;
    
  case ARCHER_DRAW_BOW_STATE:
    if (animation->isFinished()) {
      this->toShootArrowState();
    }
    break;
    
  case ARCHER_SHOOT_ARROW_STATE:
    if (animation->isFinished()) {
      animation = standAnimation;
      bow->toHoldState();
    }
    if (bow->getArrow()->stopped()) {
      delete bow->getArrow();
      bow->setArrow(NULL);
      this->toStandState();
      this->wait();
    }
    break;
  }
}


void
Archer::draw(BITMAP *buffer) {
  Enemy::draw(buffer);
  bow->draw(buffer);
}


void
Archer::toStandState() {
  state = ARCHER_STAND_STATE;
  animation = standAnimation;
}


void
Archer::toMoveState() {
  state = ARCHER_MOVE_STATE;
  animation = standAnimation;
}


void
Archer::toDrawBowState() {
  
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
Archer::toShootArrowState() {
  state = ARCHER_SHOOT_ARROW_STATE;
  animation = endAttackAnimation;
  animation->reset();
  bow->getArrow()->toFlyingState();
  bow->toHoldState();
}


void
Archer::setX(int newX) {
  Enemy::setX(newX);
  bow->setX(newX);
}


void
Archer::setY(int newY) {
  Enemy::setY(newY);
  bow->setY(newY);
}


void
Archer::moveX(int newX) {
  Enemy::moveX(newX);
  bow->moveX(newX);
}


void
Archer::moveY(int newY) {
  Enemy::moveY(newY);
  bow->moveY(newY);
}

