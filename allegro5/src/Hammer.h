#ifndef HAMMER_HEADER
#define HAMMER_HEADER


#include "anim.h"
#include "Sprite.h"


typedef enum {

  HAMMER_HOLD_STATE,
  HAMMER_AWAY_STATE,

  HAMMER_ATTACK_UP_STATE,
  HAMMER_ATTACK_DOWN_STATE,
  HAMMER_ATTACK_LEFT_STATE,
  HAMMER_ATTACK_RIGHT_STATE,

  HAMMER_END_ATTACK_STATE

} HAMMER_STATE;


class Hammer : public Sprite {
  
  ANIM hold_anim;
  ANIM attack_up_anim;
  ANIM attack_down_anim;
  ANIM attack_left_anim;
  ANIM attack_right_anim;
  
public:

  Hammer();
  ~Hammer();

  void update();

  void setState(int aState);
  bool held();
};


#endif
