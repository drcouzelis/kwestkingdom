#import "Animation.h"
#import "Character2.h"
#import "CharacterState.h"
#import "KwestKingdom.h"
#import "Sprite2.h"


@implementation CharacterState


- initCharacter:(Character2 *)aCharacter
    environment:(id<Environment>)anEnvironment
      animation:(Animation *)anAnimation {
  if ([super init]) {
    character = aCharacter;
    environment = anEnvironment;
    animation = anAnimation;
  }
  return self;
}


- start {
  [[character sprite] setAnimation:animation];
  return [super start];
}


@end


@implementation WanderState


- update {

  Sprite2 *sprite = [character sprite];

  // Pick a random direction to head
  int dir = random_number(UP, LEFT);

  int x = [sprite x];
  int y = [sprite y];

  if (dir == UP) {
    y--;
  } else if (dir == DOWN) {
    y++;
  } else if (dir == RIGHT) {
    x++;
  } else if (dir == LEFT) {
    x--;
  }

  if ([environment isWalkableAtX:x y:y] && ![environment isInhabitedAtX:x y:y]) {
    [sprite moveToX:x];
    [sprite moveToY:y];
  }

  // Bound him so he doesn't wander right out of the screen!
  [sprite boundAtTop:1 bottom:ROWS - 2 left:1 right:COLS - 2];

  prevDir = dir;

  [character wait];

  return self;
}


@end


@implementation ChaseState


- execute {
  return self;
}


@end
