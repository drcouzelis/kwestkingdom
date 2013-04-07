#ifndef HERO_HEADER
#define HERO_HEADER


#include "anim.h"
#include "Character.h"
#include "key_input.h"

class Bow;
class Shield;
class Sword;


#define MAX_HERO_HEALTH 3


class Hero : public Character {

protected:

  Shield *shield;
  Sword *sword;
  Bow *bow;
  
  ANIM stand_anim;
  ANIM begin_attack_anim;
  ANIM end_attack_anim;
  ANIM hurt_anim;
  ANIM dead_anim;
  
  char upKey;
  char downKey;
  char rightKey;
  char leftKey;
  char waitKey;
  char attackKey1;
  char attackKey2;
  char handKey;
  char shieldKey;
  char swordKey;
  char bowKey;
  
  int direction;
  
public:

  Hero();
  ~Hero();

  void update();
  void draw(IMAGE *canvas);

  virtual void hurt();
  virtual bool isDead();
  virtual void setX(int newX);
  virtual void setY(int newY);
  virtual void moveX(int newX);
  virtual void moveY(int newY);

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
