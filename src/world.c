#include "player.h"
#include "world.h"



WORLD *create_world()
{
  WORLD *world;
  int i;

  world = malloc(sizeof(WORLD));

  /*world->player = create_player();*/

  for (i = 0; i < MAX_ROOMS; i++) {
    world->rooms[i] = NULL;
  }

  world->num_rooms = 0;
  world->room_idx = 0;

  return world;
}




void destroy_world(WORLD *world)
{
  int i;

  if (world == NULL) {
    return;
  }

  /*destroy_player(world->player);*/

  for (i = 0; i < MAX_ROOMS; i++) {
    /*destroy_room(world->room[i]);*/
  }

  free(world);
}




void update_world(WORLD *world)
{
  world = world; /* TEMP */
}




void paint_world(WORLD *world, BITMAP *canvas)
{
  world = world; /* TEMP */
  canvas = canvas; /* TEMP */
}
