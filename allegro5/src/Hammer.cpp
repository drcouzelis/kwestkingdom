#include "Hammer.h"
#include "KwestKingdom.h"
#include "resources.h"
#include "World.h"


Hammer::Hammer() {
  
  init_anim(&hold_anim, ON, 6);
  add_frame(&hold_anim, IMG("hammer_hold_1.bmp"));
  add_frame(&hold_anim, IMG("hammer_hold_2.bmp"));
  add_frame(&hold_anim, IMG("hammer_hold_3.bmp"));
  add_frame(&hold_anim, IMG("hammer_hold_4.bmp"));
  hold_anim.offset_y = TILE_SIZE;
  
  init_anim(&attack_right_anim, OFF, 24);
  add_frame(&attack_right_anim, IMG("hammer_swing_1.bmp"));
  add_frame(&attack_right_anim, IMG("hammer_swing_2.bmp"));
  add_frame(&attack_right_anim, IMG("hammer_swing_3.bmp"));
  add_frame(&attack_right_anim, IMG("hammer_swing_4.bmp"));
  add_frame(&attack_right_anim, IMG("hammer_swing_4.bmp"));
  add_frame(&attack_right_anim, IMG("hammer_swing_4.bmp"));
  add_frame(&attack_right_anim, IMG("hammer_swing_4.bmp"));
  add_frame(&attack_right_anim, IMG("hammer_swing_3.bmp"));
  add_frame(&attack_right_anim, IMG("hammer_swing_2.bmp"));
  add_frame(&attack_right_anim, IMG("hammer_swing_1.bmp"));
  attack_right_anim.offset_x = TILE_SIZE;
  
  copy_anim(&attack_left_anim, &attack_right_anim);
  attack_left_anim.h_flip = ON;
  attack_left_anim.offset_x = -TILE_SIZE * 2;

  copy_anim(&attack_down_anim, &attack_right_anim);
  attack_down_anim.rotate = ON;
  attack_down_anim.offset_x = 0;
  attack_down_anim.offset_y = TILE_SIZE;

  copy_anim(&attack_up_anim, &attack_right_anim);
  attack_up_anim.h_flip = ON;
  attack_up_anim.v_flip = ON;
  attack_up_anim.rotate = ON;
  attack_up_anim.offset_x = -TILE_SIZE;
  attack_up_anim.offset_y = -TILE_SIZE * 2;
  
  this->setState(HAMMER_AWAY_STATE);
}


Hammer::~Hammer() {
}


void Hammer::update() {
  
  Sprite::update();
  
  switch (state) {
  case HAMMER_ATTACK_UP_STATE:
  case HAMMER_ATTACK_DOWN_STATE:
  case HAMMER_ATTACK_LEFT_STATE:
  case HAMMER_ATTACK_RIGHT_STATE:
    if (anim->pos == 3) {
      this->setState(HAMMER_END_ATTACK_STATE);
    }
    break;
  }
}



void Hammer::setState(int aState) {
  
  state = aState;
  
  switch (state) {
  
  case HAMMER_HOLD_STATE:
    anim = &hold_anim;
    break;
    
  case HAMMER_AWAY_STATE:
    anim = NULL;
    break;
    
  case HAMMER_ATTACK_UP_STATE:
    anim = &attack_up_anim;
    reset_anim(anim);
    break;
    
  case HAMMER_ATTACK_DOWN_STATE:
    anim = &attack_down_anim;
    reset_anim(anim);
    break;
    
  case HAMMER_ATTACK_LEFT_STATE:
    anim = &attack_left_anim;
    reset_anim(anim);
    break;
    
  case HAMMER_ATTACK_RIGHT_STATE:
    anim = &attack_right_anim;
    reset_anim(anim);
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

