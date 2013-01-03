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
  
  init_anim(&stand_anim, ON, 6);
  add_frame(&stand_anim, IMG("ninja_1.bmp"));
  add_frame(&stand_anim, IMG("ninja_2.bmp"));
  add_frame(&stand_anim, IMG("ninja_3.bmp"));
  add_frame(&stand_anim, IMG("ninja_2.bmp"));
  
  copy_anim(&dash_anim, &stand_anim);
  dash_anim.speed = 24;
  
  init_anim(&attack_anim, OFF, 12);
  add_frame(&attack_anim, IMG("ninja_1.bmp"));
  add_frame(&attack_anim, IMG("ninja_2.bmp"));
  add_frame(&attack_anim, IMG("ninja_2.bmp"));
  add_frame(&attack_anim, IMG("ninja_3.bmp"));
  add_frame(&attack_anim, IMG("ninja_3.bmp"));
  add_frame(&attack_anim, IMG("ninja_2.bmp"));
  add_frame(&attack_anim, IMG("ninja_2.bmp"));
  
  anim = &stand_anim;
  state = NINJA_STAND_STATE;
  this->setSpeed(getWalkSpeed());
  this->wait();
}


Ninja::~Ninja() {
  delete sword;
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
      anim = &attack_anim;
      reset_anim(anim);
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
      anim = &dash_anim;
      reset_anim(anim);
      
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
      anim = &dash_anim;
      reset_anim(anim);
      
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
        anim = &attack_anim;
        reset_anim(anim);
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
        anim = &stand_anim;
        reset_anim(anim);
        this->wait();
      }
    }
    break;
    
  case NINJA_ATTACK_STATE:
    if (anim->done) {
      world->attackFromTeam(team, target->getX(), target->getY());
      state = NINJA_STAND_STATE;
      anim = &stand_anim;
      reset_anim(anim);
      sword->toHoldState();
      this->wait();
    }
	break;
	
  }
  

  
}


void Ninja::draw(IMAGE * canvas) {
  Enemy::draw(canvas);
  sword->draw(canvas);

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



