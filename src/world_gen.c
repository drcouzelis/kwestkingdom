#include "character.h"
#include "direction.h"
#include "player.h"
#include "room.h"
#include "room_gen.h"
#include "sprite.h"
#include "world.h"
#include "world_gen.h"




/**
 * Private
 */




/**
 * This function can be used to see if the game has been won.
 */
FLAG is_in_final_room(WORLD *world)
{
  if (grab_room(world)->num == 40) {
    return ON;
  }
  
  return OFF;
}




/**
 * Randomly generate a row and col point that is
 * on the edge of the screen.
 * Tell it the direction to exclude to prevent creating
 * an exit on the same side as the entrance.
 */
void generate_exit_on_border(int *row, int *col, int exclude_dir)
{
  /**
   * I think this algorithm is kind of stupid.
   * Try making a better one sometime.
   */
  
  int n;
  int s;
  int e;
  int w;
  
  int dir;
  
  n = random_number(1, COLS - 2);
  s = random_number(1, COLS - 2);
  e = random_number(1, ROWS - 2);
  w = random_number(1, ROWS - 2);
  
  dir = random_number(NORTH, WEST);
  
  if (dir == exclude_dir) {
    dir++;
    dir %= 4;
  }
  
  if (dir == NORTH) {
    *row = 0;
    *col = n;
  } else if (dir == SOUTH) {
    *row = ROWS -1;
    *col = s;
  } else if (dir == EAST) {
    *row = e;
    *col = COLS - 1;
  } else {
    *row = w;
    *col = 0;
  }
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
  if (row == 0) {
    return NORTH;
  }
  
  if (row == ROWS - 1) {
    return SOUTH;
  }
  
  if (col == 0) {
    return WEST;
  }
  
  if (col == COLS - 1) {
    return EAST;
  }
  
  return -1;
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
    generate_terrain(room, &terrain);
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
    
    generate_terrain(room, &terrain);
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
  world->is_end_of_world = is_in_final_room;
  
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
  world->is_end_of_world = NULL;
  
  cache_rooms(world);
  
  return world;
}

