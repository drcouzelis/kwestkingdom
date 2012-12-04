#ifndef ARROW_HEADER
#define ARROW_HEADER


#include "Character.h"
#include "Resources.h"


class Arrow : public Character {
 
protected:

  Animation *flyUpAnimation;
  Animation *flyDownAnimation;
  Animation *flyLeftAnimation;
  Animation *flyRightAnimation;
  
  int direction;
  
public:

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
