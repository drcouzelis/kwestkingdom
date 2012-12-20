#include "Animation.h"
#include "resources.h"
#include "UndergroundRoom.h"


UndergroundRoom::UndergroundRoom() {
  
  grassAnimation = new Animation();
  //pathAnimation = new Animation();
  mountainAnimation = new Animation();
  waterAnimation = new Animation();
  shoreNorthAnimation = new Animation();
  shoreInsideNEAnimation = new Animation();
  shoreOutsideNEAnimation = new Animation();
  
  grassAnimation->addFrame(IMG("terrain_dirt.bmp"));
  //pathAnimation->addFrame(IMG("snow_path_01.bmp"));
  mountainAnimation->addFrame(IMG("terrain_spire.bmp"));
  //waterAnimation->addFrame(IMG("terrain_water.bmp"));
  
  //shoreNorthAnimation->addFrame(IMG("shore_01.bmp"));
  //shoreSouthAnimation = shoreNorthAnimation->copy()->setVerticalFlip(true);
  //shoreEastAnimation = shoreNorthAnimation->copy()->setRotate(true);
  //shoreWestAnimation = shoreNorthAnimation->copy()->setVerticalFlip(true)->setRotate(true);
  
  //shoreInsideNEAnimation->addFrame(IMG("shore_inside_corner_01.bmp"));
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

