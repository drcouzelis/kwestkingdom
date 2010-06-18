// TEMP
#import "Animation.h"
#import "Character2.h"
#import "CharacterCommands.h"
#import "Resources.h"
#import "Sprite2.h"

#import "EndlessWorld.h"


@implementation EndlessWorld


- init {
  
  self = [super init];
  
  if (self) {
    difficulty = 100;

    // TEMP
    Sprite2 *sprite = [[Sprite2 alloc] initWorld:self width:1 height:1];
    [sprite setX:5];
    [sprite setY:5];
    Animation *anim = [[Animation alloc] init];
    [anim addFrame:getImage(IMG_CHOMPER_STAND_1)];
    [anim addFrame:getImage(IMG_CHOMPER_STAND_2)];
    [anim addFrame:getImage(IMG_CHOMPER_STAND_3)];
    [anim addFrame:getImage(IMG_CHOMPER_STAND_2)];
    [anim setLoop:YES];
    [anim setSpeed:6];
    [sprite addAnimation:anim named:"STANDING"];
    enemy = [[Character2 alloc] initSprite:sprite];
    Command *command = [[WanderCommand alloc] initCharacter:enemy];
    [enemy addCommand:command named:"WANDER"];
  }
  
  return self;
  
}


// TEMP
- update {
  [super update];
  [enemy update];
  return self;
}


// TEMP
- draw:(BITMAP *)canvas {
  [super draw:canvas];
  [enemy draw:canvas];
  return self;
}


@end

