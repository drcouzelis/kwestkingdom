#include "Animation.h"
#include "Chomper.h"
#include "KwestKingdom.h"
#include "Resources.h"
#include "World.h"


typedef enum {
  CHOMPER_STAND_STATE,
  CHOMPER_ATTACK_STATE,
  CHOMPER_MOVE_STATE
} CHOMPER_STATE;





Chomper::Chomper() {
  
  prevDirection = UP;
  
  standAnimation = new Animation();
  standAnimation->addFrame(getImage(IMAGES_CHOMPER_STAND_1));
  standAnimation->addFrame(getImage(IMAGES_CHOMPER_STAND_2));
  standAnimation->addFrame(getImage(IMAGES_CHOMPER_STAND_3));
  standAnimation->addFrame(getImage(IMAGES_CHOMPER_STAND_2));
  standAnimation->setLoop(true);
  standAnimation->setSpeed(6);
  
  attackAnimation = new Animation();
  attackAnimation->addFrame(getImage(IMAGES_CHOMPER_BITE_1));
  attackAnimation->addFrame(getImage(IMAGES_CHOMPER_BITE_2));
  attackAnimation->addFrame(getImage(IMAGES_CHOMPER_BITE_3));
  attackAnimation->addFrame(getImage(IMAGES_CHOMPER_BITE_4));
  attackAnimation->addFrame(getImage(IMAGES_CHOMPER_BITE_5));
  attackAnimation->addFrame(getImage(IMAGES_CHOMPER_BITE_4));
  attackAnimation->addFrame(getImage(IMAGES_CHOMPER_BITE_3));
  attackAnimation->addFrame(getImage(IMAGES_CHOMPER_BITE_2));
  attackAnimation->addFrame(getImage(IMAGES_CHOMPER_BITE_1));
  attackAnimation->setLoop(false);
  attackAnimation->setSpeed(20);
  
  animation = standAnimation;
  state = CHOMPER_STAND_STATE;
  this->wait();
  
}






Chomper::~Chomper() {
  delete standAnimation;
  delete attackAnimation;

}


void Chomper::update() {
  
  int dir;
  int toX;
  int toY;
  Character *target;
  
  Enemy::update();
  
  if (this->waiting()) {
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
      playSound(SOUNDS_CHOMP);
      
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
        this->moveX(toX);
        this->moveY(toY);
        state = CHOMPER_MOVE_STATE;
      }
      
      // Bound him so he doesn't wander right out of the screen!
      this->bound(1, ROWS - 2, 1, COLS - 2);
      
      prevDirection = dir;
      
      this->wait();
      
    }
    
    break;
    
  case CHOMPER_MOVE_STATE:
    if (!this->moving()) {
      state = CHOMPER_STAND_STATE;
    }
    break;
    
  case CHOMPER_ATTACK_STATE:
    if (animation->isFinished()) {
      world->attackFromTeam(team, target->getX(), target->getY());
      state = CHOMPER_STAND_STATE;
      animation = standAnimation;
      animation->reset();
      this->wait();
    }
	break;
	
  }
  

  
}




