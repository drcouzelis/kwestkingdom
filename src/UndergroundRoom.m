#import "UndergroundRoom.h"


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

    [grassAnimation addFrame: getImage(IMG_TERRAIN_DIRT)];
    //[pathAnimation addFrame: getImage(SNOW_PATH_01)];
    [mountainAnimation addFrame: getImage(IMG_TERRAIN_SPIRE)];
    //[waterAnimation addFrame: getImage(IMG_TERRAIN_WATER)];

    //[shoreNorthAnimation addFrame: getImage(SHORE_01)];
    //shoreSouthAnimation = [[shoreNorthAnimation copy] setVerticalFlip: YES];
    //shoreEastAnimation = [[shoreNorthAnimation copy] setRotate: YES];
    //shoreWestAnimation = [[[shoreNorthAnimation copy] setVerticalFlip: YES] setRotate: YES];

    //[shoreInsideNEAnimation addFrame: getImage(SHORE_INSIDE_CORNER_01)];
    //shoreInsideNWAnimation = [[shoreInsideNEAnimation copy] setHorizontalFlip: YES];
    //shoreInsideSEAnimation = [[shoreInsideNEAnimation copy] setVerticalFlip: YES];
    //shoreInsideSWAnimation = [[[shoreInsideNEAnimation copy] setVerticalFlip: YES] setHorizontalFlip: YES];

    //[shoreOutsideNEAnimation addFrame: getImage(SHORE_OUTSIDE_CORNER_01)];
    //[shoreOutsideNEAnimation setOffsetX: -TILE_SIZE];
    //[shoreOutsideNEAnimation setOffsetY: -TILE_SIZE];
    //shoreOutsideNWAnimation = [[shoreOutsideNEAnimation copy] setHorizontalFlip: YES];
    //shoreOutsideSEAnimation = [[shoreOutsideNEAnimation copy] setVerticalFlip: YES];
    //shoreOutsideSWAnimation = [[[shoreOutsideNEAnimation copy] setVerticalFlip: YES] setHorizontalFlip: YES];

  }

  return self;

}


@end

