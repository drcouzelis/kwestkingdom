#include "Animation.h"
#include "Character.h"
#include "MoneyBag.h"
#include "resources.h"


MoneyBag::MoneyBag() {
  
  amount = 1;
  animation = new Animation();
  animation->addFrame(IMG("moneybag.bmp"));
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




