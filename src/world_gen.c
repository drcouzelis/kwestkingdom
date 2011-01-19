#include "character.h"
#include "direction.h"
#include "game.h"
#include "player.h"
#include "room.h"
#include "room_gen.h"
#include "sprite.h"
#include "world.h"
#include "world_gen.h"




/**
 * Private
 */




#define NUM_BORDER_TILES 24




/**
 * Randomly generate a row and col point that is
 * on the edge of the screen.
 * Tell it the direction to exclude to prevent creating
 * an exit on the same side as the entrance.
 */
void generate_exit_on_border(int *row, int *col, int from_dir)
{
  int pos;
  int num;
  
  int border_for_n[NUM_BORDER_TILES] = {
    ROWCOL2POS(11, 1),
    ROWCOL2POS(11, 2),
    ROWCOL2POS(11, 3),
    ROWCOL2POS(11, 4),
    ROWCOL2POS(11, 5),
    ROWCOL2POS(11, 6),
    ROWCOL2POS(11, 7),
    ROWCOL2POS(11, 8),
    ROWCOL2POS(11, 9),
    ROWCOL2POS(11, 10),
    ROWCOL2POS(11, 11),
    ROWCOL2POS(11, 12),
    ROWCOL2POS(11, 13),
    ROWCOL2POS(11, 14),
    ROWCOL2POS(6, 0),
    ROWCOL2POS(7, 0),
    ROWCOL2POS(8, 0),
    ROWCOL2POS(9, 0),
    ROWCOL2POS(10, 0),
    ROWCOL2POS(6, 15),
    ROWCOL2POS(7, 15),
    ROWCOL2POS(8, 15),
    ROWCOL2POS(9, 15),
    ROWCOL2POS(10, 15)
  };
  
  int border_for_s[NUM_BORDER_TILES] = {
    ROWCOL2POS(0, 1),
    ROWCOL2POS(0, 2),
    ROWCOL2POS(0, 3),
    ROWCOL2POS(0, 4),
    ROWCOL2POS(0, 5),
    ROWCOL2POS(0, 6),
    ROWCOL2POS(0, 7),
    ROWCOL2POS(0, 8),
    ROWCOL2POS(0, 9),
    ROWCOL2POS(0, 10),
    ROWCOL2POS(0, 11),
    ROWCOL2POS(0, 12),
    ROWCOL2POS(0, 13),
    ROWCOL2POS(0, 14),
    ROWCOL2POS(1, 0),
    ROWCOL2POS(2, 0),
    ROWCOL2POS(3, 0),
    ROWCOL2POS(4, 0),
    ROWCOL2POS(5, 0),
    ROWCOL2POS(1, 15),
    ROWCOL2POS(2, 15),
    ROWCOL2POS(3, 15),
    ROWCOL2POS(4, 15),
    ROWCOL2POS(5, 15)
  };
  
  int border_for_e[NUM_BORDER_TILES] = {
    ROWCOL2POS(1, 0),
    ROWCOL2POS(2, 0),
    ROWCOL2POS(3, 0),
    ROWCOL2POS(4, 0),
    ROWCOL2POS(5, 0),
    ROWCOL2POS(6, 0),
    ROWCOL2POS(7, 0),
    ROWCOL2POS(8, 0),
    ROWCOL2POS(9, 0),
    ROWCOL2POS(10, 0),
    ROWCOL2POS(0, 1),
    ROWCOL2POS(0, 2),
    ROWCOL2POS(0, 3),
    ROWCOL2POS(0, 4),
    ROWCOL2POS(0, 5),
    ROWCOL2POS(0, 6),
    ROWCOL2POS(0, 7),
    ROWCOL2POS(11, 1),
    ROWCOL2POS(11, 2),
    ROWCOL2POS(11, 3),
    ROWCOL2POS(11, 4),
    ROWCOL2POS(11, 5),
    ROWCOL2POS(11, 6),
    ROWCOL2POS(11, 7)
  };
  
  int border_for_w[NUM_BORDER_TILES] = {
    ROWCOL2POS(1, 15),
    ROWCOL2POS(2, 15),
    ROWCOL2POS(3, 15),
    ROWCOL2POS(4, 15),
    ROWCOL2POS(5, 15),
    ROWCOL2POS(6, 15),
    ROWCOL2POS(7, 15),
    ROWCOL2POS(8, 15),
    ROWCOL2POS(9, 15),
    ROWCOL2POS(10, 15),
    ROWCOL2POS(0, 8),
    ROWCOL2POS(0, 9),
    ROWCOL2POS(0, 10),
    ROWCOL2POS(0, 11),
    ROWCOL2POS(0, 12),
    ROWCOL2POS(0, 13),
    ROWCOL2POS(0, 14),
    ROWCOL2POS(11, 8),
    ROWCOL2POS(11, 9),
    ROWCOL2POS(11, 10),
    ROWCOL2POS(11, 11),
    ROWCOL2POS(11, 12),
    ROWCOL2POS(11, 13),
    ROWCOL2POS(11, 14)
  };
  
  num = random_number(0, NUM_BORDER_TILES - 1);
  
  if (from_dir == NORTH) {
    pos = border_for_n[num];
  } else if (from_dir == SOUTH) {
    pos = border_for_s[num];
  } else if (from_dir == EAST) {
    pos = border_for_e[num];
  } else {
    pos = border_for_w[num];
  }
  
  *row = POS2ROW(pos);
  *col = POS2COL(pos);
}




int flip_door_row(int row)
{
  if (row == ROWS - 1) {
    return 0;
  }
  
  if (row == 0) {
    return ROWS - 1;
  }
  
  return row;
}




int flip_door_col(int col)
{
  if (col == COLS - 1) {
    return 0;
  }
  
  if (col == 0) {
    return COLS - 1;
  }
  
  return col;
}




int shift_door_row(int row)
{
  if (row == ROWS - 1) {
    return row + 1;
  }
  
  if (row == 0) {
    return row - 1;
  }
  
  return row;
}




int shift_door_col(int col)
{
  if (col == COLS - 1) {
    return col + 1;
  }
  
  if (col == 0) {
    return col - 1;
  }
  
  return col;
}




int calc_edge_dir(int row, int col)
{
  int map[ROWS][COLS] = {
    {NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH},
    { WEST,  WEST, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH,  EAST,  EAST},
    { WEST,  WEST,  WEST,  WEST, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH, NORTH,  EAST,  EAST,  EAST,  EAST},
    { WEST,  WEST,  WEST,  WEST,  WEST,  WEST, NORTH, NORTH, NORTH, NORTH,  EAST,  EAST,  EAST,  EAST,  EAST,  EAST},
    { WEST,  WEST,  WEST,  WEST,  WEST,  WEST,  WEST,  WEST, NORTH, NORTH,  EAST,  EAST,  EAST,  EAST,  EAST,  EAST},
    { WEST,  WEST,  WEST,  WEST,  WEST,  WEST,  WEST,  WEST,  EAST,  EAST,  EAST,  EAST,  EAST,  EAST,  EAST,  EAST},
    { WEST,  WEST,  WEST,  WEST,  WEST,  WEST,  WEST,  WEST,  EAST,  EAST,  EAST,  EAST,  EAST,  EAST,  EAST,  EAST},
    { WEST,  WEST,  WEST,  WEST,  WEST,  WEST, SOUTH, SOUTH,  EAST,  EAST,  EAST,  EAST,  EAST,  EAST,  EAST,  EAST},
    { WEST,  WEST,  WEST,  WEST,  WEST,  WEST, SOUTH, SOUTH, SOUTH, SOUTH,  EAST,  EAST,  EAST,  EAST,  EAST,  EAST},
    { WEST,  WEST,  WEST,  WEST, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH,  EAST,  EAST,  EAST,  EAST},
    { WEST,  WEST, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH,  EAST,  EAST},
    {SOUTH, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH, SOUTH}
  };
  
  return map[row][col];
}




ROOM *create_story_world_room(WORLD *world, int num)
{
  ROOM *room;
  
  DOOR *door;
  
  ROOM *prev_room = NULL;
  DOOR *prev_door = NULL;
  int i;
  
  int entr_row;
  int entr_col;
  
  int exit_row;
  int exit_col;
  
  TERRAIN_OPTIONS terrain = {40, 0, 50, 0, OFF, OFF, WALL_PRIORITY};
  int terrain_percent;
  
  room = create_room();
  room->num = num;
  
  if (num == 1) {
    
    entr_row = world->player->character->sprite->row;
    entr_col = world->player->character->sprite->col;
    
    generate_exit_on_border(&exit_row, &exit_col, SOUTH);
    
    door = create_door(
      shift_door_row(exit_row),
      shift_door_col(exit_col),
      num + 1,
      flip_door_row(exit_row),
      flip_door_col(exit_col)
    );
    
    add_door(room, door);
    
    change_room_theme(room, ROOM_THEME_FOREST);
    create_path(room, entr_row, entr_col, exit_row, exit_col);
    generate_terrain(room, &terrain, ON);
  }
  
  if (num >= 2) {
    
    /**
     * Get a pointer to the previous room
     */
    for (i = 0; prev_room == NULL && i < MAX_ROOMS; i++) {
      if (world->rooms[i]->num == num - 1) {
        prev_room = world->rooms[i];
      }
    }
    
    /**
     * Get a pointer to the previous door
     */
    for (i = 0; prev_door == NULL && i < MAX_DOORS; i++) {
      if (prev_room->doors[i]->new_room_num == num) {
        prev_door = prev_room->doors[i];
      }
    }
    
    entr_row = prev_door->new_row;
    entr_col = prev_door->new_col;
    
    generate_exit_on_border(&exit_row, &exit_col, calc_edge_dir(entr_row, entr_col));
    
    /**
     * Add the exit
     */
    door = create_door(
      shift_door_row(exit_row),
      shift_door_col(exit_col),
      num + 1,
      flip_door_row(exit_row),
      flip_door_col(exit_col)
    );
    
    add_door(room, door);
    
    /**
     * Add the entrance
     */
    door = create_door(
      shift_door_row(entr_row),
      shift_door_col(entr_col),
      num - 1,
      flip_door_row(entr_row),
      flip_door_col(entr_col)
    );
    
    add_door(room, door);
    
    change_room_theme(room, ROOM_THEME_FOREST);
    create_path(room, entr_row, entr_col, exit_row, exit_col);
    
    /**
     * Randomly generate some crazy terrain
     */
    terrain_percent = random_number(0, 80);
    terrain.percent_walls = random_number(0, terrain_percent);
    terrain.percent_holes = terrain_percent - terrain.percent_walls;
    terrain.percent_scattered_walls = random_number(0, 100);
    terrain.percent_scattered_holes = random_number(0, 100);
    terrain.priority = random_number(0, 1);
    
    generate_terrain(room, &terrain, ON);
  }
  
  return room;
}




ROOM *create_endless_world_room(WORLD *world, int num)
{
  world = world; /* TEMP */
  num = num;
  
  return NULL;
}




/**
 * Public
 */




WORLD *create_story_world()
{
  WORLD *world;
  
  world = create_world();
  
  world->num_cached_rooms = 10;
  world->max_cached_rooms = 10;
  world->create_room = create_story_world_room;
  world->final_room = 40;
  
  cache_rooms(world);
  
  return world;
}




WORLD *create_endless_world()
{
  WORLD *world;
  
  world = create_world();
  
  world->num_cached_rooms = 10;
  world->max_cached_rooms = 10;
  world->create_room = create_endless_world_room;
  world->final_room = -1;
  
  cache_rooms(world);
  
  return world;
}

