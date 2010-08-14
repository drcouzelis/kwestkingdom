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


typedef struct
{
  int percent_walls;
  FLAG group_walls;
  int percent_holes;
  FLAG group_holes;
} TERRAIN_OPTIONS;


/**
 * Set the appearance of a room.
 */
void set_room_theme(struct ROOM *room, ROOM_THEME theme);


/**
 * Create a path between two points.
 * A path guarantees that a character will be able
 * to move between the two points.
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
void generate_terrain(struct ROOM *room, TERRAIN_OPTIONS *options);

/**
 * Randomly generate enemies in a room.
 * It will not generate any enemies near any doors.
 */
void generate_enemies(struct ROOM *room, int types);


#endif
