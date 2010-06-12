#import "Character.h"
#import "Heart.h"


@implementation Heart


- init {
  
  self = [super init];
  
  if (self) {
    animation = [[Animation alloc] init];
    [animation addFrame: getImage(IMG_ITEMS_HEART)];
  }
  
  return self;
  
}


- collectedBy:(Character *)aCharacter {
  [aCharacter setHealth: [aCharacter getHealth] + 1];
  playSound(SND_HEART);
  return self;
}


@end

