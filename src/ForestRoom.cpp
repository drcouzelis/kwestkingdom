#include "ForestRoom.h"


@implementation ForestRoom


- init {
  
  self = [super init];
  
  if (self) {
    
    grassAnimation = [[Animation alloc] init];
    pathAnimation = [[Animation alloc] init];
    mountainAnimation = [[Animation alloc] init];
    waterAnimation = [[Animation alloc] init];
    shoreNorthAnimation = [[Animation alloc] init];
    shoreInsideNEAnimation = [[Animation alloc] init];
    shoreOutsideNEAnimation = [[Animation alloc] init];
    
    [grassAnimation addFrame: getImage(IMAGES_TERRAIN_GRASS)];
    [pathAnimation addFrame: getImage(IMAGES_TERRAIN_PATH)];
    [mountainAnimation addFrame: getImage(IMAGES_TERRAIN_OAK)];
    [waterAnimation addFrame: getImage(IMAGES_TERRAIN_WATER)];
    
    [shoreNorthAnimation addFrame: getImage(IMAGES_SHORE_GRASS)];
    shoreSouthAnimation = [[shoreNorthAnimation copy] setVerticalFlip: true];
    shoreEastAnimation = [[shoreNorthAnimation copy] setRotate: true];
    shoreWestAnimation = [[[shoreNorthAnimation copy] setVerticalFlip: true] setRotate: true];
    
    [shoreInsideNEAnimation addFrame: getImage(IMAGES_SHORE_GRASS_INSIDECORNER)];
    shoreInsideNWAnimation = [[shoreInsideNEAnimation copy] setHorizontalFlip: true];
    shoreInsideSEAnimation = [[shoreInsideNEAnimation copy] setVerticalFlip: true];
    shoreInsideSWAnimation = [[[shoreInsideNEAnimation copy] setVerticalFlip: true] setHorizontalFlip: true];
    
    [shoreOutsideNEAnimation addFrame: getImage(IMAGES_SHORE_GRASS_OUTSIDECORNER)];
    [shoreOutsideNEAnimation setOffsetX: -TILE_SIZE];
    [shoreOutsideNEAnimation setOffsetY: -TILE_SIZE];
    shoreOutsideNWAnimation = [[shoreOutsideNEAnimation copy] setHorizontalFlip: true];
    shoreOutsideSEAnimation = [[shoreOutsideNEAnimation copy] setVerticalFlip: true];
    shoreOutsideSWAnimation = [[[shoreOutsideNEAnimation copy] setVerticalFlip: true] setHorizontalFlip: true];
    
  }
  
  return self;
  
}


@end

