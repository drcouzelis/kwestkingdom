#include "Animation.h"
#include "ForestRoom.h"
#include "KwestKingdom.h"
#include "Resources.h"


ForestRoom::ForestRoom() {
  
  grassAnimation = new Animation();
  pathAnimation = new Animation();
  mountainAnimation = new Animation();
  waterAnimation = new Animation();
  shoreNorthAnimation = new Animation();
  shoreInsideNEAnimation = new Animation();
  shoreOutsideNEAnimation = new Animation();
  
  grassAnimation->addFrame(getImage(IMAGES_TERRAIN_GRASS));
  pathAnimation->addFrame(getImage(IMAGES_TERRAIN_PATH));
  mountainAnimation->addFrame(getImage(IMAGES_TERRAIN_OAK));
  waterAnimation->addFrame(getImage(IMAGES_TERRAIN_WATER));
  
  shoreNorthAnimation->addFrame(getImage(IMAGES_SHORE_GRASS));
  shoreSouthAnimation = shoreNorthAnimation->copy()->setVerticalFlip(true);
  shoreEastAnimation = shoreNorthAnimation->copy()->setRotate(true);
  shoreWestAnimation = shoreNorthAnimation->copy()->setVerticalFlip(true)->setRotate(true);
  
  shoreInsideNEAnimation->addFrame(getImage(IMAGES_SHORE_GRASS_INSIDECORNER));
  shoreInsideNWAnimation = shoreInsideNEAnimation->copy()->setHorizontalFlip(true);
  shoreInsideSEAnimation = shoreInsideNEAnimation->copy()->setVerticalFlip(true);
  shoreInsideSWAnimation = shoreInsideNEAnimation->copy()->setVerticalFlip(true)->setHorizontalFlip(true);
  
  shoreOutsideNEAnimation->addFrame(getImage(IMAGES_SHORE_GRASS_OUTSIDECORNER));
  shoreOutsideNEAnimation->setOffsetX(-TILE_SIZE);
  shoreOutsideNEAnimation->setOffsetY(-TILE_SIZE);
  shoreOutsideNWAnimation = shoreOutsideNEAnimation->copy()->setHorizontalFlip(true);
  shoreOutsideSEAnimation = shoreOutsideNEAnimation->copy()->setVerticalFlip(true);
  shoreOutsideSWAnimation = shoreOutsideNEAnimation->copy()->setVerticalFlip(true)->setHorizontalFlip(true);
  
}

