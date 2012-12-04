#ifndef MONEYBAG_HEADER
#define MONEYBAG_HEADER


#include "Item.h"


class MoneyBag : public Item {
  int amount;
public:

  MoneyBag();

  int getAmount();
  void setAmount(int anAmount);
};


#endif
