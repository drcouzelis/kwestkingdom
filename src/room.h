#ifndef ROOM_HEADER
#define ROOM_HEADER


#include <allegro.h>
#include "utilities.h"


#define COLS 16
#define ROWS 12

#define MAX_ENEMIES 100


typedef struct DOOR DOOR;
typedef struct ROOM ROOM;
typedef struct TILE TILE;
struct ANIM;
struct DOOR;
struct ENEMY;
struct HELP;
struct TILE;


struct DOOR
{
  int new_room_num;
  int new_row;
  int new_col;
};


typedef enum
{
  TILE_TYPE_EMPTY = 0,
  TILE_TYPE_HOLE,
  TILE_TYPE_WALL,
  
  /**
   * An edge appears between a hole and an empty tile.
   */
  TILE_TYPE_N_EDGE,
  TILE_TYPE_S_EDGE,
  TILE_TYPE_E_EDGE,
  TILE_TYPE_W_EDGE,
  
  /**
   * These appear on edge corners.
   */
  TILE_TYPE_NE_INSIDE,
  TILE_TYPE_SE_INSIDE,
  TILE_TYPE_NW_INSIDE,
  TILE_TYPE_SW_INSIDE,
  TILE_TYPE_NE_OUTSIDE,
  TILE_TYPE_SE_OUTSIDE,
  TILE_TYPE_NW_OUTSIDE,
  TILE_TYPE_SW_OUTSIDE,
  
  MAX_TILE_TYPES
} TILE_TYPE;


struct ROOM
{
  /**
   * A list of the enemies currently in the room.
   */
  struct ENEMY *enemies[MAX_ENEMIES];
  int num_enemies;
  
  /**
   * Spaces marked as part of the path are not allowed
   * to have any walls or holes.
   * This is used to guarantee, for example, that the
   * player will be able to walk from one door to another.
   */
  FLAG path[ROWS][COLS];
  
  /**
   * A map of the terrain in the room.
   */
  struct TILE *terrain[ROWS][COLS];
  
  /**
   * Appearance of different types of terrain.
   */
  struct ANIM *terrain_anims[MAX_TILE_TYPES];
  
  /**
   * A map of the help tiles in the room.
   */
  struct HELP *help[ROWS][COLS];
  
  /**
   * A map of the doors in the room.
   */
  struct DOOR *doors[ROWS][COLS];
};


/**
 * The different types of terrain
 */
typedef enum
{
  OBSTACLE_TYPE_NONE = 0,
  OBSTACLE_TYPE_SWIMMABLE,
  OBSTACLE_TYPE_WALKABLE,
  OBSTACLE_TYPE_FLYABLE,
  OBSTACLE_TYPE_SOARABLE,
  MAX_OBSTACLE_TYPES
} OBSTACLE_TYPE;


struct TILE
{
  /**
   * Use a shared animation for the tiles to save on
   * memory and speed.
   */
  TILE_TYPE type;
  
  /**
   * Helps determine how a character can interact
   * with this tile.
   */
  OBSTACLE_TYPE obstacle;
};


/**
 * Create and destroy doors
 */
DOOR *create_door(int new_room_num, int new_row, int new_col);
void destroy_door(DOOR *door);

/**
 * Room controls
 */
ROOM *create_room();
void destroy_room(ROOM *room);

void add_door(ROOM *room, DOOR *door, int row, int col);

void update_room(ROOM *room);
void paint_room(ROOM *room, BITMAP *canvas);

/**
 * Create and destroy tiles
 */
TILE *create_tile(TILE_TYPE type, OBSTACLE_TYPE obstacle);
void destroy_tile(TILE *tile);


#endif
