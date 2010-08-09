#import "MoneyBag.h"


@implementation MoneyBag


- init {

  self = [super init];

  if (self) {
    amount = 1;
    animation = [[Animation alloc] init];
    [animation addFrame: getImage(IMG_ITEMS_MONEYBAG)];
  }

  return self;

}


- collectedBy: (id<Livable, Moneyable>) character {
  [character setMoney: [character getMoney] + amount];
  playSound(SND_MONEY);
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

