#ifndef ROOM_GEN_HEADER
#define ROOM_GEN_HEADER


#include "utilities.h"


struct ROOM;


typedef enum
{
  ROOM_THEME_FOREST = 0,
  ROOM_THEME_SNOW,
  ROOM_THEME_UNDERGROUND
} ROOM_THEME;


typedef enum
{
  WALL_PRIORITY = 0,
  HOLE_PRIORITY
} TERRAIN_PRIORITY;


typedef struct
{
  /**
   * What percentage of the available tiles you want marked
   * as walls or holes.
   * A tile is unavailable if it is part of the path.
   */
  int percent_walls;
  int percent_holes;

  /**
   * The higher the percent scattered, the more individual
   * walls and holes you will get.
   */
  int percent_scattered_walls;
  int percent_scattered_holes;

  /**
   * Use this to remove the areas of the room that are inaccessable.
   */
  FLAG remove_wall_gaps;
  FLAG remove_hole_gaps;
  
  /**
   * Whether you want the holes or the walls generated first.
   * There probably won't be that much of a difference, but
   * could give a little different effect.
   */
  TERRAIN_PRIORITY priority;

} TERRAIN_OPTIONS;


/**
 * Change the appearance of a room.
 */
void change_room_theme(struct ROOM *room, ROOM_THEME theme);


/**
 * Create a path between two points.
 * A path guarantees that a character will be able
 * to move between the two points.
 * A room can only have one path.
 * If you try to add a new path, it will erase the old one.
 * See "add_to_path".
 */
void create_path(struct ROOM *room, int start_row, int start_col, int end_row, int end_col);

/**
 * Create a path between the existing path and another point.
 * This guarantees that a character will be able to move
 * to the point.
 * If there's no existing path, then only the point will be added.
 */
void add_to_path(struct ROOM *room, int row, int col);


/**
 * Randomly generate the layout of a specified style for a room.
 * It will not generate anything on part of the path.
 */
void generate_terrain(struct ROOM *room, TERRAIN_OPTIONS *options, FLAG show_path);

/**
 * Randomly generate enemies in a room.
 * It will not generate any enemies near any doors.
 */
void generate_enemies(struct ROOM *room, int types);

/**
 * Convert between position and rows and columns.
 */
#define ROWCOL2POS(r, c) (((r) * (COLS)) + (c))
#define POS2ROW(p) ((p) / (COLS))
#define POS2COL(p) ((p) - (((p) / (COLS)) * (COLS)))


#endif
