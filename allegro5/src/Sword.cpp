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
  
  init_anim(&hold_anim, ON, 6);
  add_frame(&hold_anim, IMG("sword_hold_1.bmp"));
  add_frame(&hold_anim, IMG("sword_hold_2.bmp"));
  add_frame(&hold_anim, IMG("sword_hold_3.bmp"));
  add_frame(&hold_anim, IMG("sword_hold_4.bmp"));
  
  init_anim(&attack_right_anim, OFF, 12);
  add_frame(&attack_right_anim, IMG("sword_stab_1.bmp"));
  add_frame(&attack_right_anim, IMG("sword_stab_2.bmp"));
  add_frame(&attack_right_anim, IMG("sword_stab_3.bmp"));
  add_frame(&attack_right_anim, IMG("sword_stab_4.bmp"));
  add_frame(&attack_right_anim, IMG("sword_stab_3.bmp"));
  add_frame(&attack_right_anim, IMG("sword_stab_2.bmp"));
  add_frame(&attack_right_anim, IMG("sword_stab_1.bmp"));
  attack_right_anim.offset_x = -TILE_SIZE;
  attack_right_anim.offset_y = -TILE_SIZE;
  
  copy_anim(&attack_left_anim, &attack_right_anim);
  attack_left_anim.h_flip = ON;

  copy_anim(&attack_down_anim, &attack_right_anim);
  attack_down_anim.rotate = ON;

  copy_anim(&attack_up_anim, &attack_right_anim);
  attack_up_anim.h_flip = ON;
  attack_up_anim.rotate = ON;
  
  this->toAwayState();
}


Sword::~Sword() {
}


void Sword::toHoldState() {
  state = SWORD_HOLD_STATE;
  anim = &hold_anim;
}


void Sword::toAwayState() {
  state = SWORD_AWAY_STATE;
  anim = NULL;
}


void Sword::toAttackUpState() {
  anim = &attack_up_anim;
  reset_anim(anim);
  play_sound(SND("sword.wav"));
}


void Sword::toAttackDownState() {
  anim = &attack_down_anim;
  reset_anim(anim);
  play_sound(SND("sword.wav"));
}


void Sword::toAttackLeftState() {
  anim = &attack_left_anim;
  reset_anim(anim);
  play_sound(SND("sword.wav"));
}


void Sword::toAttackRightState() {
  anim = &attack_right_anim;
  reset_anim(anim);
  play_sound(SND("sword.wav"));
}


bool Sword::held() {
  if (state == SWORD_HOLD_STATE) {
    return true;
  }
  return false;
}

