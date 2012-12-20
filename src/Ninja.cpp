#include "Animation.h"
#include "KwestKingdom.h"
#include "Ninja.h"
#include "resources.h"
#include "Sword.h"
#include "utilities.h"
#include "World.h"


typedef enum {
  NINJA_STAND_STATE,
  NINJA_ATTACK_STATE,
  NINJA_MOVE_STATE,
  NINJA_DASH_STATE
} NINJA_STATE;


Ninja::Ninja() {
  
  x = 0;
  y = 0;
  
  team = ENEMY_TEAM;
  
  sword = new Sword();
  sword->setSpeed(speed);
  sword->toHoldState();
  
  standAnimation = new Animation();
  standAnimation->addFrame(IMG("ninja_1.bmp"));
  standAnimation->addFrame(IMG("ninja_2.bmp"));
  standAnimation->addFrame(IMG("ninja_3.bmp"));
  standAnimation->addFrame(IMG("ninja_2.bmp"));
  standAnimation->setLoop(true);
  standAnimation->setSpeed(6);
  
  dashAnimation = standAnimation->copy();
  dashAnimation->setSpeed(24);
  
  attackAnimation = new Animation();
  attackAnimation->addFrame(img.bmp("NINJA_1"));
  attackAnimation->addFrame(img.bmp("NINJA_2"));
  attackAnimation->addFrame(img.bmp("NINJA_2"));
  attackAnimation->addFrame(img.bmp("NINJA_3"));
  attackAnimation->addFrame(img.bmp("NINJA_3"));
  attackAnimation->addFrame(img.bmp("NINJA_2"));
  attackAnimation->addFrame(img.bmp("NINJA_2"));
  attackAnimation->setLoop(false);
  attackAnimation->setSpeed(12);
  
  animation = standAnimation;
  state = NINJA_STAND_STATE;
  this->setSpeed(getWalkSpeed());
  this->wait();
}


Ninja::~Ninja() {
  delete sword;
  delete standAnimation;
  delete dashAnimation;
  delete attackAnimation;

}


void Ninja::update() {
  
  int dir;
  int toX;
  int toY;
  Character *target;
  
  Enemy::update();
  sword->update();
  
  if (this->waiting()) {
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
        sword->toAttackUpState();
      } else if (x == target->getX() && y == target->getY() - 1) { // Down
        sword->toAttackDownState();
      } else if (x == target->getX() + 1 && y == target->getY()) { // Left
        sword->toAttackLeftState();
      } else if (x == target->getX() - 1 && y == target->getY()) { // Right
        sword->toAttackRightState();
      }
      
    } else if (x == target->getX()) {
      
      if (y > target->getY()) { // Hero is directly up.
        while (y - 1 != target->getY() && world->isWalkable(x, y - 1) && !world->isInhabited(x, y - 1)) {
          this->moveY(y - 1);
        }
      } else { // Hero is directly down.
        while (y + 1 != target->getY() && world->isWalkable(x, y + 1) && !world->isInhabited(x, y + 1)) {
          this->moveY(y + 1);
        }
      }
      
      state = NINJA_DASH_STATE;
      this->setSpeed(getWalkSpeed() + (getWalkSpeed() / 5));
      animation = dashAnimation;
      animation->reset();
      
    } else if (y == target->getY()) {
      
      if (x > target->getX()) { // Hero is directly left.
        while (x - 1 != target->getX() && world->isWalkable(x - 1, y) && !world->isInhabited(x - 1, y)) {
          this->moveX(x - 1);
        }
      } else { // Hero is directly right.
        while (x + 1 != target->getX() && world->isWalkable(x + 1, y) && !world->isInhabited(x + 1, y)) {
          this->moveX(x + 1);
        }
      }
      
      state = NINJA_DASH_STATE;
      this->setSpeed(getWalkSpeed() + (getWalkSpeed() / 5));
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
        this->moveX(toX);
        this->moveY(toY);
        state = NINJA_MOVE_STATE;
      }
      
      this->wait();
      
    }
    
    // Bound him so he doesn't wander right out of the screen!
    this->bound(1, ROWS - 2, 1, COLS - 2);
    
    break;
    
  case NINJA_MOVE_STATE:
    if (!this->moving()) {
      state = NINJA_STAND_STATE;
    }
    break;
    
  case NINJA_DASH_STATE:
    if (!this->moving()) {
      this->setSpeed(getWalkSpeed());
      // If the target has a walking distance of one...
      if (abs(x - target->getX()) + abs(y - target->getY()) == 1) {
        state = NINJA_ATTACK_STATE;
        animation = attackAnimation;
        animation->reset();
        // Change the state of the sword.
        if (x == target->getX() && y == target->getY() + 1) { // Up
          sword->toAttackUpState();
        } else if (x == target->getX() && y == target->getY() - 1) { // Down
          sword->toAttackDownState();
        } else if (x == target->getX() + 1 && y == target->getY()) { // Left
          sword->toAttackLeftState();
        } else if (x == target->getX() - 1 && y == target->getY()) { // Right
          sword->toAttackRightState();
        }
      } else {
        state = NINJA_STAND_STATE;
        animation = standAnimation;
        animation->reset();
        this->wait();
      }
    }
    break;
    
  case NINJA_ATTACK_STATE:
    if (animation->isFinished()) {
      world->attackFromTeam(team, target->getX(), target->getY());
      state = NINJA_STAND_STATE;
      animation = standAnimation;
      animation->reset();
      sword->toHoldState();
      this->wait();
    }
	break;
	
  }
  

  
}


void Ninja::draw(BITMAP * buffer) {
  Enemy::draw(buffer);
  sword->draw(buffer);

}


void Ninja::setX(int newX) {
  Enemy::setX(newX);
  sword->setX(newX);

}


void Ninja::setY(int newY) {
  Enemy::setY(newY);
  sword->setY(newY);

}


void Ninja::moveX(int newX) {
  Enemy::moveX(newX);
  sword->moveX(newX);

}


void Ninja::moveY(int newY) {
  Enemy::moveY(newY);
  sword->moveY(newY);

}


void Ninja::setSpeed(int theSpeed) {
  speed = theSpeed;
  sword->setSpeed(speed);

}



