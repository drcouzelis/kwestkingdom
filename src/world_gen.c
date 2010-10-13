#include "room.h"
#include "room_gen.h"
#include "world.h"
#include "world_gen.h"




/**
 * Create a new set of cached rooms.
 * If the number of rooms in the world exceeds the
 * max number of cached rooms, then some rooms will
 * be removed.
 */
void cache_rooms(WORLD *world)
{
  ROOM *room;
  
  TERRAIN_OPTIONS terrain = {40, 0, 50, 0, OFF, OFF, WALL_PRIORITY};
  
  int i;
  
  for (i = 0; i < world->num_cached_rooms; i++) {
    
    room = create_room();
    set_room_theme(room, ROOM_THEME_FOREST);
    create_path(room, ROWS - 3, COLS / 2, 0, COLS / 2);
    generate_terrain(room, &terrain);
    
    add_room(world, room);
  }
}




WORLD *create_story_world()
{
  WORLD *world;
  
  world = create_world();
  
  cache_rooms(world);
  
  return world;
}




WORLD *create_endless_world()
{
  WORLD *world;
  
  world = create_world();
  
  return world;
}




/**
 * Internal functions
 */




ROOM *create_story_world_room(WORLD *world, int num)
{
  world = world; /* TEMP */
  num = num;
  
  return NULL;
}




ROOM *create_endless_world_room(WORLD *world, int num)
{
  world = world; /* TEMP */
  num = num;
  
  return NULL;
}
