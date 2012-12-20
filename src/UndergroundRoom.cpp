#include "Animation.h"
#include "Resources.h"
#include "UndergroundRoom.h"


UndergroundRoom::UndergroundRoom() {
  
  grassAnimation = new Animation();
  //pathAnimation = new Animation();
  mountainAnimation = new Animation();
  waterAnimation = new Animation();
  shoreNorthAnimation = new Animation();
  shoreInsideNEAnimation = new Animation();
  shoreOutsideNEAnimation = new Animation();
  
  grassAnimation->addFrame(IMG("TERRAIN_DIRT"));
  //pathAnimation->addFrame(getImage(SNOW_PATH_01));
  mountainAnimation->addFrame(IMG("TERRAIN_SPIRE"));
  //waterAnimation->addFrame(IMG("TERRAIN_WATER"));
  
  //shoreNorthAnimation->addFrame(getImage(SHORE_01));
  //shoreSouthAnimation = shoreNorthAnimation->copy()->setVerticalFlip(true);
  //shoreEastAnimation = shoreNorthAnimation->copy()->setRotate(true);
  //shoreWestAnimation = shoreNorthAnimation->copy()->setVerticalFlip(true)->setRotate(true);
  
  //shoreInsideNEAnimation->addFrame(getImage(SHORE_INSIDE_CORNER_01));
  //shoreInsideNWAnimation = shoreInsideNEAnimation->copy()->setHorizontalFlip(true);
  //shoreInsideSEAnimation = shoreInsideNEAnimation->copy()->setVerticalFlip(true);
  //shoreInsideSWAnimation = shoreInsideNEAnimation->copy()->setVerticalFlip(true)->setHorizontalFlip(true);
  
  //shoreOutsideNEAnimation->addFrame(getImage(SHORE_OUTSIDE_CORNER_01));
  //shoreOutsideNEAnimation->setOffsetX(-TILE_SIZE);
  //shoreOutsideNEAnimation->setOffsetY(-TILE_SIZE);
  //shoreOutsideNWAnimation = shoreOutsideNEAnimation->copy()->setHorizontalFlip(true);
  //shoreOutsideSEAnimation = shoreOutsideNEAnimation->copy()->setVerticalFlip(true);
  //shoreOutsideSWAnimation = shoreOutsideNEAnimation->copy()->setVerticalFlip(true)->setHorizontalFlip(true);
}

