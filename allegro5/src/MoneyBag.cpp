#include "Character.h"
#include "MoneyBag.h"
#include "resources.h"


MoneyBag::MoneyBag() {
  amount = 1;

  init_anim(&money_bag_anim, OFF, 0);
  add_frame(&money_bag_anim, IMG("moneybag.bmp"));

  anim = &money_bag_anim;
}


void MoneyBag::collectedBy(Character * character) {
  character->setMoney(character->getMoney() + amount);
  play_sound(SND("money.wav"));
}


int MoneyBag::getAmount() {
  return amount;
}


void MoneyBag::setAmount(int anAmount) {
  amount = anAmount;
  if (amount < 0) {
    amount = 0;
  }

}




