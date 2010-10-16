#include "character.h"
#include "direction.h"
#include "player.h"
#include "room.h"
#include "room_gen.h"
#include "sprite.h"
#include "world.h"
#include "world_gen.h"




ROOM *create_story_world_room(WORLD *world, int num);
ROOM *create_endless_world_room(WORLD *world, int num);
void cache_rooms(WORLD *world);
FLAG completed_final_room(WORLD *world);




WORLD *create_story_world()
{
  WORLD *world;
  
  world = create_world();
  
  world->num_cached_rooms = 10;
  world->max_cached_rooms = 10;
  world->create_room = create_story_world_room;
  world->is_game_won = completed_final_room;
  
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
  world->is_game_won = NULL;
  
  cache_rooms(world);
  
  return world;
}




/**
 * Internal functions
 */




FLAG completed_final_room(WORLD *world)
{
  if (current_room(world)->num == 40) {
    return ON;
  }
  
  return OFF;
}




/**
 * Create a new set of cached rooms.
 * If the number of rooms in the world exceeds the
 * max number of cached rooms, then some rooms will
 * be removed.
 */
void cache_rooms(WORLD *world)
{
  ROOM *room;
  
  int i;
  
  for (i = 0; i < world->num_cached_rooms; i++) {
    
    room = world->create_room(world, find_highest_room_number(world) + 1);
    
    add_room(world, room);
  }
}




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




ROOM *create_story_world_room(WORLD *world, int num)
{
  ROOM *room;
  
  DOOR *door;
  
  int entr_row;
  int entr_col;
  
  int exit_row;
  int exit_col;
  
  TERRAIN_OPTIONS terrain = {40, 0, 50, 0, OFF, OFF, WALL_PRIORITY};
  
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
    
    set_room_theme(room, ROOM_THEME_FOREST);
    create_path(room, entr_row, entr_col, exit_row, exit_col);
    generate_terrain(room, &terrain);
  }
  
  add_room(world, room);
  
  return NULL;
}




ROOM *create_endless_world_room(WORLD *world, int num)
{
  world = world; /* TEMP */
  num = num;
  
  return NULL;
}
