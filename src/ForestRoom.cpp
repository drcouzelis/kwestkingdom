#include "Animation.h"
#include "ForestRoom.h"
#include "KwestKingdom.h"
#include "resources.h"


ForestRoom::ForestRoom() {
  
  grassAnimation = new Animation();
  pathAnimation = new Animation();
  mountainAnimation = new Animation();
  waterAnimation = new Animation();
  shoreNorthAnimation = new Animation();
  shoreInsideNEAnimation = new Animation();
  shoreOutsideNEAnimation = new Animation();
  
  grassAnimation->addFrame(IMG("terrain_grass.bmp"));
  pathAnimation->addFrame(IMG("terrain_path.bmp"));
  mountainAnimation->addFrame(IMG("terrain_oak.bmp"));
  waterAnimation->addFrame(IMG("terrain_water.bmp"));
  
  shoreNorthAnimation->addFrame(IMG("shore_grass.bmp"));
  shoreSouthAnimation = shoreNorthAnimation->copy()->setVerticalFlip(true);
  shoreEastAnimation = shoreNorthAnimation->copy()->setRotate(true);
  shoreWestAnimation = shoreNorthAnimation->copy()->setVerticalFlip(true)->setRotate(true);
  
  shoreInsideNEAnimation->addFrame(IMG("shore_grass_insidecorner.bmp"));
  shoreInsideNWAnimation = shoreInsideNEAnimation->copy()->setHorizontalFlip(true);
  shoreInsideSEAnimation = shoreInsideNEAnimation->copy()->setVerticalFlip(true);
  shoreInsideSWAnimation = shoreInsideNEAnimation->copy()->setVerticalFlip(true)->setHorizontalFlip(true);
  
  shoreOutsideNEAnimation->addFrame(IMG("shore_grass_outsidecorner.bmp"));
  shoreOutsideNEAnimation->setOffsetX(-TILE_SIZE);
  shoreOutsideNEAnimation->setOffsetY(-TILE_SIZE);
  shoreOutsideNWAnimation = shoreOutsideNEAnimation->copy()->setHorizontalFlip(true);
  shoreOutsideSEAnimation = shoreOutsideNEAnimation->copy()->setVerticalFlip(true);
  shoreOutsideSWAnimation = shoreOutsideNEAnimation->copy()->setVerticalFlip(true)->setHorizontalFlip(true);
  
}

