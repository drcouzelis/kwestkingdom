#ifndef SWORD_HEADER
#define SWORD_HEADER


#include "Sprite.h"


class Sword : public Sprite {
 
protected:

  Animation *holdAnimation;
  Animation *attackUpAnimation;
  Animation *attackDownAnimation;
  Animation *attackLeftAnimation;
  Animation *attackRightAnimation;
  
public:

  Sword();
  ~Sword();

  bool held();

  void toHoldState();
  void toAwayState();

  // Deprecated
  void toAttackUpState();
  void toAttackDownState();
  void toAttackLeftState();
  void toAttackRightState();
};


#endif
