#include "Animation.h"
#include "Character.h"
#include "MoneyBag.h"
#include "Resources.h"


MoneyBag::MoneyBag() {
  
  amount = 1;
  animation = new Animation();
  animation->addFrame(IMG("MONEYBAG"));
}


void MoneyBag::collectedBy(Character * character) {
  character->setMoney(character->getMoney() + amount);
  playSound(SOUNDS_MONEY);

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




