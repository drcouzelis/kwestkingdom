#import "Enemy.h"


@implementation Enemy


- init {

  self = [super init];

  if (self) {
    team = ENEMY_TEAM;
    money = 1;
  }

  return self;

}


- dropItem {

  //Heart *heart;
  MoneyBag *bag;
  //int num;

  //num = random_number(1, 3);

  //if (num == 1) {
    //heart = [[Heart alloc] init];
    //[heart setX: x];
    //[heart setY: y];
    //[world addItem: heart];
  //} else {
    bag = [[MoneyBag alloc] init];
    [bag setX: x];
    [bag setY: y];
    [bag setAmount: money];
    [world addItem: bag];
  //}

  return self;

}


@end

