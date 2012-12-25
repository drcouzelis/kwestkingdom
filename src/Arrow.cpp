#include "Arrow.h"
#include "KwestKingdom.h"
#include "resources.h"
#include "utilities.h"
#include "World.h"


typedef enum {
  ARROW_HOLD_STATE,
  ARROW_FLYING_STATE,
  ARROW_STOPPED_STATE
} ARROW_STATE;


Arrow::Arrow() {
  
  this->setSpeed(getWalkSpeed() * 4);
  
  init_anim(&fly_right_anim, OFF, 0);
  add_frame(&fly_right_anim, IMG("arrow.bmp"));
  
  copy_anim(&fly_left_anim, &fly_right_anim);
  fly_left_anim.h_flip = ON;

  copy_anim(&fly_down_anim, &fly_right_anim);
  fly_down_anim.rotate = ON;

  copy_anim(&fly_right_anim, &fly_right_anim);
  fly_right_anim.h_flip = ON;
  fly_right_anim.rotate = ON;
  
  direction = UP;
  
  this->toHoldState();
}


Arrow::~Arrow() {
}


void Arrow::update() {
  
  Character::update();
  
  switch (state) {
  case ARROW_HOLD_STATE:
    // There's just not much going on when it's being held.
    break;
    
  case ARROW_FLYING_STATE:
    
    if (!this->moving()) {
      
      if (direction == LEFT) {
        world->attackFromTeam(team, x - 1, y);
      } else if (direction == RIGHT) {
        world->attackFromTeam(team, x + 1, y);
      } else if (direction == UP) {
        world->attackFromTeam(team, x, y - 1);
      } else {
        world->attackFromTeam(team, x, y + 1);
      }
      
      this->toStoppedState();
      
    }
    
    break;
    
  case ARROW_STOPPED_STATE:
    // There's not much going on when it's stopped.
    break;
  }
  

  
}


bool Arrow::isInsideScreen() {
  if (x < 0 || x > COLS - 1 || y < 0 || y > ROWS - 1) {
    return false;
  }
  return true;
}


void Arrow::findTarget() {
  
  if (direction == LEFT) {
    while (world->isFlyable(x - 1, y) && !world->isAttackable(team, x - 1, y) && this->isInsideScreen()) {
      x--;
    }
  } else if (direction == RIGHT) {
    while (world->isFlyable(x + 1, y) && !world->isAttackable(team, x + 1, y) && this->isInsideScreen()) {
      x++;
    }
  } else if (direction == UP) {
    while (world->isFlyable(x, y - 1) && !world->isAttackable(team, x, y - 1) && this->isInsideScreen()) {
      y--;
    }
  } else {
    while (world->isFlyable(x, y + 1) && !world->isAttackable(team, x, y + 1) && this->isInsideScreen()) {
      y++;
    }
  }
  

  
}


void Arrow::setDirection(int aDirection) {
  direction = aDirection;
  if (direction == UP) {
    anim = &fly_up_anim;
  } else if (direction == DOWN) {
    anim = &fly_down_anim;
  } else if (direction == LEFT) {
    anim = &fly_left_anim;
  } else {
    anim = &fly_right_anim;
  }
}


void Arrow::toHoldState() {
  
  int visualOffset;
  
  visualOffset = (getTileSize() / 3) + (getTileSize() / 10);
  
  state = ARROW_HOLD_STATE;
  
  this->setDirection(direction);
  
  // Offset the anim a little bit to make it look like
  // the arrow is in the bow string.
  fly_up_anim.offset_x = 0;
  fly_up_anim.offset_y = visualOffset;
  fly_down_anim.offset_x = 0;
  fly_down_anim.offset_y = -visualOffset;
  fly_left_anim.offset_x = visualOffset;
  fly_left_anim.offset_y = 0;
  fly_right_anim.offset_x = -visualOffset;
  fly_right_anim.offset_y = 0;
}


void Arrow::toFlyingState() {
  state = ARROW_FLYING_STATE;
  this->setDirection(direction);
  this->findTarget();
  // Put the anim back to where it's supposed to be.
  fly_up_anim.offset_x = 0;
  fly_up_anim.offset_y = 0;
  fly_down_anim.offset_x = 0;
  fly_down_anim.offset_y = 0;
  fly_left_anim.offset_x = 0;
  fly_left_anim.offset_y = 0;
  fly_right_anim.offset_x = 0;
  fly_right_anim.offset_y = 0;
  play_sound(SND("arrow_fly.wav"));
}


void Arrow::toStoppedState() {
  state = ARROW_STOPPED_STATE;
  this->setDirection(direction);
  play_sound(SND("arrow_hit.wav"));
}


bool Arrow::stopped() {
  if (state == ARROW_STOPPED_STATE) {
    return true;
  }
  return false;
}



