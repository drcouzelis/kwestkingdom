#include "Giant.h"
#include "Hammer.h"
#include "KwestKingdom.h"
#include "resources.h"
#include "utilities.h"
#include "World.h"


typedef enum {
  GIANT_STAND_STATE,
  GIANT_ATTACK_STATE,
  GIANT_MOVE_STATE
} GIANT_STATE;


Giant::Giant() {
  
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
  
  init_anim(&stand_anim, ON, 3);
  add_frame(&stand_anim, IMG("giant_1.bmp"));
  add_frame(&stand_anim, IMG("giant_2.bmp"));
  add_frame(&stand_anim, IMG("giant_3.bmp"));
  add_frame(&stand_anim, IMG("giant_2.bmp"));
  
  init_anim(&attack_anim, OFF, 24);
  add_frame(&attack_anim, IMG("giant_1.bmp"));
  add_frame(&attack_anim, IMG("giant_2.bmp"));
  add_frame(&attack_anim, IMG("giant_2.bmp"));
  add_frame(&attack_anim, IMG("giant_3.bmp"));
  add_frame(&attack_anim, IMG("giant_3.bmp"));
  add_frame(&attack_anim, IMG("giant_3.bmp"));
  add_frame(&attack_anim, IMG("giant_3.bmp"));
  add_frame(&attack_anim, IMG("giant_3.bmp"));
  add_frame(&attack_anim, IMG("giant_2.bmp"));
  add_frame(&attack_anim, IMG("giant_2.bmp"));
  
  anim = &stand_anim;
  state = GIANT_STAND_STATE;
  this->setMoney(5);
  this->wait();
}


Giant::~Giant() {
  delete hammer;
}


bool Giant::target(Character *target, int range) {
  
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


int Giant::directionToTarget(Character *target) {
  
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


bool Giant::isMe(int atX, int atY) {
  if (
    (x == atX && y == atY) ||
    (x + 1 == atX && y == atY) ||
    (x == atX && y + 1 == atY) ||
    (x + 1 == atX && y + 1 == atY)
  ) {
    
    return true;
    
  }
  
  return false;
  
}


bool Giant::canWalkTo(int toX, int toY) {
  
  if (
    !world->isWalkable(toX, toY) ||
    !world->isWalkable(toX + 1, toY) ||
    !world->isWalkable(toX, toY + 1) ||
    !world->isWalkable(toX + 1, toY + 1) ||
    (world->isInhabited(toX, toY) && !this->isMe(toX, toY)) ||
    (world->isInhabited(toX + 1, toY) && !this->isMe(toX + 1, toY)) ||
    (world->isInhabited(toX, toY + 1) && !this->isMe(toX, toY + 1)) ||
    (world->isInhabited(toX + 1, toY + 1) && !this->isMe(toX + 1, toY + 1))
  ) {
    
    return false;
    
  }
  
  return true;
  
}


void Giant::update() {
  
  int dir;
  int toX;
  int toY;
  Character *target;
  
  Enemy::update();
  hammer->update();
  
  if (this->waiting()) {
    return;
  }
  
  if (health == 0) {
    return;
  }
  
  target = world->getTarget();
  
  switch (state) {
  
  case GIANT_STAND_STATE:
    
    // If the target has a walking distance of one...
    if (this->target(target, 1)) {
      
      state = GIANT_ATTACK_STATE;
      anim = &attack_anim;
      reset_anim(anim);
      
      // Change the state of the hammer.
      if (this->directionToTarget(target) == UP) {
        hammer->setState(HAMMER_ATTACK_UP_STATE);
      } else if (this->directionToTarget(target) == DOWN) {
        hammer->setState(HAMMER_ATTACK_DOWN_STATE);
      } else if (this->directionToTarget(target) == LEFT) {
        hammer->setState(HAMMER_ATTACK_LEFT_STATE);
      } else if (this->directionToTarget(target) == RIGHT) {
        hammer->setState(HAMMER_ATTACK_RIGHT_STATE);
      }
      
    } else if (/* Hero is nearby */ false) {
      
      // Then chase the hero!
      // (Not implemented)
      
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
      
      if (this->canWalkTo(toX, toY)) {
        
        this->moveX(toX);
        this->moveY(toY);
        state = GIANT_MOVE_STATE;
        
      }
      
      this->wait();
      
    }
    
    // Bound him so he doesn't wander right out of the screen!
    this->bound(1, ROWS - 2, 1, COLS - 2);
    
    break;
    
  case GIANT_MOVE_STATE:
    if (!this->moving()) {
      state = GIANT_STAND_STATE;
    }
    break;
    
  case GIANT_ATTACK_STATE:
    if (anim->done) {
      // Send the hero soaring!
      world->attackFromTeam(team, target->getX(), target->getY());
      
      state = GIANT_STAND_STATE;
      anim = &stand_anim;
      reset_anim(anim);
      hammer->setState(HAMMER_HOLD_STATE);
      this->wait();
    }
    break;
    
  }
  

  
}


void Giant::draw(BITMAP * buffer) {
  Enemy::draw(buffer);
  hammer->draw(buffer);
}


void Giant::setX(int newX) {
  Enemy::setX(newX);
  hammer->setX(newX);
}


void Giant::setY(int newY) {
  Enemy::setY(newY);
  hammer->setY(newY);
}


void Giant::moveX(int newX) {
  Enemy::moveX(newX);
  hammer->moveX(newX);
}


void Giant::moveY(int newY) {
  Enemy::moveY(newY);
  hammer->moveY(newY);
}


void Giant::dropItem() {
  y++;
  Enemy::dropItem();
  y--;
}


void Giant::setWorld(World * aWorld) {
  world = aWorld;
  hammer->setWorld(world);

}



