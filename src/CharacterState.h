#import <objc/Object.h>

#import "Environment.h"
#import "State.h"


@class Animation;
@class Character2;


@interface CharacterState : State {
 @protected
  Character2 *character;
  id<Environment> environment;
  Animation *animation;
}
- initCharacter:(Character2 *)aCharacter
    environment:(id<Environment>)anEnvironment
      animation:(Animation *)anAnimation;
@end


@interface WanderState : CharacterState {
 @private
  int prevDir;
}
@end


@interface ChaseState : CharacterState {
}
@end
