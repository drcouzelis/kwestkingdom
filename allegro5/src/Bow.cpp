#include "Arrow.h"
#include "Bow.h"
#include "resources.h"


typedef enum {
  BOW_HOLD_STATE,
  BOW_AWAY_STATE
} BOW_STATE;


Bow::Bow() {
  
  arrow = NULL;
  
  init_anim(&hold_anim, ON, 6);
  add_frame(&hold_anim, IMG("bow_hold_1.bmp"));
  add_frame(&hold_anim, IMG("bow_hold_2.bmp"));
  add_frame(&hold_anim, IMG("bow_hold_3.bmp"));
  add_frame(&hold_anim, IMG("bow_hold_4.bmp"));
  
  init_anim(&attack_right_anim, OFF, 12);
  add_frame(&attack_right_anim, IMG("bow_draw_1.bmp"));
  add_frame(&attack_right_anim, IMG("bow_draw_2.bmp"));
  add_frame(&attack_right_anim, IMG("bow_draw_3.bmp"));
  
  copy_anim(&attack_left_anim, &attack_right_anim);
  attack_left_anim.h_flip = ON;

  copy_anim(&attack_down_anim, &attack_right_anim);
  attack_down_anim.rotate = ON;

  copy_anim(&attack_up_anim, &attack_right_anim);
  attack_up_anim.h_flip = ON;
  attack_up_anim.rotate = ON;

  this->toAwayState();
}


Bow::~Bow() {
  delete arrow;
}


void Bow::update() {
  Sprite::update();

  if (arrow) {
    arrow->update();
  }
}


void Bow::draw(IMAGE * canvas) {
  Sprite::draw(canvas);

  if (arrow) {
    arrow->draw(canvas);
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
  anim = &hold_anim;
}


void Bow::toAwayState() {
  state = BOW_AWAY_STATE;
  anim = NULL;
}


void Bow::toAttackUpState() {
  anim = &attack_up_anim;
  reset_anim(anim);
}


void Bow::toAttackDownState() {
  anim = &attack_down_anim;
  reset_anim(anim);
}


void Bow::toAttackLeftState() {
  anim = &attack_left_anim;
  reset_anim(anim);
}


void Bow::toAttackRightState() {
  anim = &attack_right_anim;
  reset_anim(anim);
}


bool Bow::held() {
  if (state != BOW_AWAY_STATE) {
    return true;
  }
  return false;
}

