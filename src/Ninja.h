#import "Enemy.h"
#import "Sword.h"


@interface Ninja : Enemy {

  Sword *sword;

  Animation *standAnimation;
  Animation *attackAnimation;
  Animation *dashAnimation;

}


@end
