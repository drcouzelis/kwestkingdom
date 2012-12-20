#include "Animation.h"
#include "resources.h"
#include "SnowRoom.h"





SnowRoom::SnowRoom() {
  
  grassAnimation = new Animation();
  pathAnimation = new Animation();
  mountainAnimation = new Animation();
  waterAnimation = new Animation();
  shoreNorthAnimation = new Animation();
  shoreInsideNEAnimation = new Animation();
  shoreOutsideNEAnimation = new Animation();
  
  grassAnimation->addFrame(IMG("terrain_snow.bmp"));
  //pathAnimation->addFrame(IMG("snow_path_01.bmp"));
  mountainAnimation->addFrame(IMG("terrain_evergreen.bmp"));
  waterAnimation->addFrame(IMG("terrain_ice.bmp"));
  
  shoreNorthAnimation->addFrame(IMG("shore_snow.bmp"));
  shoreSouthAnimation = shoreNorthAnimation->copy()->setVerticalFlip(true);
  shoreEastAnimation = shoreNorthAnimation->copy()->setRotate(true);
  shoreWestAnimation = shoreNorthAnimation->copy()->setVerticalFlip(true)->setRotate(true);
  
  shoreInsideNEAnimation->addFrame(IMG("shore_snow_insidecorner.bmp"));
  shoreInsideNWAnimation = shoreInsideNEAnimation->copy()->setHorizontalFlip(true);
  shoreInsideSEAnimation = shoreInsideNEAnimation->copy()->setVerticalFlip(true);
  shoreInsideSWAnimation = shoreInsideNEAnimation->copy()->setVerticalFlip(true)->setHorizontalFlip(true);
  
  shoreOutsideNEAnimation->addFrame(IMG("shore_snow_outsidecorner.bmp"));
  shoreOutsideNEAnimation->setOffsetX(-TILE_SIZE);
  shoreOutsideNEAnimation->setOffsetY(-TILE_SIZE);
  shoreOutsideNWAnimation = shoreOutsideNEAnimation->copy()->setHorizontalFlip(true);
  shoreOutsideSEAnimation = shoreOutsideNEAnimation->copy()->setVerticalFlip(true);
  shoreOutsideSWAnimation = shoreOutsideNEAnimation->copy()->setVerticalFlip(true)->setHorizontalFlip(true);
}

