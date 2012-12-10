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
  
  grassAnimation->addFrame(getImage(IMAGES_TERRAIN_SNOW));
  //pathAnimation->addFrame(getImage(SNOW_PATH_01));
  mountainAnimation->addFrame(getImage(IMAGES_TERRAIN_EVERGREEN));
  waterAnimation->addFrame(getImage(IMAGES_TERRAIN_ICE));
  
  shoreNorthAnimation->addFrame(getImage(IMAGES_SHORE_SNOW));
  shoreSouthAnimation = shoreNorthAnimation->copy()->setVerticalFlip(true);
  shoreEastAnimation = shoreNorthAnimation->copy()->setRotate(true);
  shoreWestAnimation = shoreNorthAnimation->copy()->setVerticalFlip(true)->setRotate(true);
  
  shoreInsideNEAnimation->addFrame(getImage(IMAGES_SHORE_SNOW_INSIDECORNER));
  shoreInsideNWAnimation = shoreInsideNEAnimation->copy()->setHorizontalFlip(true);
  shoreInsideSEAnimation = shoreInsideNEAnimation->copy()->setVerticalFlip(true);
  shoreInsideSWAnimation = shoreInsideNEAnimation->copy()->setVerticalFlip(true)->setHorizontalFlip(true);
  
  shoreOutsideNEAnimation->addFrame(getImage(IMAGES_SHORE_SNOW_OUTSIDECORNER));
  shoreOutsideNEAnimation->setOffsetX(-TILE_SIZE);
  shoreOutsideNEAnimation->setOffsetY(-TILE_SIZE);
  shoreOutsideNWAnimation = shoreOutsideNEAnimation->copy()->setHorizontalFlip(true);
  shoreOutsideSEAnimation = shoreOutsideNEAnimation->copy()->setVerticalFlip(true);
  shoreOutsideSWAnimation = shoreOutsideNEAnimation->copy()->setVerticalFlip(true)->setHorizontalFlip(true);
}

