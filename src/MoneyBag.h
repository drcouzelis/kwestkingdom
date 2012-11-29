#ifndef MONEYBAG_HEADER
#define MONEYBAG_HEADER


#include "Collectable.h"
#include "Sprite.h"


@interface MoneyBag : Sprite <Collectable> {
  int amount;
}


- (int) getAmount;
- setAmount: (int) anAmount;


@end


#endif