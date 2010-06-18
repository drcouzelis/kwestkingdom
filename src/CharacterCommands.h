#import <objc/Object.h>

#import "Command.h"


@class Character2;


@interface WanderCommand : Command {
 @private
  Character2 *character;
  int prevDir;
}
- initCharacter:(Character2 *)aCharacter;
@end


@interface ChaseCommand : Command {
 @private
  Sprite2 *sprite;
}
@end
