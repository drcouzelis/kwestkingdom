#include "UndergroundRoom.h"


@implementation UndergroundRoom


- init {
  
  self = [super init];
  
  if (self) {
    
    grassAnimation = [[Animation alloc] init];
    //pathAnimation = [[Animation alloc] init];
    mountainAnimation = [[Animation alloc] init];
    waterAnimation = [[Animation alloc] init];
    shoreNorthAnimation = [[Animation alloc] init];
    shoreInsideNEAnimation = [[Animation alloc] init];
    shoreOutsideNEAnimation = [[Animation alloc] init];
    
    [grassAnimation addFrame: getImage(IMAGES_TERRAIN_DIRT)];
    //[pathAnimation addFrame: getImage(SNOW_PATH_01)];
    [mountainAnimation addFrame: getImage(IMAGES_TERRAIN_SPIRE)];
    //[waterAnimation addFrame: getImage(IMAGES_TERRAIN_WATER)];
    
    //[shoreNorthAnimation addFrame: getImage(SHORE_01)];
    //shoreSouthAnimation = [[shoreNorthAnimation copy] setVerticalFlip: true];
    //shoreEastAnimation = [[shoreNorthAnimation copy] setRotate: true];
    //shoreWestAnimation = [[[shoreNorthAnimation copy] setVerticalFlip: true] setRotate: true];
    
    //[shoreInsideNEAnimation addFrame: getImage(SHORE_INSIDE_CORNER_01)];
    //shoreInsideNWAnimation = [[shoreInsideNEAnimation copy] setHorizontalFlip: true];
    //shoreInsideSEAnimation = [[shoreInsideNEAnimation copy] setVerticalFlip: true];
    //shoreInsideSWAnimation = [[[shoreInsideNEAnimation copy] setVerticalFlip: true] setHorizontalFlip: true];
    
    //[shoreOutsideNEAnimation addFrame: getImage(SHORE_OUTSIDE_CORNER_01)];
    //[shoreOutsideNEAnimation setOffsetX: -TILE_SIZE];
    //[shoreOutsideNEAnimation setOffsetY: -TILE_SIZE];
    //shoreOutsideNWAnimation = [[shoreOutsideNEAnimation copy] setHorizontalFlip: true];
    //shoreOutsideSEAnimation = [[shoreOutsideNEAnimation copy] setVerticalFlip: true];
    //shoreOutsideSWAnimation = [[[shoreOutsideNEAnimation copy] setVerticalFlip: true] setHorizontalFlip: true];
    
  }
  
  return self;
  
}


@end

