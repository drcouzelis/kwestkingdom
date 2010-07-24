#import "Animation.h"
#import "Character2.h"
#import "CharacterCommands.h"
#import "Command.h"
#import "KwestKingdom.h"
#import "Sprite2.h"
#import "World.h"


@implementation CharacterCommand


- setCharacter:(Character2 *)aCharacter {
  character = aCharacter;
  return self;
}


- setAnimation:(Animation *)anAnimation {
  animation = anAnimation;
  return self;
}


- start {
  [[character sprite] setAnimation:animation];
  return [super start];
}


@end


@implementation WanderCommand


- execute {

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

  World *world = [sprite world];

  if ([world isWalkableAtX:x andY:y] && ![world isInhabitedAtX:x andY:y]) {
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


@implementation ChaseCommand


- execute {
  return self;
}


@end
