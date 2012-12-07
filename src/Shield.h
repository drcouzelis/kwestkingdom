#ifndef SHIELD_HEADER
#define SHIELD_HEADER


#include "Sprite.h"


class Shield : public Sprite {

protected:
  
  Animation *holdAnimation;
  
public:

  Shield();
  ~Shield();

  bool held();

  // Deprecated
  void toHoldState();
  void toAwayState();
};


#endif
