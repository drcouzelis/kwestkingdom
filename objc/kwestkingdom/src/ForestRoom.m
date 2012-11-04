/**
 * Copyright 2009 David Couzelis
 * 
 * This file is part of "Kwest Kingdom".
 * 
 * "Kwest Kingdom" is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * "Kwest Kingdom" is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with "Kwest Kingdom".  If not, see <http://www.gnu.org/licenses/>.
 */
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
    
    [grassAnimation addFrame: getImage(IMG_TERRAIN_GRASS)];
    [pathAnimation addFrame: getImage(IMG_TERRAIN_PATH)];
    [mountainAnimation addFrame: getImage(IMG_TERRAIN_OAK)];
    [waterAnimation addFrame: getImage(IMG_TERRAIN_WATER)];
    
    [shoreNorthAnimation addFrame: getImage(IMG_SHORE_GRASS_SHORE)];
    shoreSouthAnimation = [[shoreNorthAnimation copy] setVerticalFlip: YES];
    shoreEastAnimation = [[shoreNorthAnimation copy] setRotate: YES];
    shoreWestAnimation = [[[shoreNorthAnimation copy] setVerticalFlip: YES] setRotate: YES];
    
    [shoreInsideNEAnimation addFrame: getImage(IMG_SHORE_GRASS_INSIDECORNER)];
    shoreInsideNWAnimation = [[shoreInsideNEAnimation copy] setHorizontalFlip: YES];
    shoreInsideSEAnimation = [[shoreInsideNEAnimation copy] setVerticalFlip: YES];
    shoreInsideSWAnimation = [[[shoreInsideNEAnimation copy] setVerticalFlip: YES] setHorizontalFlip: YES];
    
    [shoreOutsideNEAnimation addFrame: getImage(IMG_SHORE_GRASS_OUTSIDECORNER)];
    [shoreOutsideNEAnimation setOffsetX: -TILE_SIZE];
    [shoreOutsideNEAnimation setOffsetY: -TILE_SIZE];
    shoreOutsideNWAnimation = [[shoreOutsideNEAnimation copy] setHorizontalFlip: YES];
    shoreOutsideSEAnimation = [[shoreOutsideNEAnimation copy] setVerticalFlip: YES];
    shoreOutsideSWAnimation = [[[shoreOutsideNEAnimation copy] setVerticalFlip: YES] setHorizontalFlip: YES];
    
  }
  
  return self;
  
}


@end

