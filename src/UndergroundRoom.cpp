#include "resources.h"
#include "UndergroundRoom.h"


UndergroundRoom::UndergroundRoom() {
  
  add_frame(&grass_anim, IMG("terrain_dirt.bmp"));
  //add_frame(&path_anim, IMG("snow_path_01.bmp"));
  add_frame(&mountain_anim, IMG("terrain_spire.bmp"));
  //add_frame(&water_anim, IMG("terrain_water.bmp"));
  
  //shore_north_anim->addFrame(IMG("shore_01.bmp"));
  //shore_south_anim = shore_north_anim->copy()->setVerticalFlip(true);
  //shore_east_anim = shore_north_anim->copy()->setRotate(true);
  //shore_west_anim = shore_north_anim->copy()->setVerticalFlip(true)->setRotate(true);
  
  //shore_inside_ne_anim->addFrame(IMG("shore_inside_corner_01.bmp"));
  //shore_inside_nw_anim = shore_inside_ne_anim->copy()->setHorizontalFlip(true);
  //shore_inside_se_anim = shore_inside_ne_anim->copy()->setVerticalFlip(true);
  //shore_inside_sw_anim = shore_inside_ne_anim->copy()->setVerticalFlip(true)->setHorizontalFlip(true);
  
  //shore_outside_ne_anim->addFrame(getImage(SHORE_OUTSIDE_CORNER_01));
  //shore_outside_ne_anim->setOffsetX(-TILE_SIZE);
  //shore_outside_ne_anim->setOffsetY(-TILE_SIZE);
  //shore_outside_nw_anim = shore_outside_ne_anim->copy()->setHorizontalFlip(true);
  //shore_outside_se_anim = shore_outside_ne_anim->copy()->setVerticalFlip(true);
  //shore_outside_sw_anim = shore_outside_ne_anim->copy()->setVerticalFlip(true)->setHorizontalFlip(true);
}

