#include "MoneyBag.h"


@implementation MoneyBag


- init {
  
  self = [super init];
  
  if (self) {
    amount = 1;
    animation = [[Animation alloc] init];
    [animation addFrame: getImage(IMAGES_MONEYBAG)];
  }
  
  return self;
  
}


- collectedBy: (Character *) character {
  [character setMoney: [character getMoney] + amount];
  playSound(SOUNDS_MONEY);
  return self;
}


- (int) getAmount {
  return amount;
}


- setAmount: (int) anAmount {
  amount = anAmount;
  if (amount < 0) {
    amount = 0;
  }
  return self;
}


@end

