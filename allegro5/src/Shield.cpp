#include "resources.h"
#include "Shield.h"


typedef enum {
  SHIELD_HOLD_STATE,
  SHIELD_AWAY_STATE
} SHIELD_STATE;


Shield::Shield() {
  
  init_anim(&hold_anim, ON, 6);
  add_frame(&hold_anim, IMG("shield_1.bmp"));
  add_frame(&hold_anim, IMG("shield_2.bmp"));
  add_frame(&hold_anim, IMG("shield_3.bmp"));
  add_frame(&hold_anim, IMG("shield_4.bmp"));
  
  this->toAwayState();
}


Shield::~Shield() {
}


void Shield::toHoldState() {
  state = SHIELD_HOLD_STATE;
  anim = &hold_anim;
  reset_anim(anim);
}


void Shield::toAwayState() {
  state = SHIELD_AWAY_STATE;
  anim = NULL;
}


bool Shield::held() {
  if (state == SHIELD_HOLD_STATE) {
    return true;
  }
  return false;
}

