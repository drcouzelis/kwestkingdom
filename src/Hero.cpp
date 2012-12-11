#include "Animation.h"
#include "Arrow.h"
#include "Bow.h"
#include "Hero.h"
#include "KeyControl.h"
#include "KwestKingdom.h"
#include "Resources.h"
#include "Shield.h"
#include "Sword.h"
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
  health = 3;
  maxHealth = MAX_HERO_HEALTH;
  team = HERO_TEAM;
  
  shield = new Shield();
  sword = new Sword();
  bow = new Bow();
  
  shield->setSpeed(speed);
  sword->setSpeed(speed);
  bow->setSpeed(speed);
  
  standAnimation = new Animation();
  standAnimation->addFrame(getImage(IMAGES_HERO_STAND_1));
  standAnimation->addFrame(getImage(IMAGES_HERO_STAND_2));
  standAnimation->addFrame(getImage(IMAGES_HERO_STAND_3));
  standAnimation->addFrame(getImage(IMAGES_HERO_STAND_2));
  standAnimation->setLoop(true);
  standAnimation->setSpeed(6);
  
  beginAttackAnimation = new Animation();
  beginAttackAnimation->addFrame(getImage(IMAGES_HERO_ATTACK_1));
  beginAttackAnimation->addFrame(getImage(IMAGES_HERO_ATTACK_2));
  beginAttackAnimation->addFrame(getImage(IMAGES_HERO_ATTACK_3));
  beginAttackAnimation->addFrame(getImage(IMAGES_HERO_ATTACK_4));
  beginAttackAnimation->setLoop(false);
  beginAttackAnimation->setSpeed(HERO_ATTACK_SPEED);
  
  endAttackAnimation = new Animation();
  endAttackAnimation->addFrame(getImage(IMAGES_HERO_ATTACK_3));
  endAttackAnimation->addFrame(getImage(IMAGES_HERO_ATTACK_2));
  endAttackAnimation->addFrame(getImage(IMAGES_HERO_ATTACK_1));
  endAttackAnimation->setLoop(false);
  endAttackAnimation->setSpeed(HERO_ATTACK_SPEED);
  
  hurtAnimation = new Animation();
  hurtAnimation->addFrame(getImage(IMAGES_HERO_HURT_1));
  hurtAnimation->addFrame(getImage(IMAGES_HERO_HURT_2));
  hurtAnimation->addFrame(getImage(IMAGES_HERO_HURT_3));
  hurtAnimation->addFrame(getImage(IMAGES_HERO_HURT_4));
  hurtAnimation->addFrame(getImage(IMAGES_HERO_HURT_3));
  hurtAnimation->addFrame(getImage(IMAGES_HERO_HURT_2));
  hurtAnimation->addFrame(getImage(IMAGES_HERO_HURT_1));
  hurtAnimation->setLoop(false);
  hurtAnimation->setSpeed(12);
  
  deadAnimation = new Animation();
  deadAnimation->addFrame(getImage(IMAGES_HERO_DIE_1));
  deadAnimation->addFrame(getImage(IMAGES_HERO_DIE_2));
  deadAnimation->addFrame(getImage(IMAGES_HERO_DIE_3));
  deadAnimation->addFrame(getImage(IMAGES_HERO_DIE_4));
  deadAnimation->addFrame(getImage(IMAGES_HERO_DIE_5));
  deadAnimation->setLoop(false);
  deadAnimation->setSpeed(6);
  
  upKey = new KeyControl(KEY_UP);
  downKey = new KeyControl(KEY_DOWN);
  leftKey = new KeyControl(KEY_LEFT);
  rightKey = new KeyControl(KEY_RIGHT);
  waitKey = new KeyControl(KEY_SPACE);
  waitKey->setDelay(GAME_TICKER);
  attackKey = new KeyControl(KEY_LCONTROL);
  handKey = new KeyControl(KEY_0);
  handKey->setDelay(GAME_TICKER);
  shieldKey = new KeyControl(KEY_1);
  shieldKey->setDelay(GAME_TICKER);
  swordKey = new KeyControl(KEY_2);
  swordKey->setDelay(GAME_TICKER);
  bowKey = new KeyControl(KEY_3);
  swordKey->setDelay(GAME_TICKER);
  
  this->toStandState();
  sword->toHoldState();
  
  this->go(); // The hero doesn't wait! At least not when the game starts. ;-)
}


Hero::~Hero() {
  delete shield;
  delete sword;
  delete bow;
  delete standAnimation;
  delete beginAttackAnimation;
  delete endAttackAnimation;
  delete upKey;
  delete downKey;
  delete leftKey;
  delete rightKey;
  delete waitKey;
  delete attackKey;
  delete shieldKey;
  delete swordKey;
  delete bowKey;
  delete handKey;

}


void Hero::updateStandState() {
  
  int toX;
  int toY;
  
  // Handle item key input.
  // Update the items.
  if (shieldKey->isPressed()) {
    shield->toHoldState();
    sword->toAwayState();
    bow->toAwayState();
  } else if (swordKey->isPressed()) {
    shield->toAwayState();
    sword->toHoldState();
    bow->toAwayState();
  } else if (bowKey->isPressed()) {
    shield->toAwayState();
    sword->toAwayState();
    bow->toHoldState();
  } else if (handKey->isPressed()) {
    shield->toAwayState();
    sword->toAwayState();
    bow->toAwayState();
  }
  
  if (attackKey->isPressed()) {
    
    if (upKey->isPressed()) {
      direction = UP;
      this->toAttackState();
    } else if (downKey->isPressed()) {
      direction = DOWN;
      this->toAttackState();
    } else if (leftKey->isPressed()) {
      direction = LEFT;
      this->toAttackState();
    } else if (rightKey->isPressed()) {
      direction = RIGHT;
      this->toAttackState();
    }
    
  } else {
    
    // If you're not attacking with the attack key,
    // then maybe you are trying to walk...
    
    toX = x;
    toY = y;
    
    if (upKey->isPressed()) {
      toY--;
      if (sword->held() && world->isAttackable(team, x, y - 1)) {
        direction = UP;
        this->toAttackState();
      }
    } else if (downKey->isPressed()) {
      toY++;
      if (sword->held() && world->isAttackable(team, toX, toY)) {
        direction = DOWN;
        this->toAttackState();
      }
    } else if (leftKey->isPressed()) {
      toX--;
      if (sword->held() && world->isAttackable(team, toX, toY)) {
        direction = LEFT;
        this->toAttackState();
      }
    } else if (rightKey->isPressed()) {
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
  
  if (waitKey->isPressed()) {
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
    if (animation->isFinished()) {
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
    if (animation->isFinished()) {
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
    if (animation->isFinished()) {
      this->toStandState();
      sword->toHoldState();
      this->wait();
    }
    break;
    
  case HERO_DRAW_BOW_STATE:
    if (animation->isFinished()) {
      this->toShootArrowState();
    }
    break;
    
  case HERO_SHOOT_ARROW_STATE:
    if (animation->isFinished()) {
      animation = standAnimation;
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
  animation = standAnimation;

}


void Hero::toMoveState() {
  state = HERO_MOVE_STATE;
  animation = standAnimation;

}


void Hero::toAttackState() {
  state = HERO_ATTACK_STATE;
  animation = standAnimation;

}


void Hero::toHurtState() {
  
  state = HERO_HURT_STATE;
  animation = hurtAnimation;
  animation->reset();
  
  // You can't shoot an arrow if you get
  // hurt whil trying to do it.
  delete bow->getArrow();
  bow->setArrow(NULL);
  if (bow->held()) {
    bow->toHoldState();
  }
  
  playSound(SOUNDS_GASP);
  

  
}


void Hero::toDeadState() {
  state = HERO_DEAD_STATE;
  animation = deadAnimation;
  animation->reset();

}


void Hero::toPushSwordState() {
  state = HERO_PUSH_SWORD_STATE;
  animation = beginAttackAnimation;
  animation->reset();
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
  animation = endAttackAnimation;
  animation->reset();

}


void Hero::toDrawBowState() {
  
  state = HERO_DRAW_BOW_STATE;
  animation = beginAttackAnimation;
  animation->reset();
  
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
  animation = endAttackAnimation;
  animation->reset();
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
  if (state == HERO_DEAD_STATE && animation->isFinished()) {
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

