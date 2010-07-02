#import "Animation.h"
#import "Character2.h"
#import "CharacterCommands.h"
#import "EnemyFactory.h"
#import "Resources.h"
#import "Sprite2.h"


@implementation EnemyFactory


+ (Character2 *)createChomperX:(int)x y:(int)y {
  
  // Sprite
  Sprite2 *sprite = [[Sprite2 alloc] initWidth:1 height:1];
  [sprite setX:x];
  [sprite setY:x];
  
  // Main "doing nothing" animation
  Animation *anim = [[[[Animation alloc] init] setLoop:YES] setSpeed:6];
  [anim addFrame:getImage(IMG_CHOMPER_STAND_1)];
  [anim addFrame:getImage(IMG_CHOMPER_STAND_2)];
  [anim addFrame:getImage(IMG_CHOMPER_STAND_3)];
  [anim addFrame:getImage(IMG_CHOMPER_STAND_2)];
  [sprite addAnimation:anim named:"STANDING"];
  
  // Attack animation
  anim = [[[[Animation alloc] init] setLoop:NO] setSpeed:20];
  [anim addFrame:getImage(IMG_CHOMPER_BITE_1)];
  [anim addFrame:getImage(IMG_CHOMPER_BITE_2)];
  [anim addFrame:getImage(IMG_CHOMPER_BITE_3)];
  [anim addFrame:getImage(IMG_CHOMPER_BITE_4)];
  [anim addFrame:getImage(IMG_CHOMPER_BITE_5)];
  [anim addFrame:getImage(IMG_CHOMPER_BITE_4)];
  [anim addFrame:getImage(IMG_CHOMPER_BITE_3)];
  [anim addFrame:getImage(IMG_CHOMPER_BITE_2)];
  [anim addFrame:getImage(IMG_CHOMPER_BITE_1)];
  [sprite addAnimation:anim named:"ATTACKING"];
  
  // The enemy
  Character2 *enemy = [[Character2 alloc] initSprite:sprite];
  
  // Wander command
  CharacterCommand *command = [[WanderCommand alloc] init];
  [command setAnimation:[[enemy sprite] animationNamed:"STANDING"]];
  [enemy addCommand:command named:"WANDER"];
  
  // (Add attack command here)
  
  [enemy setCommandNamed:"WANDER"];
  [enemy wait];
  
  return enemy;
}


@end
