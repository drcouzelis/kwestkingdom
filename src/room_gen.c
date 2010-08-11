#include "anim.h"
#include "resources.h"
#include "room.h"
#include "room_gen.h"




void set_room_theme(ROOM *room, ROOM_THEME theme)
{
  int i;
  
  int empty;
  int hole;
  int wall;
  int edge;
  int inside;
  int outside;
  
  if (room == NULL) {
    return;
  }
  
  for (i = 0; i < MAX_TILE_TYPES; i++) {
    free(room->tile_anims[i]);
  }
  
  /**
   * At the moment, none of these have more than one frame of animation.
   * Just initialize them all here.
   */
  for (i = 0; i < MAX_TILE_TYPES; i++) {
    room->tile_anims[i] = create_anim(0, OFF);
  }
  
  switch (theme) {
  
  case ROOM_THEME_FOREST:
    empty = IMG_TERRAIN_GRASS;
    hole = IMG_TERRAIN_WATER;
    wall = IMG_TERRAIN_OAK;
    edge = IMG_SHORE_GRASS_SHORE;
    inside = IMG_SHORE_GRASS_INSIDECORNER;
    outside = IMG_SHORE_GRASS_OUTSIDECORNER;
    break;
    
  case ROOM_THEME_SNOW:
    empty = IMG_TERRAIN_SNOW;
    hole = IMG_TERRAIN_ICE;
    wall = IMG_TERRAIN_EVERGREEN;
    edge = IMG_SHORE_SNOW_SHORE;
    inside = IMG_SHORE_SNOW_INSIDECORNER;
    outside = IMG_SHORE_SNOW_OUTSIDECORNER;
    break;
    
  case ROOM_THEME_UNDERGROUND:
    empty = IMG_TERRAIN_DIRT;
    hole = IMG_TERRAIN_WATER; /* NOT USED */
    wall = IMG_TERRAIN_SPIRE;
    edge = IMG_SHORE_GRASS_SHORE; /* NOT USED */
    inside = IMG_SHORE_GRASS_INSIDECORNER; /* NOT USED */
    outside = IMG_SHORE_GRASS_OUTSIDECORNER; /* NOT USED */
    break;
    
  default:
    return;
  }
  
  add_frame(room->tile_anims[TILE_TYPE_EMPTY], get_image(empty, NORMAL));
  add_frame(room->tile_anims[TILE_TYPE_HOLE], get_image(hole, NORMAL));
  add_frame(room->tile_anims[TILE_TYPE_WALL], get_image(wall, NORMAL));
  add_frame(room->tile_anims[TILE_TYPE_N_EDGE], get_image(edge, NORMAL));
  add_frame(room->tile_anims[TILE_TYPE_S_EDGE], get_image(edge, V_FLIP));
  add_frame(room->tile_anims[TILE_TYPE_E_EDGE], get_image(edge, ROTATE));
  add_frame(room->tile_anims[TILE_TYPE_W_EDGE], get_image(edge, ROTATE_V_FLIP));
  add_frame(room->tile_anims[TILE_TYPE_NE_INSIDE], get_image(inside, NORMAL));
  add_frame(room->tile_anims[TILE_TYPE_NW_INSIDE], get_image(inside, H_FLIP));
  add_frame(room->tile_anims[TILE_TYPE_SE_INSIDE], get_image(inside, V_FLIP));
  add_frame(room->tile_anims[TILE_TYPE_SW_INSIDE], get_image(inside, H_V_FLIP));
}




void create_path(ROOM *room, int start_x, int start_y, int end_x, int end_y)
{
}




void generate_layout(ROOM *room, LAYOUT_OPTIONS *options)
{
  /* TEMP */
  int row;
  int col;
  
  for (row = 0; row < ROWS; row++) {
    for (col = 0; col < COLS; col++) {
      room->tiles[row][col] = create_tile(TILE_TYPE_EMPTY, OBSTACLE_TYPE_NONE);
    }
  }
}




void generate_enemies(ROOM *room, int types)
{
}

