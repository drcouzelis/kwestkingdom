#include "Enemy.h"


Enemy::Enemy() {
  team = ENEMY_TEAM;
  money = 1;
}


void
Enemy::dropItem() {
  
  //Heart *heart;
  MoneyBag *bag;
  //int num;
  
  //num = random_number(1, 3);
  
  //if (num == 1) {
    //heart = new Heart();
    //heart->setX(x);
    //heart->setY(y);
    //world->addItem(heart);
  //} else {
    bag = new MoneyBag();
    bag->setX(x);
    bag->setY(y);
    bag->setAmount(money);
    world->addItem(bag);
  //}
}

