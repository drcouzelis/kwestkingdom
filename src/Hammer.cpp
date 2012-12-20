#include "Animation.h"
#include "Hammer.h"
#include "KwestKingdom.h"
#include "resources.h"
#include "World.h"





Hammer::Hammer() {
  
  holdAnimation = new Animation();
  holdAnimation->addFrame(IMG("hammer_hold_1.bmp"));
  holdAnimation->addFrame(IMG("hammer_hold_2.bmp"));
  holdAnimation->addFrame(IMG("hammer_hold_3.bmp"));
  holdAnimation->addFrame(IMG("hammer_hold_4.bmp"));
  holdAnimation->setOffsetY(TILE_SIZE);
  holdAnimation->setLoop(true);
  holdAnimation->setSpeed(6);
  
  attackRightAnimation = new Animation();
  attackRightAnimation->addFrame(IMG("hammer_swing_1.bmp"));
  attackRightAnimation->addFrame(IMG("hammer_swing_2.bmp"));
  attackRightAnimation->addFrame(IMG("hammer_swing_3.bmp"));
  attackRightAnimation->addFrame(IMG("hammer_swing_4.bmp"));
  attackRightAnimation->addFrame(IMG("hammer_swing_4.bmp"));
  attackRightAnimation->addFrame(IMG("hammer_swing_4.bmp"));
  attackRightAnimation->addFrame(IMG("hammer_swing_4.bmp"));
  attackRightAnimation->addFrame(IMG("hammer_swing_3.bmp"));
  attackRightAnimation->addFrame(IMG("hammer_swing_2.bmp"));
  attackRightAnimation->addFrame(IMG("hammer_swing_1.bmp"));
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
    play_sound(SND("hammer.wav"));
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

