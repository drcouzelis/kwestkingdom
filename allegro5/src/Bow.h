#ifndef BOW_HEADER
#define BOW_HEADER


#include "Sprite.h"

class Arrow;
class World;


class Bow : public Sprite {
  
  Arrow *arrow;
  
  ANIM hold_anim;
  ANIM attack_up_anim;
  ANIM attack_down_anim;
  ANIM attack_left_anim;
  ANIM attack_right_anim;
  
public:

  Bow();
  ~Bow();

  void update();
  void draw(IMAGE *canvas);

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
