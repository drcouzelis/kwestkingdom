#include "anim.h"
#include "direction.h"
#include "room.h"
#include "kwestkingdom.h"




DOOR *create_door(int new_room_num, int new_row, int new_col)
{
  DOOR *door;

  door = malloc(sizeof(DOOR));

  door->new_room_num = new_room_num;
  door->new_row = new_row;
  door->new_col = new_col;

  return door;
}




void destroy_door(DOOR *door)
{
  if (door == NULL) {
    return;
  }
  free(door);
}




ROOM *create_room()
{
  ROOM *room;
  int i;
  int j;

  room = malloc(sizeof(ROOM));

  for (i = 0; i < MAX_ENEMIES; i++) {
    room->enemies[i] = NULL;
  }

  room->num_enemies = 0;

  for (i = 0; i < ROWS; i++) {
    for (j = 0; j < COLS; j++) {
      room->path[i][j] = OFF;
      room->terrain[i][j] = NULL;
      room->help[i][j] = NULL;
      room->doors[i][j] = NULL;
    }
  }

  for (i = 0; i < MAX_TILE_TYPES; i++) {
    room->terrain_anims[i] = NULL;
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
    free(room->enemies[i]);
  }

  for (i = 0; i < ROWS; i++) {
    for (j = 0; j < COLS; j++) {
      destroy_tile(room->terrain[i][j]);
      free(room->help[i][j]);
      destroy_door(room->doors[i][j]);
    }
  }

  for (i = 0; i < MAX_TILE_TYPES; i++) {
    free(room->terrain_anims[i]);
  }

  free(room);
}




void add_door(ROOM *room, DOOR *door, int row, int col)
{
  if (room == NULL || door == NULL) {
    return;
  }

  if (row < 0 || row >= ROWS) {
    return;
  }

  if (col < 0 || col >= COLS) {
    return;
  }

  free(room->doors[row][col]);

  room->doors[row][col] = door;
}




void update_room(ROOM *room)
{
  int i;

  for (i = 0; i < MAX_TILE_TYPES; i++) {
    animate(room->terrain_anims[i]);
  }
}




void paint_room_terrain(ROOM *room, BITMAP *canvas);




void paint_room(ROOM *room, BITMAP *canvas)
{
  /*
  int row;
  int col;
  int x;
  int y;
  int type;
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
      type = room->terrain[row][col]->type;
      x = col * get_tile_size();
      y = row * get_tile_size();
      paint_anim(room->terrain_anims[type], canvas, x, y);
    }
  }
  */

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
      room->hel[row][col];
    }
  }
  */

}




TILE *create_tile(TILE_TYPE type, OBSTACLE_TYPE obstacle)
{
  TILE *tile;

  tile = malloc(sizeof(TILE));

  if (type < MAX_TILE_TYPES) {
    tile->type = type;
  } else {
    tile->type = TILE_TYPE_EMPTY;
  }

  if (obstacle < MAX_OBSTACLE_TYPES) {
    tile->obstacle = obstacle;
  } else {
    tile->obstacle = OBSTACLE_TYPE_NONE;
  }

  return tile;
}




void destroy_tile(TILE *tile)
{
  if (tile == NULL) {
    return;
  }
  free(tile);
}




void paint_room_terrain(ROOM *room, BITMAP *canvas)
{
  int row;
  int col;
  int trow = 0; /* temp row */
  int tcol = 0; /* temp col */
  int x;
  int y;
  int d; /* direction */
  int type;

  for (row = 0; row < ROWS; row++) {
    for (col = 0; col < COLS; col++) {

      /* Paint the tile */
      type = room->terrain[row][col]->type;
      x = col * get_tile_size();
      y = row * get_tile_size();
      paint_anim(room->terrain_anims[type], canvas, x, y);

      /**
       * A hole is a special case.
       * You need to draw the edge around it.
       */
      if (type == TILE_TYPE_HOLE) {

        for (d = NORTH; d <= WEST; d++) {

          /**
           * If the adjacent tile is not another hole...
           */
          trow = row + cardinals[d].v_offset;
          tcol = col + cardinals[d].h_offset;
          type = room->terrain[trow][tcol]->type;

          if (type != TILE_TYPE_HOLE) {

            /**
             * ...then add an edge.
             */
            x = tcol * get_tile_size();
            y = trow * get_tile_size();
            paint_anim(room->terrain_anims[type], canvas, x, y);
          }
        }

      }

    }
  }

  /**
   * Add the shore corners
   */
  for (row = 0; row < ROWS; row++) {
    for (col = 0; col < COLS; col++) {

      if (room->terrain[row][col]->type == TILE_TYPE_HOLE) {

        x = tcol * get_tile_size();
        y = trow * get_tile_size();

        /**
         * Add the shore inside corners
         */

        /* North East */
        if (
          room->terrain[row][col - 1]->type != TILE_TYPE_HOLE &&
          room->terrain[row + 1][col]->type != TILE_TYPE_HOLE
        ) {
          paint_anim(room->terrain_anims[TILE_TYPE_NE_INSIDE], canvas, x, y);
        }

        /* South East */
        if (
          room->terrain[row][col + 1]->type != TILE_TYPE_HOLE &&
          room->terrain[row + 1][col]->type != TILE_TYPE_HOLE
        ) {
          paint_anim(room->terrain_anims[TILE_TYPE_SE_INSIDE], canvas, x, y);
        }

        /* North West */
        if (
          room->terrain[row][col - 1]->type != TILE_TYPE_HOLE &&
          room->terrain[row - 1][col]->type != TILE_TYPE_HOLE
        ) {
          paint_anim(room->terrain_anims[TILE_TYPE_NW_INSIDE], canvas, x, y);
        }

        /* South West */
        if (
          room->terrain[row][col + 1]->type != TILE_TYPE_HOLE &&
          room->terrain[row - 1][col]->type != TILE_TYPE_HOLE
        ) {
          paint_anim(room->terrain_anims[TILE_TYPE_SW_INSIDE], canvas, x, y);
        }

        /**
         * Add the shore outside corners
         */

        /* North East */
        if (
          room->terrain[row][col - 1]->type == TILE_TYPE_HOLE &&
          room->terrain[row + 1][col]->type == TILE_TYPE_HOLE &&
          room->terrain[row + 1][col - 1]->type != TILE_TYPE_HOLE
        ) {
          paint_anim(room->terrain_anims[TILE_TYPE_NE_OUTSIDE], canvas, x, y);
        }

        /* South East */
        if (
          room->terrain[row][col + 1]->type == TILE_TYPE_HOLE &&
          room->terrain[row + 1][col]->type == TILE_TYPE_HOLE &&
          room->terrain[row + 1][col + 1]->type != TILE_TYPE_HOLE
        ) {
          paint_anim(room->terrain_anims[TILE_TYPE_SE_OUTSIDE], canvas, x, y);
        }

        /* North West */
        if (
          room->terrain[row][col - 1]->type == TILE_TYPE_HOLE &&
          room->terrain[row - 1][col]->type == TILE_TYPE_HOLE &&
          room->terrain[row - 1][col - 1]->type != TILE_TYPE_HOLE
        ) {
          paint_anim(room->terrain_anims[TILE_TYPE_NW_OUTSIDE], canvas, x, y);
        }

        /* South West */
        if (
          room->terrain[row][col + 1]->type == TILE_TYPE_HOLE &&
          room->terrain[row - 1][col]->type == TILE_TYPE_HOLE &&
          room->terrain[row - 1][col + 1]->type != TILE_TYPE_HOLE
        ) {
          paint_anim(room->terrain_anims[TILE_TYPE_SW_OUTSIDE], canvas, x, y);
        }

      }

    }
  }

}
