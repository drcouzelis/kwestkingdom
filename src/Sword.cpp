#include "Animation.h"
#include "KwestKingdom.h"
#include "Resources.h"
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
  holdAnimation->addFrame(getImage(IMAGES_SWORD_HOLD_1));
  holdAnimation->addFrame(getImage(IMAGES_SWORD_HOLD_2));
  holdAnimation->addFrame(getImage(IMAGES_SWORD_HOLD_3));
  holdAnimation->addFrame(getImage(IMAGES_SWORD_HOLD_4));
  holdAnimation->setLoop(true);
  holdAnimation->setSpeed(6);
  
  attackRightAnimation = new Animation();
  attackRightAnimation->addFrame(getImage(IMAGES_SWORD_STAB_1));
  attackRightAnimation->addFrame(getImage(IMAGES_SWORD_STAB_2));
  attackRightAnimation->addFrame(getImage(IMAGES_SWORD_STAB_3));
  attackRightAnimation->addFrame(getImage(IMAGES_SWORD_STAB_4));
  attackRightAnimation->addFrame(getImage(IMAGES_SWORD_STAB_3));
  attackRightAnimation->addFrame(getImage(IMAGES_SWORD_STAB_2));
  attackRightAnimation->addFrame(getImage(IMAGES_SWORD_STAB_1));
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
  playSound(SOUNDS_SWORD);
}


void Sword::toAttackDownState() {
  animation = attackDownAnimation;
  animation->reset();
  playSound(SOUNDS_SWORD);
}


void Sword::toAttackLeftState() {
  animation = attackLeftAnimation;
  animation->reset();
  playSound(SOUNDS_SWORD);
}


void Sword::toAttackRightState() {
  animation = attackRightAnimation;
  animation->reset();
  playSound(SOUNDS_SWORD);
}


bool Sword::held() {
  if (state == SWORD_HOLD_STATE) {
    return true;
  }
  return false;
}

