#import "Sprite.h"


@class Character;


@interface Powerup : Sprite
- collectedBy: (Character *) character;
@end

