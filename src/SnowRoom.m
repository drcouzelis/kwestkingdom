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
#import "SnowRoom.h"


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
    
    [grassAnimation addFrame: getImage(TERRAIN_SNOW_01_BMP)];
    //[pathAnimation addFrame: getImage(SNOW_PATH_01_BMP)];
    [mountainAnimation addFrame: getImage(TERRAIN_EVERGREEN_01_BMP)];
    [waterAnimation addFrame: getImage(TERRAIN_ICE_01_BMP)];
    
    [shoreNorthAnimation addFrame: getImage(SHORE_ICE_01_BMP)];
    shoreSouthAnimation = [[shoreNorthAnimation copy] vFlip: YES];
    shoreEastAnimation = [[shoreNorthAnimation copy] rotate: YES];
    shoreWestAnimation = [[[shoreNorthAnimation copy] vFlip: YES] rotate: YES];
    
    [shoreInsideNEAnimation addFrame: getImage(SHORE_ICE_INSIDE_CORNER_01_BMP)];
    shoreInsideNWAnimation = [[shoreInsideNEAnimation copy] hFlip: YES];
    shoreInsideSEAnimation = [[shoreInsideNEAnimation copy] vFlip: YES];
    shoreInsideSWAnimation = [[[shoreInsideNEAnimation copy] vFlip: YES] hFlip: YES];
    
    [shoreOutsideNEAnimation addFrame: getImage(SHORE_ICE_OUTSIDE_CORNER_01_BMP)];
    [shoreOutsideNEAnimation setOffsetX: -TILE_SIZE];
    [shoreOutsideNEAnimation setOffsetY: -TILE_SIZE];
    shoreOutsideNWAnimation = [[shoreOutsideNEAnimation copy] hFlip: YES];
    shoreOutsideSEAnimation = [[shoreOutsideNEAnimation copy] vFlip: YES];
    shoreOutsideSWAnimation = [[[shoreOutsideNEAnimation copy] vFlip: YES] hFlip: YES];
    
  }
  
  return self;
  
}


@end

