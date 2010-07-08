#import "Character2.h"
#import "EndlessWorld.h"
//#import "EnemyFactory.h" // TEMP
#import "Sprite2.h"


@implementation EndlessWorld


- init {
  
  self = [super init];
  
  if (self) {
    difficulty = 100;
    
    // TEMP
    //enemy = [[[EnemyFactory createChomperX:5 y:5] sprite] setWorld:self];
  }
  
  return self;
  
}


// TEMP
//- update {
//  [super update];
//  [enemy update];
//  return self;
//}


// TEMP
//- draw:(BITMAP *)canvas {
//  [super draw:canvas];
//  [enemy draw:canvas];
//  return self;
//}


@end

