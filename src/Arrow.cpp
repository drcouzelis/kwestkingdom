#include "Animation.h"
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
  
  flyRightAnimation = new Animation();
  flyRightAnimation->addFrame(IMG("arrow.bmp"));
  
  flyLeftAnimation = flyRightAnimation->copy()->setHorizontalFlip(true);
  flyDownAnimation = flyRightAnimation->copy()->setRotate(true);
  flyUpAnimation = flyRightAnimation->copy()->setHorizontalFlip(true)->setRotate(true);
  
  direction = UP;
  
  this->toHoldState();
}


Arrow::~Arrow() {
  delete flyUpAnimation;
  delete flyDownAnimation;
  delete flyLeftAnimation;
  delete flyRightAnimation;

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
    animation = flyUpAnimation;
  } else if (direction == DOWN) {
    animation = flyDownAnimation;
  } else if (direction == LEFT) {
    animation = flyLeftAnimation;
  } else {
    animation = flyRightAnimation;
  }

}


void Arrow::toHoldState() {
  
  int visualOffset;
  
  visualOffset = (getTileSize() / 3) + (getTileSize() / 10);
  
  state = ARROW_HOLD_STATE;
  
  this->setDirection(direction);
  
  // Offset the animation a little bit to make it look like
  // the arrow is in the bow string.
  flyUpAnimation->setOffsetX(0);
  flyUpAnimation->setOffsetY(visualOffset);
  flyDownAnimation->setOffsetX(0);
  flyDownAnimation->setOffsetY(-visualOffset);
  flyLeftAnimation->setOffsetX(visualOffset);
  flyLeftAnimation->setOffsetY(0);
  flyRightAnimation->setOffsetX(-visualOffset);
  flyRightAnimation->setOffsetY(0);
  

}


void Arrow::toFlyingState() {
  state = ARROW_FLYING_STATE;
  this->setDirection(direction);
  this->findTarget();
  // Put the animation back to where it's supposed to be.
  flyUpAnimation->setOffsetX(0);
  flyUpAnimation->setOffsetY(0);
  flyDownAnimation->setOffsetX(0);
  flyDownAnimation->setOffsetY(0);
  flyLeftAnimation->setOffsetX(0);
  flyLeftAnimation->setOffsetY(0);
  flyRightAnimation->setOffsetX(0);
  flyRightAnimation->setOffsetY(0);
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



