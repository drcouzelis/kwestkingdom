#ifndef ARROW_HEADER
#define ARROW_HEADER


#include "Character.h"


class Arrow : public Character {
 
protected:

  ANIM fly_up_anim;
  ANIM fly_down_anim;
  ANIM fly_left_anim;
  ANIM fly_right_anim;
  
  int direction;
  
public:

  Arrow();
  ~Arrow();

  void update();

  bool isInsideScreen();
  void findTarget();
  void setDirection(int aDirection);
 
  bool stopped();

  // Deprecated
  void toHoldState();
  void toFlyingState();
  void toStoppedState();
};


#endif
