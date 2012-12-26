#include "Chomper.h"
#include "KwestKingdom.h"
#include "resources.h"
#include "utilities.h"
#include "World.h"


typedef enum {
  CHOMPER_STAND_STATE,
  CHOMPER_ATTACK_STATE,
  CHOMPER_MOVE_STATE
} CHOMPER_STATE;


Chomper::Chomper() {
  
  prevDirection = UP;
  
  init_anim(&stand_anim, ON, 6);
  add_frame(&stand_anim, IMG("chomper_stand_1.bmp"));
  add_frame(&stand_anim, IMG("chomper_stand_2.bmp"));
  add_frame(&stand_anim, IMG("chomper_stand_3.bmp"));
  add_frame(&stand_anim, IMG("chomper_stand_2.bmp"));
  
  init_anim(&attack_anim, OFF, 20);
  add_frame(&attack_anim, IMG("chomper_bite_1.bmp"));
  add_frame(&attack_anim, IMG("chomper_bite_2.bmp"));
  add_frame(&attack_anim, IMG("chomper_bite_3.bmp"));
  add_frame(&attack_anim, IMG("chomper_bite_4.bmp"));
  add_frame(&attack_anim, IMG("chomper_bite_5.bmp"));
  add_frame(&attack_anim, IMG("chomper_bite_4.bmp"));
  add_frame(&attack_anim, IMG("chomper_bite_3.bmp"));
  add_frame(&attack_anim, IMG("chomper_bite_2.bmp"));
  add_frame(&attack_anim, IMG("chomper_bite_1.bmp"));
  
  anim = &stand_anim;
  state = CHOMPER_STAND_STATE;
  this->wait();
  
}


Chomper::~Chomper() {
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
      anim = &attack_anim;
      reset_anim(anim);
      play_sound(SND("chomp.wav"));
      
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
    if (anim->done) {
      world->attackFromTeam(team, target->getX(), target->getY());
      state = CHOMPER_STAND_STATE;
      anim = &stand_anim;
      reset_anim(anim);
      this->wait();
    }
	break;
	
  }
  

  
}




