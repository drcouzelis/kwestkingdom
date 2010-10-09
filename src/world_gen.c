#include "world.h"
#include "world_gen.h"




WORLD *create_story_world()
{
  WORLD *world;
  
  world = create_world();
  
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




void generate_endless_rooms(WORLD *world)
{
  world = world; /* TEMP */
}




void generate_forest_rooms(WORLD *world)
{
  world = world; /* TEMP */
}
