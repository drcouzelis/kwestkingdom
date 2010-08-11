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
} LAYOUT_OPTIONS;


/**
 * Set the appearance of a room.
 */
void set_room_theme(struct ROOM *room, ROOM_THEME theme);


void create_path(struct ROOM *room, int start_x, int start_y, int end_x, int end_y);

/**
 * Randomly generate the layout of a specified style for a room.
 * It will not generate anything on part of the path or any door.
 */
void generate_layout(struct ROOM *room, LAYOUT_OPTIONS *options);

/**
 * Randomly generate enemies in a room.
 * It will not generate any enemies near any doors.
 */
void generate_enemies(struct ROOM *room, int types);


#endif
