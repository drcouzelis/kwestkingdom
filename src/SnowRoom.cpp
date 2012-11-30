#include "SnowRoom.h"


@implementation SnowRoom


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
    
    [grassAnimation addFrame: getImage(IMAGES_TERRAIN_SNOW)];
    //[pathAnimation addFrame: getImage(SNOW_PATH_01)];
    [mountainAnimation addFrame: getImage(IMAGES_TERRAIN_EVERGREEN)];
    [waterAnimation addFrame: getImage(IMAGES_TERRAIN_ICE)];
    
    [shoreNorthAnimation addFrame: getImage(IMAGES_SHORE_SNOW)];
    shoreSouthAnimation = [[shoreNorthAnimation copy] setVerticalFlip: YES];
    shoreEastAnimation = [[shoreNorthAnimation copy] setRotate: YES];
    shoreWestAnimation = [[[shoreNorthAnimation copy] setVerticalFlip: YES] setRotate: YES];
    
    [shoreInsideNEAnimation addFrame: getImage(IMAGES_SHORE_SNOW_INSIDECORNER)];
    shoreInsideNWAnimation = [[shoreInsideNEAnimation copy] setHorizontalFlip: YES];
    shoreInsideSEAnimation = [[shoreInsideNEAnimation copy] setVerticalFlip: YES];
    shoreInsideSWAnimation = [[[shoreInsideNEAnimation copy] setVerticalFlip: YES] setHorizontalFlip: YES];
    
    [shoreOutsideNEAnimation addFrame: getImage(IMAGES_SHORE_SNOW_OUTSIDECORNER)];
    [shoreOutsideNEAnimation setOffsetX: -TILE_SIZE];
    [shoreOutsideNEAnimation setOffsetY: -TILE_SIZE];
    shoreOutsideNWAnimation = [[shoreOutsideNEAnimation copy] setHorizontalFlip: YES];
    shoreOutsideSEAnimation = [[shoreOutsideNEAnimation copy] setVerticalFlip: YES];
    shoreOutsideSWAnimation = [[[shoreOutsideNEAnimation copy] setVerticalFlip: YES] setHorizontalFlip: YES];
    
  }
  
  return self;
  
}


@end

