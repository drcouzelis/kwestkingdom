#ifndef SHIELD_HEADER
#define SHIELD_HEADER


#include "Sprite.h"


class Shield : public Sprite {
  
  Animation *holdAnimation;
  
public:


  (bool) held;

// Deprecated
  toHoldState;
  toAwayState;


};


#endif