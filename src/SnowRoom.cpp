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
#include "SnowRoom.h"


SnowRoom::SnowRoom()
{
  grassAnimation = new Animation();
  pathAnimation = new Animation();
  mountainAnimation = new Animation();
  waterAnimation = new Animation();
  shoreNorthAnimation = new Animation();
  shoreInsideNEAnimation = new Animation();
  shoreOutsideNEAnimation = new Animation();
  
  grassAnimation->addFrame(get_image(IMG_TERRAIN_SNOW));
  //pathAnimation->addFrame(get_image(SNOW_PATH_01));
  mountainAnimation->addFrame(get_image(IMG_TERRAIN_EVERGREEN));
  waterAnimation->addFrame(get_image(IMG_TERRAIN_ICE));
  
  // Shores
  shoreNorthAnimation->addFrame(get_image(IMG_SHORE_SNOW_SHORE));
  
  shoreSouthAnimation = shoreNorthAnimation;
  shoreSouthAnimation->setVerticalFlip(true);
  
  shoreEastAnimation = shoreNorthAnimation;
  shoreEastAnimation->setRotate(true);
  
  shoreWestAnimation = shoreNorthAnimation;
  shoreWestAnimation->setVerticalFlip(true);
  shoreWestAnimation->setRotate(true);
  
  // Inside shores
  shoreInsideNEAnimation->addFrame(get_image(IMG_SHORE_SNOW_INSIDECORNER));
  
  shoreInsideNWAnimation = shoreInsideNEAnimation;
  shoreInsideNWAnimation->setHorizontalFlip(true);
  
  shoreInsideSEAnimation = shoreInsideNEAnimation;
  shoreInsideSEAnimation->setVerticalFlip(true);
  
  shoreInsideSWAnimation = shoreInsideNEAnimation;
  shoreInsideSWAnimation->setVerticalFlip(true);
  shoreInsideSWAnimation->setHorizontalFlip(true);
  
  // Outside shores
  shoreOutsideNEAnimation->addFrame(get_image(IMG_SHORE_SNOW_OUTSIDECORNER));
  shoreOutsideNEAnimation->setHorizontalOffset(-TILE_SIZE);
  shoreOutsideNEAnimation->setVerticalOffset(-TILE_SIZE);
  
  shoreOutsideNWAnimation = shoreOutsideNEAnimation;
  shoreOutsideNWAnimation->setHorizontalFlip(true);
  
  shoreOutsideSEAnimation = shoreOutsideNEAnimation;
  shoreOutsideSEAnimation->setVerticalFlip(true);
  
  shoreOutsideSWAnimation = shoreOutsideNEAnimation;
  shoreOutsideSWAnimation->setVerticalFlip(true);
  shoreOutsideSWAnimation->setHorizontalFlip(true);
}
