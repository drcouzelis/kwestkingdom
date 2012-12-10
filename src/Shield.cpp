#include "Animation.h"
#include "Resources.h"
#include "Shield.h"


typedef enum {
  SHIELD_HOLD_STATE,
  SHIELD_AWAY_STATE
} SHIELD_STATE;


Shield::Shield() {
  
  holdAnimation = new Animation();
  holdAnimation->addFrame(getImage(IMAGES_SHIELD_1));
  holdAnimation->addFrame(getImage(IMAGES_SHIELD_2));
  holdAnimation->addFrame(getImage(IMAGES_SHIELD_3));
  holdAnimation->addFrame(getImage(IMAGES_SHIELD_4));
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




