#include "Character.h"
#include "KwestKingdom.h"


Character::Character() {
  turns = 0;
  health = 1;
  maxHealth = 3;
  money = 0;
  team = NO_TEAM;
  speed = getWalkSpeed();
  
}


bool Character::isDead() {
  if (health == 0) {
    return true;
  }
  return false;
}


void Character::setHealth(int theHealth) {
  health = theHealth;
  if (health < 0) {
    health = 0;
  } else if (health > maxHealth) {
    health = maxHealth;
  }

}


int Character::getHealth() {
  return health;
}


void Character::setMaxHealth(int theHealth) {
  maxHealth = theHealth;

}


int Character::getMaxHealth() {
  return maxHealth;
}


void Character::hurt() {
  health--;
  if (health < 0) {
    health = 0;
  }

}


bool Character::waiting() {
  if (turns > 0) {
    return true;
  }
  return false;
}


void Character::go() {
  turns--;
  if (turns < 0) {
    turns = 0;
  }

}


void Character::wait() {
  turns++;

}


void Character::setTeam(int aTeam) {
  team = aTeam;

}


int Character::getTeam() {
  return team;
}


int Character::getMoney() {
  return money;
}


void Character::setMoney(int amount) {
  money = amount;
  if (money < 0) {
    money = 0;
  } else if (money > 999) {
    money = 999;
  }

}



