#ifndef HERO_HEADER
#define HERO_HEADER


#include "Arrow.h"
#include "Bow.h"
#include "Character.h"
#include "KeyControl.h"
#include "Resources.h"
#include "Shield.h"
#include "Sword.h"


#define MAX_HERO_HEALTH 3


class Hero : public Character {
  
  Shield *shield;
  Sword *sword;
  Bow *bow;
  
  Animation *standAnimation;
  Animation *beginAttackAnimation;
  Animation *endAttackAnimation;
  Animation *hurtAnimation;
  Animation *deadAnimation;
  
  KeyControl *upKey;
  KeyControl *downKey;
  KeyControl *rightKey;
  KeyControl *leftKey;
  KeyControl *waitKey;
  KeyControl *attackKey;
  KeyControl *handKey;
  KeyControl *shieldKey;
  KeyControl *swordKey;
  KeyControl *bowKey;
  
  int direction;
  
public:

  Hero();
  ~Hero();

  void emptyHands();

  // Updates
  void updateStandState();

  // State control
  void toStandState();
  void toMoveState();
  void toAttackState();
  void toHurtState();
  void toDeadState();
  void toPushSwordState();
  void toPullSwordState();
  void toDrawBowState();
  void toShootArrowState();
};


#endif
