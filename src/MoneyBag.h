#ifndef MONEYBAG_HEADER
#define MONEYBAG_HEADER


#include "Collectable.h"
#include "Sprite.h"


class MoneyBag : public Sprite <Collectable> {
  int amount;
public:


  (int) getAmount;
  setAmount: (int) anAmount;


};


#endif