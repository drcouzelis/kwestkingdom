#include "Arrow.h"
#include "Bow.h"
#include "Hero.h"
#include "KwestKingdom.h"
#include "resources.h"
#include "Shield.h"
#include "Sword.h"
#include "utilities.h"
#include "World.h"


#define HERO_ATTACK_SPEED 12


typedef enum {
  HERO_STAND_STATE,
  HERO_MOVE_STATE,
  HERO_ATTACK_STATE,
  HERO_HURT_STATE,
  HERO_DEAD_STATE,
  HERO_PUSH_SWORD_STATE,
  HERO_PULL_SWORD_STATE,
  HERO_DRAW_BOW_STATE,
  HERO_SHOOT_ARROW_STATE
} HERO_STATE;


Hero::Hero() {
  
  speed = getWalkSpeed(); // In FPS
  health = 1; //3;
  maxHealth = MAX_HERO_HEALTH;
  team = HERO_TEAM;
  
  shield = new Shield();
  sword = new Sword();
  bow = new Bow();
  
  shield->setSpeed(speed);
  sword->setSpeed(speed);
  bow->setSpeed(speed);
  
  init_anim(&stand_anim, ON, 6);
  add_frame(&stand_anim, IMG("hero_stand_1.bmp"));
  add_frame(&stand_anim, IMG("hero_stand_2.bmp"));
  add_frame(&stand_anim, IMG("hero_stand_3.bmp"));
  add_frame(&stand_anim, IMG("hero_stand_2.bmp"));
  
  init_anim(&begin_attack_anim, OFF, HERO_ATTACK_SPEED);
  add_frame(&begin_attack_anim, IMG("hero_attack_1.bmp"));
  add_frame(&begin_attack_anim, IMG("hero_attack_2.bmp"));
  add_frame(&begin_attack_anim, IMG("hero_attack_3.bmp"));
  add_frame(&begin_attack_anim, IMG("hero_attack_4.bmp"));
  
  init_anim(&end_attack_anim, OFF, HERO_ATTACK_SPEED);
  add_frame(&end_attack_anim, IMG("hero_attack_3.bmp"));
  add_frame(&end_attack_anim, IMG("hero_attack_2.bmp"));
  add_frame(&end_attack_anim, IMG("hero_attack_1.bmp"));
  
  init_anim(&hurt_anim, OFF, HERO_ATTACK_SPEED);
  add_frame(&hurt_anim, IMG("hero_hurt_1.bmp"));
  add_frame(&hurt_anim, IMG("hero_hurt_2.bmp"));
  add_frame(&hurt_anim, IMG("hero_hurt_3.bmp"));
  add_frame(&hurt_anim, IMG("hero_hurt_4.bmp"));
  add_frame(&hurt_anim, IMG("hero_hurt_3.bmp"));
  add_frame(&hurt_anim, IMG("hero_hurt_2.bmp"));
  add_frame(&hurt_anim, IMG("hero_hurt_1.bmp"));
  
  init_anim(&dead_anim, OFF, 6);
  add_frame(&dead_anim, IMG("hero_die_1.bmp"));
  add_frame(&dead_anim, IMG("hero_die_2.bmp"));
  add_frame(&dead_anim, IMG("hero_die_3.bmp"));
  add_frame(&dead_anim, IMG("hero_die_4.bmp"));
  add_frame(&dead_anim, IMG("hero_die_5.bmp"));
  
  init_key_input(&upKey, KEY_UP, 0);
  init_key_input(&downKey, KEY_DOWN, 0);
  init_key_input(&leftKey, KEY_LEFT, 0);
  init_key_input(&rightKey, KEY_RIGHT, 0);
  init_key_input(&waitKey, KEY_SPACE, GAME_TICKER);
  init_key_input(&attackKey1, KEY_LCONTROL, 0);
  init_key_input(&attackKey2, KEY_RCONTROL, 0);
  init_key_input(&handKey, KEY_0, GAME_TICKER);
  init_key_input(&shieldKey, KEY_1, GAME_TICKER);
  init_key_input(&swordKey, KEY_2, GAME_TICKER);
  init_key_input(&bowKey, KEY_3, GAME_TICKER);
  
  this->toStandState();
  sword->toHoldState();
  
  this->go(); // The hero doesn't wait! At least not when the game starts. ;-)
}


Hero::~Hero() {
  delete shield;
  delete sword;
  delete bow;
}


void Hero::updateStandState() {
  
  int toX;
  int toY;
  
  // Handle item key input.
  // Update the items.
  if (is_key_pressed(&shieldKey)) {
    shield->toHoldState();
    sword->toAwayState();
    bow->toAwayState();
  } else if (is_key_pressed(&swordKey)) {
    shield->toAwayState();
    sword->toHoldState();
    bow->toAwayState();
  } else if (is_key_pressed(&bowKey)) {
    shield->toAwayState();
    sword->toAwayState();
    bow->toHoldState();
  } else if (is_key_pressed(&handKey)) {
    shield->toAwayState();
    sword->toAwayState();
    bow->toAwayState();
  }
  
  if (is_key_pressed(&attackKey1) || is_key_pressed(&attackKey2)) {
    
    if (is_key_pressed(&upKey)) {
      direction = UP;
      this->toAttackState();
    } else if (is_key_pressed(&downKey)) {
      direction = DOWN;
      this->toAttackState();
    } else if (is_key_pressed(&leftKey)) {
      direction = LEFT;
      this->toAttackState();
    } else if (is_key_pressed(&rightKey)) {
      direction = RIGHT;
      this->toAttackState();
    }
    
  } else {
    
    // If you're not attacking with the attack key,
    // then maybe you are trying to walk...
    
    toX = x;
    toY = y;
    
    if (is_key_pressed(&upKey)) {
      toY--;
      if (sword->held() && world->isAttackable(team, x, y - 1)) {
        direction = UP;
        this->toAttackState();
      }
    } else if (is_key_pressed(&downKey)) {
      toY++;
      if (sword->held() && world->isAttackable(team, toX, toY)) {
        direction = DOWN;
        this->toAttackState();
      }
    } else if (is_key_pressed(&leftKey)) {
      toX--;
      if (sword->held() && world->isAttackable(team, toX, toY)) {
        direction = LEFT;
        this->toAttackState();
      }
    } else if (is_key_pressed(&rightKey)) {
      toX++;
      if (sword->held() && world->isAttackable(team, toX, toY)) {
        direction = RIGHT;
        this->toAttackState();
      }
    }
    
    if (world->isWalkable(toX, toY) && !world->isInhabited(toX, toY)) {
      
      this->moveX(toX);
      this->moveY(toY);
      this->toMoveState();
      this->wait();
      
      // If the hero is holding the shield
      // then make him wait another turn.
      if (shield->held()) {
        this->wait();
      }
    }
    
  }
}


void Hero::update() {
  
  Character::update();
  shield->update();
  sword->update();
  bow->update();
  
  if (this->waiting()) {
    return;
  }
  
  if (is_key_pressed(&waitKey)) {
    this->wait();
  }
  
  switch (state) {
  
  case HERO_STAND_STATE:
    this->updateStandState();
    break;
    
  case HERO_MOVE_STATE:
    if (!this->moving()) {
      this->toStandState();
    }
    break;
    
  case HERO_ATTACK_STATE:
    if (sword->held()) {
      this->toPushSwordState();
    } else if (bow->held()) {
      this->toDrawBowState();
      this->wait();
    }else {
      this->toStandState();
    }
    break;
  
  case HERO_HURT_STATE:
    if (anim->done) {
      if (health == 0) {
        shield->toAwayState();
        sword->toAwayState();
        bow->toAwayState();
        this->toDeadState();
      } else {
        this->toStandState();
      }
    }
    break;
  
  case HERO_DEAD_STATE:
    // You are not going to do anything once you enter
    // the state of being dead.
    break;
      
  case HERO_PUSH_SWORD_STATE:
    if (anim->done) {
      switch (direction) {
      case UP:
        world->attackFromTeam(team, x, y - 1);
        break;
      case DOWN:
        world->attackFromTeam(team, x, y + 1);
        break;
      case LEFT:
        world->attackFromTeam(team, x - 1, y);
        break;
      case RIGHT:
        world->attackFromTeam(team, x + 1, y);
        break;
      }
      this->toPullSwordState();
    }
    break;
    
  case HERO_PULL_SWORD_STATE:
    if (anim->done) {
      this->toStandState();
      sword->toHoldState();
      this->wait();
    }
    break;
    
  case HERO_DRAW_BOW_STATE:
    if (anim->done) {
      this->toShootArrowState();
    }
    break;
    
  case HERO_SHOOT_ARROW_STATE:
    if (anim->done) {
      anim = &stand_anim;
      bow->toHoldState();
    }
    if (bow->getArrow()->stopped()) {
      delete bow->getArrow();
      bow->setArrow(NULL);
      this->toStandState();
      this->wait();
    }
    break;
  }
}


void Hero::draw(BITMAP * buffer) {
  Character::draw(buffer);
  shield->draw(buffer);
  sword->draw(buffer);
  bow->draw(buffer);
}


void Hero::emptyHands() {
  shield->toAwayState();
  sword->toAwayState();
  bow->toAwayState();

}


void Hero::toStandState() {
  state = HERO_STAND_STATE;
  anim = &stand_anim;
}


void Hero::toMoveState() {
  state = HERO_MOVE_STATE;
  anim = &stand_anim;
}


void Hero::toAttackState() {
  state = HERO_ATTACK_STATE;
  anim = &stand_anim;
}


void Hero::toHurtState() {
  
  state = HERO_HURT_STATE;
  anim = &hurt_anim;
  reset_anim(anim);
  
  // You can't shoot an arrow if you get
  // hurt whil trying to do it.
  delete bow->getArrow();
  bow->setArrow(NULL);
  if (bow->held()) {
    bow->toHoldState();
  }
  
  play_sound(SND("gasp.wav"));
}


void Hero::toDeadState() {
  state = HERO_DEAD_STATE;
  anim = &dead_anim;
  reset_anim(anim);
}


void Hero::toPushSwordState() {
  state = HERO_PUSH_SWORD_STATE;
  anim = &begin_attack_anim;
  reset_anim(anim);
  switch (direction) {
  case UP:
    sword->toAttackUpState();
    break;
  case DOWN:
    sword->toAttackDownState();
    break;
  case LEFT:
    sword->toAttackLeftState();
    break;
  case RIGHT:
    sword->toAttackRightState();
    break;
  }
}


void Hero::toPullSwordState() {
  state = HERO_PULL_SWORD_STATE;
  anim = &end_attack_anim;
  reset_anim(anim);
}


void Hero::toDrawBowState() {
  
  state = HERO_DRAW_BOW_STATE;
  anim = &begin_attack_anim;
  reset_anim(anim);
  
  switch (direction) {
  case UP:
    bow->toAttackUpState();
    break;
  case DOWN:
    bow->toAttackDownState();
    break;
  case LEFT:
    bow->toAttackLeftState();
    break;
  case RIGHT:
    bow->toAttackRightState();
    break;
  }
  
  bow->setArrow(x, y, direction, team, world);
  

  
}


void Hero::toShootArrowState() {
  state = HERO_SHOOT_ARROW_STATE;
  anim = &end_attack_anim;
  reset_anim(anim);
  bow->getArrow()->toFlyingState();
  bow->toHoldState();

}


void Hero::hurt() {
  if (!shield->held()) {
    this->toHurtState();
    Character::hurt();
  }

}


bool Hero::isDead() {
  if (state == HERO_DEAD_STATE && anim->done) {
    return true;
  }
  return false;
}


void Hero::setX(int newX) {
  Character::setX(newX);
  shield->setX(newX);
  sword->setX(newX);
  bow->setX(newX);

}


void Hero::setY(int newY) {
  Character::setY(newY);
  shield->setY(newY);
  sword->setY(newY);
  bow->setY(newY);

}


void Hero::moveX(int newX) {
  Character::moveX(newX);
  shield->moveX(newX);
  sword->moveX(newX);
  bow->moveX(newX);

}


void Hero::moveY(int newY) {
  Character::moveY(newY);
  shield->moveY(newY);
  sword->moveY(newY);
  bow->moveY(newY);

}

