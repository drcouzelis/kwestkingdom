#include "Animation.h"
#include "Arrow.h"
#include "Bow.h"
#include "Resources.h"


typedef enum {
  BOW_HOLD_STATE,
  BOW_AWAY_STATE
} BOW_STATE;





Bow::Bow() {
  
    arrow = NULL;
    
    holdAnimation = new Animation();
    holdAnimation->addFrame(getImage(IMAGES_BOW_HOLD_1));
    holdAnimation->addFrame(getImage(IMAGES_BOW_HOLD_2));
    holdAnimation->addFrame(getImage(IMAGES_BOW_HOLD_3));
    holdAnimation->addFrame(getImage(IMAGES_BOW_HOLD_4));
    holdAnimation->setLoop(true);
    holdAnimation->setSpeed(6);
	
    attackRightAnimation = new Animation();
    attackRightAnimation->addFrame(getImage(IMAGES_BOW_DRAW_1));
    attackRightAnimation->addFrame(getImage(IMAGES_BOW_DRAW_2));
    attackRightAnimation->addFrame(getImage(IMAGES_BOW_DRAW_3));
    attackRightAnimation->setLoop(false);
    attackRightAnimation->setSpeed(12);
	
    attackLeftAnimation = attackRightAnimation->copy()->setHorizontalFlip(true);
    attackDownAnimation = attackRightAnimation->copy()->setRotate(true);
    attackUpAnimation = attackRightAnimation->copy()->setHorizontalFlip(true)->setRotate(true);
}


Bow::~Bow() {
  delete holdAnimation;
  delete attackUpAnimation;
  delete attackDownAnimation;
  delete attackLeftAnimation;
  delete attackRightAnimation;
  delete arrow;
}


void Bow::update() {
  Sprite::update();

  if (arrow) {
    arrow->update();
  }
}


void Bow::draw(BITMAP * buffer) {
  Sprite::draw(buffer);

  if (arrow) {
    arrow->draw(buffer);
  }
}


void Bow::setArrow(Arrow * anArrow) {
  arrow = anArrow;
}


Arrow * Bow::getArrow() {
  return arrow;
}


void Bow::setArrow(int newX, int newY, int aDirection, int aTeam, World *aWorld) {
  
  arrow = new Arrow();
  arrow->setTeam(aTeam);
  arrow->setX(newX);
  arrow->setY(newY);
  arrow->setWorld(aWorld);
  arrow->setDirection(aDirection);
  arrow->toHoldState();
}


void Bow::toHoldState() {
  state = BOW_HOLD_STATE;
  animation = holdAnimation;
}


void Bow::toAwayState() {
  state = BOW_AWAY_STATE;
  animation = NULL;
}


void Bow::toAttackUpState() {
  animation = attackUpAnimation;
  animation->reset();
}


void Bow::toAttackDownState() {
  animation = attackDownAnimation;
  animation->reset();
}


void Bow::toAttackLeftState() {
  animation = attackLeftAnimation;
  animation->reset();
}


void Bow::toAttackRightState() {
  animation = attackRightAnimation;
  animation->reset();
}


bool Bow::held() {
  if (state != BOW_AWAY_STATE) {
    return true;
  }
  return false;
}




