#include "anim.h"
#include "direction.h"
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




/**
 * An internal data structure used to calculate a path.
 */
typedef struct
{
  /**
   * A "working area" for the new path.
   * You could think of this as "new_path" instead of "mask".
   */
  FLAG mask[ROWS][COLS];

  /**
   * As the algorithm searches for a path, it needs to remember
   * which tiles it has already looked at.
   * That information is saved in this "history".
   */
  FLAG hist[ROWS][COLS];
} PATH_ALG_DATA;




FLAG is_path_between_points(PATH_ALG_DATA *data, int r1, int c1, int r2, int c2);

int calc_pos_from_row_and_col(int row, int col);
int calc_row_from_pos(int pos);
int calc_col_from_pos(int pos);




void create_path(ROOM *room, int start_row, int start_col, int end_row, int end_col)
{
  PATH_ALG_DATA data;

  int list[ROWS * COLS];
  int len;

  int row;
  int col;
  int i;

  int rand_num;
  int rand_row;
  int rand_col;

  /**
   * For convenience
   */
  int r1 = start_row;
  int c1 = start_col;
  int r2 = end_row;
  int c2 = end_col;

  /**
   * Initialize the data needed for this algorithm.
   * Fill the tile mask with tiles.
   */
  for (row = 0; row < ROWS; row++) {
    for (col = 0; col < COLS; col++) {

      /**
       * Each room in this game will have a wall around it.
       * The wall is one tile thick.
       */
      if (row == 0 || row == ROWS - 1 || col == 0 || col == COLS - 1) {
        if (room->path[row][col]) {
          data.mask[row][col] = ON;
        } else {
          data.mask[row][col] = OFF;
        }
      } else {
        data.mask[row][col] = ON;
      }
    }
  }

  /**
   * Mark the two points we are making a path between
   * as part of the path.
   */
  data.mask[r1][c1] = ON;
  data.mask[r2][c2] = ON;

  /**
   * Create a list of sequential numbers,
   * representing each tile on the map.
   */
  for (i = 0; i < ROWS * COLS; i++) {
    list[i] = i;
  }

  len = ROWS * COLS;

  /**
   * Loop through every tile
   */
  while (len > 0) {

    /**
     * Randomly pick a tile
     */
    rand_num = random_number(0, len - 1);
    rand_row = calc_row_from_pos(list[rand_num]);
    rand_col = calc_col_from_pos(list[rand_num]);

    /**
     * There's no need to do anything if the randomly selected
     * tile is already part of the path.
     */
    if (room->path[rand_row][rand_col] == OFF) {

      if (rand_row == r1 && rand_col == c1) {

        /* The start of the path. Don't remove! */

      } else if (rand_row == r2 && rand_col == c2) {

        /* The end of the path. Don't remove! */

      } else {

        /**
         * Let's see what happens when we remove the
         * randomly selected tile...
         */
        data.mask[rand_row][rand_col] = OFF;

        if (!is_path_between_points(&data, r1, c1, r2, c2)) {

          /**
           * Removing the tile broke the path, so put it back
           */
          data.mask[rand_row][rand_col] = ON;
        }
      }
    }


    /**
     * You can kind of think of this line of code as doing a "sort"
     * on the list of tiles.
     * Remove the randomly selected tile from the list.
     * Replace it with the tile that is currently at the end
     * of the list.
     */
    list[rand_num] = list[len - 1];

    /**
     * And now we have one less tile to look at.
     */
    len--;
  }

  /**
   * Finally, save the mask as the new path!
   */
  for (row = 0; row < ROWS; row++) {
    for (col = 0; col < COLS; col++) {
      room->path[row][col] = data.mask[row][col];
    }
  }
}




void add_to_path(struct ROOM *room, int row, int col)
{
  /**
   * Create a new tile map.
   * Fill the tile map with tiles.
   */

  /**
   * Randomly loop through every tile in the tile map.
   */

    /**
     * If the randomly selected tile is "blocked" by the
     * existing path in the room, then just remove it.
     */

    /**
     * Otherwise, try removing the randomly selected tile.
     * If a path still exists between the point and any
     * tile in the existing path in the room,
     * then leave it removed. Otherwise, put it back.
     */

  int c;
  int r;
  FLAG path_found = OFF;

  /**
   * Find the existing path...
   */
  for (r = 0; !path_found && r < ROWS; r++) {
    for (c = 0; !path_found && c < COLS; c++) {
      if (room->path[r][c]) {
        path_found = ON;
      }
    }
  }

  if (path_found) {

    create_path(room, row, col, r, c);

  } else {

    /**
     * If no existing path was found, just mark the one
     * spot as the "path".
     */
    room->path[row][col] = ON;
  }
}




void generate_terrain(ROOM *room, TERRAIN_OPTIONS *options)
{
  /* TEMP */
  int row;
  int col;

  for (row = 0; row < ROWS; row++) {
    for (col = 0; col < COLS; col++) {

      if (room->path[row][col]) {
        room->tiles[row][col] = create_tile(TILE_TYPE_EMPTY, OBSTACLE_TYPE_NONE);
      } else {
        room->tiles[row][col] = create_tile(TILE_TYPE_WALL, OBSTACLE_TYPE_FLYABLE);
      }
    }
  }

  /**
   * Create a list of the tiles that are not part of the path.
   */

  /**
   * Use the percentage to calculate how many tiles to make into walls.
   */

  /**
   * Of that number of tiles, use the percentage scattered to calculate
   * how many tiles to initially make into walls.
   */

  /**
   * Randomly select that number of tiles and mark them as walls.
   */

  /**
   * For the rest of the number of tiles that need to be marked,
   * randomly select a tile,
   * and if it's not part of the path and it's next to a wall,
   * then mark it as a wall and reset the list of tiles to look through.
   */

  /**
   * If you get to the end of the list of tiles and still haven't
   * selected one for the wall, then go through the list again and
   * put a wall on the first available randomly selected tile.
   */

  options = options; /* TEMP */
}




void generate_enemies(ROOM *room, int types)
{
  room = room; /* TEMP */
  types = types; /* TEMP */
}

/**
 * Internal functions
 */




FLAG is_path_between_points_rec(PATH_ALG_DATA *data, int r1, int c1, int r2, int c2)
{
  /**
   * Warning!
   * Recursion! <3
   */

  int row;
  int col;
  int dir;

  /**
   * If the two points match, you're done!
   */
  if (r1 == r2 && c1 == c2) {
    return ON;
  }

  /**
   * Mark this spot in the history.
   */
  data->hist[r1][c1] = ON;

  /**
   * Trace a path through the four cardinal directions.
   * If you find a path, then great! Stop searching.
   * If not, keep searching and searching.
   */
  for (dir = NORTH; dir <= WEST; dir++) {

    row = r1 + cardinals[dir].v_offset;
    col = c1 + cardinals[dir].h_offset;

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
      continue;
    }

    if (data->mask[row][col] == ON && data->hist[row][col] == OFF) {
      if (is_path_between_points_rec(data, row, col, r2, c2)) {
        return ON;
      }
    }
  }

  /**
   * When no paths are left to search, give up.
   */
  return OFF;
}




FLAG is_path_between_points(PATH_ALG_DATA *data, int r1, int c1, int r2, int c2)
{
  int row;
  int col;

  /**
   * Clear the history map.
  */
  for (row = 0; row < ROWS; row++) {
    for (col = 0; col < COLS; col++) {
      data->hist[row][col] = OFF;
    }
  }

  return is_path_between_points_rec(data, r1, c1, r2, c2);
}



int calc_pos_from_row_and_col(int row, int col)
{
  return (row * COLS) + col;
}




int calc_row_from_pos(int pos)
{
  return pos / COLS;
}




int calc_col_from_pos(int pos)
{
  return pos - ((pos / COLS) * COLS);
}
