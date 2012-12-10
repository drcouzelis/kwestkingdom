#include "Animation.h"
#include "Hammer.h"
#include "KwestKingdom.h"
#include "Resources.h"
#include "World.h"





Hammer::Hammer() {
  
  holdAnimation = new Animation();
  holdAnimation->addFrame(getImage(IMAGES_HAMMER_HOLD_1));
  holdAnimation->addFrame(getImage(IMAGES_HAMMER_HOLD_2));
  holdAnimation->addFrame(getImage(IMAGES_HAMMER_HOLD_3));
  holdAnimation->addFrame(getImage(IMAGES_HAMMER_HOLD_4));
  holdAnimation->setOffsetY(TILE_SIZE);
  holdAnimation->setLoop(true);
  holdAnimation->setSpeed(6);
  
  attackRightAnimation = new Animation();
  attackRightAnimation->addFrame(getImage(IMAGES_HAMMER_SWING_1));
  attackRightAnimation->addFrame(getImage(IMAGES_HAMMER_SWING_2));
  attackRightAnimation->addFrame(getImage(IMAGES_HAMMER_SWING_3));
  attackRightAnimation->addFrame(getImage(IMAGES_HAMMER_SWING_4));
  attackRightAnimation->addFrame(getImage(IMAGES_HAMMER_SWING_4));
  attackRightAnimation->addFrame(getImage(IMAGES_HAMMER_SWING_4));
  attackRightAnimation->addFrame(getImage(IMAGES_HAMMER_SWING_4));
  attackRightAnimation->addFrame(getImage(IMAGES_HAMMER_SWING_3));
  attackRightAnimation->addFrame(getImage(IMAGES_HAMMER_SWING_2));
  attackRightAnimation->addFrame(getImage(IMAGES_HAMMER_SWING_1));
  attackRightAnimation->setOffsetX(TILE_SIZE);
  attackRightAnimation->setLoop(false);
  attackRightAnimation->setSpeed(24);
  
  attackLeftAnimation = attackRightAnimation->copy()->setHorizontalFlip(true);
  attackLeftAnimation->setOffsetX(-TILE_SIZE * 2);
  attackDownAnimation = attackRightAnimation->copy()->setRotate(true);
  attackDownAnimation->setOffsetX(0);
  attackDownAnimation->setOffsetY(TILE_SIZE);
  attackUpAnimation = attackRightAnimation->copy()->setHorizontalFlip(true)->setVerticalFlip(true)->setRotate(true);
  attackUpAnimation->setOffsetX(-TILE_SIZE);
  attackUpAnimation->setOffsetY(-TILE_SIZE * 2);
  
  this->setState(HAMMER_AWAY_STATE);
  
}


Hammer::~Hammer() {
  delete holdAnimation;
  delete attackUpAnimation;
  delete attackDownAnimation;
  delete attackLeftAnimation;
  delete attackRightAnimation;
}


void Hammer::update() {
  
  Sprite::update();
  
  switch (state) {
  case HAMMER_ATTACK_UP_STATE:
  case HAMMER_ATTACK_DOWN_STATE:
  case HAMMER_ATTACK_LEFT_STATE:
  case HAMMER_ATTACK_RIGHT_STATE:
    if (animation->currentFrameNumber() == 3) {
      this->setState(HAMMER_END_ATTACK_STATE);
    }
    break;
  }
  

  
}



void Hammer::setState(int aState) {
  
  state = aState;
  
  switch (state) {
  
  case HAMMER_HOLD_STATE:
    animation = holdAnimation;
    break;
    
  case HAMMER_AWAY_STATE:
    animation = NULL;
    break;
    
  case HAMMER_ATTACK_UP_STATE:
    animation = attackUpAnimation;
    animation->reset();
    break;
    
  case HAMMER_ATTACK_DOWN_STATE:
    animation = attackDownAnimation;
    animation->reset();
    break;
    
  case HAMMER_ATTACK_LEFT_STATE:
    animation = attackLeftAnimation;
    animation->reset();
    break;
    
  case HAMMER_ATTACK_RIGHT_STATE:
    animation = attackRightAnimation;
    animation->reset();
    break;
    
  case HAMMER_END_ATTACK_STATE:
    playSound(SOUNDS_HAMMER);
    world->shake();
    break;
    
  }
  

  
}


bool Hammer::held() {
  if (state == HAMMER_HOLD_STATE) {
    return true;
  }
  return false;
}




