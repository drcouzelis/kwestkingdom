#ifndef MONEYBAG_HEADER
#define MONEYBAG_HEADER


#include "Item.h"


class MoneyBag : public Item {

protected:

  ANIM money_bag_anim;
  int amount;

public:

  MoneyBag();

  void collectedBy(Character *character);

  int getAmount();
  void setAmount(int anAmount);
};


#endif
