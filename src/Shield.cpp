#include "Animation.h"
#include "resources.h"
#include "Shield.h"


typedef enum {
  SHIELD_HOLD_STATE,
  SHIELD_AWAY_STATE
} SHIELD_STATE;


Shield::Shield() {
  
  holdAnimation = new Animation();
  holdAnimation->addFrame(IMG("shield_1.bmp"));
  holdAnimation->addFrame(IMG("shield_2.bmp"));
  holdAnimation->addFrame(IMG("shield_3.bmp"));
  holdAnimation->addFrame(IMG("shield_4.bmp"));
  holdAnimation->setLoop(true);
  holdAnimation->setSpeed(6);
  
  this->toAwayState();
}


Shield::~Shield() {
  delete holdAnimation;
}


void Shield::toHoldState() {
  state = SHIELD_HOLD_STATE;
  animation = holdAnimation;
}


void Shield::toAwayState() {
  state = SHIELD_AWAY_STATE;
  animation = NULL;
}


bool Shield::held() {
  if (state == SHIELD_HOLD_STATE) {
    return true;
  }
  return false;
}

