#import "Character2.h"
#import "CharacterCommands.h"
#import "Command.h"
#import "KwestKingdom.h"
#import "Sprite2.h"
#import "World.h"


@implementation WanderCommand


- initCharacter:(Character2 *)aCharacter {
  self = [self init];
  if (self) {
    character = aCharacter;
  }
  return self;
}


- execute {

  Sprite2 *sprite = [character sprite];

  /**
   * Pick a random direction to head
   */
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


- initSprite:(Sprite2 *)aSprite {
  self = [self init];
  if (self) {
    sprite = aSprite;
  }
  return self;
}


@end
