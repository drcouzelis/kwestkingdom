#include "anim.h"
#include "direction.h"
#include "enemy.h"
#include "memory.h"
#include "resources.h"
#include "room.h"




/**
 * Private
 */




FLAG row_out_of_bounds(int row)
{
  if (row < 0 || row > ROWS - 1) {
    return ON;
  }
  
  return OFF;
}




FLAG col_out_of_bounds(int col)
{
  if (col < 0 || col > COLS - 1) {
    return ON;
  }
  
  return OFF;
}




TILE_TYPE find_tile_type(ROOM *room, int row, int col)
{
  if (row_out_of_bounds(row) && col_out_of_bounds(col)) {
    return TILE_TYPE_HOLE;
  }
  
  if (row_out_of_bounds(row) || col_out_of_bounds(col)) {
    
    /**
     * YOU LEFT OFF HERE!!
     * This is a special case.
     *
     * If there is a door with a scrolling transition... {
     *   Use the tiles from the connecting room
     * } else {
     *   return TILE_TYPE_HOLE;
     * }
     */
    return TILE_TYPE_HOLE;
  }
  
  return room->terrain[row][col]->type;
}




void paint_edge(ROOM *room, BITMAP *canvas, int row, int col, int direction, TILE_TYPE edge_type)
{
  TILE_TYPE adjacent_type;
  
  int x;
  int y;
  
  x = col * grab_tile_size();
  y = row * grab_tile_size();
  
  row = row + cardinals[direction].v_offset;
  col = col + cardinals[direction].h_offset;
  
  adjacent_type = find_tile_type(room, row, col);
  
  if (adjacent_type != TILE_TYPE_HOLE) {
    paint_anim(room->terrain_anims[edge_type], canvas, x, y);
  }
}




void paint_inside_corner_edge(ROOM *room, BITMAP *canvas, int row, int col, int direction, TILE_TYPE edge_type)
{
  int x;
  int y;
  
  int r1;
  int c1;
  
  int r2;
  int c2;
  
  TILE_TYPE adjacent_type1;
  TILE_TYPE adjacent_type2;
  
  x = col * grab_tile_size();
  y = row * grab_tile_size();
  
  r1 = row + intercardinals[direction].v_offset;
  c1 = col;
  
  r2 = row;
  c2 = col + intercardinals[direction].h_offset;
  
  adjacent_type1 = find_tile_type(room, r1, c1);
  adjacent_type2 = find_tile_type(room, r2, c2);
  
  if (adjacent_type1 != TILE_TYPE_HOLE && adjacent_type2 != TILE_TYPE_HOLE) {
    paint_anim(room->terrain_anims[edge_type], canvas, x, y);
  }
}




void paint_outside_corner_edge(ROOM *room, BITMAP *canvas, int row, int col, int direction, TILE_TYPE edge_type)
{
  int x;
  int y;
  
  int r1;
  int c1;
  
  int r2;
  int c2;
  
  int r3;
  int c3;
  
  TILE_TYPE adjacent_type1;
  TILE_TYPE adjacent_type2;
  TILE_TYPE corner_type;
  
  x = col * grab_tile_size();
  y = row * grab_tile_size();
  
  r1 = row + intercardinals[direction].v_offset;
  c1 = col;
  
  r2 = row;
  c2 = col + intercardinals[direction].h_offset;
  
  r3 = row + intercardinals[direction].v_offset;
  c3 = col + intercardinals[direction].h_offset;
  
  adjacent_type1 = find_tile_type(room, r1, c1);
  adjacent_type2 = find_tile_type(room, r2, c2);
  corner_type = find_tile_type(room, r3, c3);
  
  if (adjacent_type1 == TILE_TYPE_HOLE && adjacent_type2 == TILE_TYPE_HOLE && corner_type != TILE_TYPE_HOLE) {
    paint_anim(room->terrain_anims[edge_type], canvas, x, y);
  }
}




void paint_edges(ROOM *room, BITMAP *canvas, int row, int col)
{
  /**
   * See if you need to draw edges and draw them.
   */
  paint_edge(room, canvas, row, col, NORTH, TILE_TYPE_N_EDGE);
  paint_edge(room, canvas, row, col, SOUTH, TILE_TYPE_S_EDGE);
  paint_edge(room, canvas, row, col, EAST, TILE_TYPE_E_EDGE);
  paint_edge(room, canvas, row, col, WEST, TILE_TYPE_W_EDGE);
  
  paint_inside_corner_edge(room, canvas, row, col, NE, TILE_TYPE_NE_INSIDE);
  paint_inside_corner_edge(room, canvas, row, col, NW, TILE_TYPE_NW_INSIDE);
  paint_inside_corner_edge(room, canvas, row, col, SE, TILE_TYPE_SE_INSIDE);
  paint_inside_corner_edge(room, canvas, row, col, SW, TILE_TYPE_SW_INSIDE);
  
  paint_outside_corner_edge(room, canvas, row, col, NE, TILE_TYPE_NE_OUTSIDE);
  paint_outside_corner_edge(room, canvas, row, col, NW, TILE_TYPE_NW_OUTSIDE);
  paint_outside_corner_edge(room, canvas, row, col, SE, TILE_TYPE_SE_OUTSIDE);
  paint_outside_corner_edge(room, canvas, row, col, SW, TILE_TYPE_SW_OUTSIDE);
}




void paint_room_terrain(ROOM *room, BITMAP *canvas)
{
  int row;
  int col;
  int x;
  int y;
  int type;
  
  for (row = 0; row < ROWS; row++) {
    for (col = 0; col < COLS; col++) {
      
      /* Paint the tile */
      type = room->terrain[row][col]->type;
      x = col * grab_tile_size();
      y = row * grab_tile_size();
      paint_anim(room->terrain_anims[type], canvas, x, y);
      
      /**
       * A hole is a special case.
       * You need to draw the edge around it.
       */
      if (type == TILE_TYPE_HOLE) {
        paint_edges(room, canvas, row, col);
      }
    }
  }
}




/**
 * Public
 */




ROOM *create_room()
{
  ROOM *room;
  int i;
  int j;

  room = alloc_memory(sizeof(ROOM));

  for (i = 0; i < MAX_ENEMIES; i++) {
    room->enemies[i] = NULL;
  }

  room->num_enemies = 0;

  for (i = 0; i < ROWS; i++) {
    for (j = 0; j < COLS; j++) {
      room->path[i][j] = OFF;
      room->terrain[i][j] = NULL;
      room->messengers[i][j] = NULL;
    }
  }

  for (i = 0; i < MAX_TILE_TYPES; i++) {
    room->terrain_anims[i] = NULL;
  }
  
  for (i = 0; i < MAX_DOORS; i++) {
    room->doors[i] = NULL;
  }
  
  return room;
}




void destroy_room(ROOM *room)
{
  int i;
  int j;

  if (room == NULL) {
    return;
  }

  for (i = 0; i < room->num_enemies; i++) {
    /*destroy_enemy(room->enemies[i]);*/ /* TEMP */
  }

  for (i = 0; i < ROWS; i++) {
    for (j = 0; j < COLS; j++) {
      destroy_tile(room->terrain[i][j]);
      /*destroy_help(room->help[i][j]);*/ /* TEMP */
    }
  }

  for (i = 0; i < MAX_TILE_TYPES; i++) {
    destroy_anim(room->terrain_anims[i]);
  }

  for (i = 0; i < MAX_DOORS; i++) {
    destroy_door(room->doors[i]);
  }

  free_memory(room);
}




void add_door(ROOM *room, DOOR *door)
{
  FLAG done;
  int i;
  
  done = OFF;
  
  for (i = 0; !done && i < MAX_DOORS; i++) {
    if (room->doors[i] == NULL) {
      room->doors[i] = door;
      done = ON;
    }
  }
}




void update_room(ROOM *room)
{
  int i;

  for (i = 0; i < MAX_TILE_TYPES; i++) {
    animate(room->terrain_anims[i]);
  }
}




void paint_room(ROOM *room, BITMAP *canvas)
{
  /*
  int row;
  int col;
  */

  if (room == NULL || canvas == NULL) {
    return;
  }

  /**
   * Paint the terrain
   */
  paint_room_terrain(room, canvas);

  /*
  for (row = 0; row < ROWS; row++) {
    for (col = 0; col < COLS; col++) {
      room->door[row][col];
    }
  }
  */

  /*
  for (row = 0; row < ROWS; row++) {
    for (col = 0; col < COLS; col++) {
      room->help[row][col];
    }
  }
  */

}




FLAG is_walkable(ROOM *room, int row, int col)
{
  if (row < 0 || row >= ROWS) {
    return ON;
  }
  
  if (col < 0 || col >= COLS) {
    return ON;
  }
  
  if (room->terrain[row][col]->obstacle == OBSTACLE_TYPE_WALKABLE) {
    return ON;
  }
  
  return OFF;
}




TILE *create_tile(TILE_TYPE type, OBSTACLE_TYPE obstacle)
{
  TILE *tile;

  tile = alloc_memory(sizeof(TILE));

  tile->type = type;
  tile->obstacle = obstacle;

  return tile;
}




void destroy_tile(TILE *tile)
{
  if (tile == NULL) {
    return;
  }
  
  free_memory(tile);
}




DOOR *create_door(int row, int col, DESTINATION dest, int new_row, int new_col, TRANSITION trans)
{
  DOOR *door;

  door = alloc_memory(sizeof(DOOR));

  door->row = row;
  door->col = col;
  door->dest = dest;
  door->new_row = new_row;
  door->new_col = new_col;
  door->transition = trans;

  return door;
}




void destroy_door(DOOR *door)
{
  if (door == NULL) {
    return;
  }
  
  free_memory(door);
}
