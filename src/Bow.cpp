#include "Arrow.h"
#include "Bow.h"
#include "resources.h"


typedef enum {
  BOW_HOLD_STATE,
  BOW_AWAY_STATE
} BOW_STATE;


Bow::Bow() {
  
  arrow = NULL;
  
  holdAnimation = new Animation();
  holdAnimation->addFrame(IMG("bow_hold_1.bmp"));
  holdAnimation->addFrame(IMG("bow_hold_2.bmp"));
  holdAnimation->addFrame(IMG("bow_hold_3.bmp"));
  holdAnimation->addFrame(IMG("bow_hold_4.bmp"));
  holdAnimation->setLoop(true);
  holdAnimation->setSpeed(6);
  
  attackRightAnimation = new Animation();
  attackRightAnimation->addFrame(IMG("bow_draw_1.bmp"));
  attackRightAnimation->addFrame(IMG("bow_draw_2.bmp"));
  attackRightAnimation->addFrame(IMG("bow_draw_3.bmp"));
  attackRightAnimation->setLoop(false);
  attackRightAnimation->setSpeed(12);
  
  attackLeftAnimation = attackRightAnimation->copy()->setHorizontalFlip(true);
  attackDownAnimation = attackRightAnimation->copy()->setRotate(true);
  attackUpAnimation = attackRightAnimation->copy()->setHorizontalFlip(true)->setRotate(true);

  this->toAwayState();
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




