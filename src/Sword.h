#ifndef SWORD_HEADER
#define SWORD_HEADER


#include "Sprite.h"


class Sword : public Sprite {
 
protected:

  ANIM hold_anim;
  ANIM attack_up_anim;
  ANIM attack_down_anim;
  ANIM attack_left_anim;
  ANIM attack_right_anim;
  
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
