#import <objc/Object.h>

#import "Command.h"


@class Animation;
@class Character2;


@interface CharacterCommand : Command {
 @protected
  Character2 *character;
  Animation *animation;
}
- setCharacter:(Character2 *)aCharacter;
- setAnimation:(Animation *)anAnimation;
@end


@interface WanderCommand : CharacterCommand {
 @private
  int prevDir;
}
@end


@interface ChaseCommand : CharacterCommand {
}
@end
