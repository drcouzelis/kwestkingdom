#include "Animation.h"
#include "KwestKingdom.h"
#include "resources.h"
#include "Sword.h"


typedef enum {
  SWORD_HOLD_STATE,
  SWORD_AWAY_STATE
} SWORD_STATE;

typedef enum {
  SWORD_ATTACK_UP_STATE,
  SWORD_ATTACK_DOWN_STATE,
  SWORD_ATTACK_LEFT_STATE,
  SWORD_ATTACK_RIGHT_STATE
} SWORD_ATTACK_STATE;





Sword::Sword() {
  
  holdAnimation = new Animation();
  holdAnimation->addFrame(IMG("sword_hold_1.bmp"));
  holdAnimation->addFrame(IMG("sword_hold_2.bmp"));
  holdAnimation->addFrame(IMG("sword_hold_3.bmp"));
  holdAnimation->addFrame(IMG("sword_hold_4.bmp"));
  holdAnimation->setLoop(true);
  holdAnimation->setSpeed(6);
  
  attackRightAnimation = new Animation();
  attackRightAnimation->addFrame(IMG("sword_stab_1.bmp"));
  attackRightAnimation->addFrame(IMG("sword_stab_2.bmp"));
  attackRightAnimation->addFrame(IMG("sword_stab_3.bmp"));
  attackRightAnimation->addFrame(IMG("sword_stab_4.bmp"));
  attackRightAnimation->addFrame(IMG("sword_stab_3.bmp"));
  attackRightAnimation->addFrame(IMG("sword_stab_2.bmp"));
  attackRightAnimation->addFrame(IMG("sword_stab_1.bmp"));
  attackRightAnimation->setOffsetX(-TILE_SIZE);
  attackRightAnimation->setOffsetY(-TILE_SIZE);
  attackRightAnimation->setLoop(false);
  attackRightAnimation->setSpeed(12);
  
  attackLeftAnimation = attackRightAnimation->copy()->setHorizontalFlip(true);
  attackDownAnimation = attackRightAnimation->copy()->setRotate(true);
  attackUpAnimation = attackRightAnimation->copy()->setHorizontalFlip(true)->setRotate(true);
  
  this->toAwayState();
}


Sword::~Sword() {
  delete holdAnimation;
  delete attackUpAnimation;
  delete attackDownAnimation;
  delete attackLeftAnimation;
  delete attackRightAnimation;
}


void Sword::toHoldState() {
  state = SWORD_HOLD_STATE;
  animation = holdAnimation;
}


void Sword::toAwayState() {
  state = SWORD_AWAY_STATE;
  animation = NULL;
}


void Sword::toAttackUpState() {
  animation = attackUpAnimation;
  animation->reset();
  play_sound(SND("sword.wav"));
}


void Sword::toAttackDownState() {
  animation = attackDownAnimation;
  animation->reset();
  play_sound(SND("sword.wav"));
}


void Sword::toAttackLeftState() {
  animation = attackLeftAnimation;
  animation->reset();
  play_sound(SND("sword.wav"));
}


void Sword::toAttackRightState() {
  animation = attackRightAnimation;
  animation->reset();
  play_sound(SND("sword.wav"));
}


bool Sword::held() {
  if (state == SWORD_HOLD_STATE) {
    return true;
  }
  return false;
}

