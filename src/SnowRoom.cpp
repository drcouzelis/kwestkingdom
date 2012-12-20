#include "Animation.h"
#include "Resources.h"
#include "SnowRoom.h"





SnowRoom::SnowRoom() {
  
  grassAnimation = new Animation();
  pathAnimation = new Animation();
  mountainAnimation = new Animation();
  waterAnimation = new Animation();
  shoreNorthAnimation = new Animation();
  shoreInsideNEAnimation = new Animation();
  shoreOutsideNEAnimation = new Animation();
  
  grassAnimation->addFrame(IMG("TERRAIN_SNOW"));
  //pathAnimation->addFrame(getImage(SNOW_PATH_01));
  mountainAnimation->addFrame(IMG("TERRAIN_EVERGREEN"));
  waterAnimation->addFrame(IMG("TERRAIN_ICE"));
  
  shoreNorthAnimation->addFrame(IMG("SHORE_SNOW"));
  shoreSouthAnimation = shoreNorthAnimation->copy()->setVerticalFlip(true);
  shoreEastAnimation = shoreNorthAnimation->copy()->setRotate(true);
  shoreWestAnimation = shoreNorthAnimation->copy()->setVerticalFlip(true)->setRotate(true);
  
  shoreInsideNEAnimation->addFrame(IMG("SHORE_SNOW_INSIDECORNER"));
  shoreInsideNWAnimation = shoreInsideNEAnimation->copy()->setHorizontalFlip(true);
  shoreInsideSEAnimation = shoreInsideNEAnimation->copy()->setVerticalFlip(true);
  shoreInsideSWAnimation = shoreInsideNEAnimation->copy()->setVerticalFlip(true)->setHorizontalFlip(true);
  
  shoreOutsideNEAnimation->addFrame(IMG("SHORE_SNOW_OUTSIDECORNER"));
  shoreOutsideNEAnimation->setOffsetX(-TILE_SIZE);
  shoreOutsideNEAnimation->setOffsetY(-TILE_SIZE);
  shoreOutsideNWAnimation = shoreOutsideNEAnimation->copy()->setHorizontalFlip(true);
  shoreOutsideSEAnimation = shoreOutsideNEAnimation->copy()->setVerticalFlip(true);
  shoreOutsideSWAnimation = shoreOutsideNEAnimation->copy()->setVerticalFlip(true)->setHorizontalFlip(true);
}

