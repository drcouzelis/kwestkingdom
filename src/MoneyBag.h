#ifndef MONEYBAG_HEADER
#define MONEYBAG_HEADER


#include "Collectable.h"
#include "Sprite.h"


class MoneyBag : public Sprite, public Collectable {
  int amount;
public:

  MoneyBag();

  int getAmount();
  void setAmount(int anAmount);
};


#endif
