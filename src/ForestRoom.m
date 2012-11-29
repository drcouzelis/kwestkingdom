#import "ForestRoom.h"


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
    shoreSouthAnimation = [[shoreNorthAnimation copy] setVerticalFlip: YES];
    shoreEastAnimation = [[shoreNorthAnimation copy] setRotate: YES];
    shoreWestAnimation = [[[shoreNorthAnimation copy] setVerticalFlip: YES] setRotate: YES];
    
    [shoreInsideNEAnimation addFrame: getImage(IMAGES_SHORE_GRASS_INSIDECORNER)];
    shoreInsideNWAnimation = [[shoreInsideNEAnimation copy] setHorizontalFlip: YES];
    shoreInsideSEAnimation = [[shoreInsideNEAnimation copy] setVerticalFlip: YES];
    shoreInsideSWAnimation = [[[shoreInsideNEAnimation copy] setVerticalFlip: YES] setHorizontalFlip: YES];
    
    [shoreOutsideNEAnimation addFrame: getImage(IMAGES_SHORE_GRASS_OUTSIDECORNER)];
    [shoreOutsideNEAnimation setOffsetX: -TILE_SIZE];
    [shoreOutsideNEAnimation setOffsetY: -TILE_SIZE];
    shoreOutsideNWAnimation = [[shoreOutsideNEAnimation copy] setHorizontalFlip: YES];
    shoreOutsideSEAnimation = [[shoreOutsideNEAnimation copy] setVerticalFlip: YES];
    shoreOutsideSWAnimation = [[[shoreOutsideNEAnimation copy] setVerticalFlip: YES] setHorizontalFlip: YES];
    
  }
  
  return self;
  
}


@end

