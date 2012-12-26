#include "resources.h"
#include "SnowRoom.h"


SnowRoom::SnowRoom() {
  
  add_frame(&grass_anim, IMG("terrain_snow.bmp"));
  //add_frame(&path_anim, IMG("snow_path_01.bmp"));
  add_frame(&mountain_anim, IMG("terrain_evergreen.bmp"));
  add_frame(&water_anim, IMG("terrain_ice.bmp"));
  
  add_frame(&shore_north_anim, IMG("shore_snow.bmp"));

  copy_anim(&shore_south_anim, &shore_north_anim);
  shore_south_anim.v_flip = ON;

  copy_anim(&shore_east_anim, &shore_north_anim);
  shore_east_anim.rotate = ON;

  copy_anim(&shore_west_anim, &shore_north_anim);
  shore_west_anim.v_flip = ON;
  shore_west_anim.rotate = ON;
  
  add_frame(&shore_inside_ne_anim, IMG("shore_snow_insidecorner.bmp"));

  copy_anim(&shore_inside_nw_anim, &shore_inside_ne_anim);
  shore_inside_nw_anim.h_flip = ON;

  copy_anim(&shore_inside_se_anim, &shore_inside_ne_anim);
  shore_inside_se_anim.v_flip = ON;

  copy_anim(&shore_inside_sw_anim, &shore_inside_ne_anim);
  shore_inside_sw_anim.v_flip = ON;
  shore_inside_sw_anim.h_flip = ON;

  add_frame(&shore_outside_ne_anim, IMG("shore_snow_outsidecorner.bmp"));
  shore_outside_ne_anim.offset_x = -TILE_SIZE;
  shore_outside_ne_anim.offset_y = -TILE_SIZE;

  copy_anim(&shore_outside_nw_anim, &shore_outside_ne_anim);
  shore_outside_nw_anim.h_flip = ON;

  copy_anim(&shore_outside_se_anim, &shore_outside_ne_anim);
  shore_outside_se_anim.v_flip = ON;

  copy_anim(&shore_outside_sw_anim, &shore_outside_ne_anim);
  shore_outside_sw_anim.v_flip = ON;
  shore_outside_sw_anim.h_flip = ON;
}

