#import "Collectable.h"
#import "Sprite.h"


@interface MoneyBag : Sprite <Collectable> {
  int amount;
}


- (int) getAmount;
- setAmount: (int) anAmount;


@end
