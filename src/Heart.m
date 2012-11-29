#import "Heart.h"


@implementation Heart


- init {
  
  self = [super init];
  
  if (self) {
    animation = [[Animation alloc] init];
    [animation addFrame: getImage(IMAGES_HEART)];
  }
  
  return self;
  
}


- collectedBy: (id<Livable, Moneyable>) character {
  [character setHealth: [character getHealth] + 1];
  playSound(SOUNDS_HEART);
  return self;
}


@end

