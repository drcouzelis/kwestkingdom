#ifndef BOW_HEADER
#define BOW_HEADER


#include "Sprite.h"

class Arrow;
class World;


class Bow : public Sprite {
  
  Arrow *arrow;
  
  Animation *holdAnimation;
  Animation *attackUpAnimation;
  Animation *attackDownAnimation;
  Animation *attackLeftAnimation;
  Animation *attackRightAnimation;
  
public:

  Bow();
  ~Bow();

  void setArrow(Arrow *anArrow);
  Arrow *getArrow();

  void setArrow(int newX, int newY, int aDirection, int aTeam, World *aWorld);

  bool held();

  // State control
  void toHoldState();
  void toAwayState();
  void toAttackUpState();
  void toAttackDownState();
  void toAttackLeftState();
  void toAttackRightState();
};


#endif
