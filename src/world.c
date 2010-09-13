#include "character.h"
#include "player.h"
#include "room.h"
#include "sprite.h"
#include "world.h"



WORLD *create_world()
{
  WORLD *world;
  int i;

  world = malloc(sizeof(WORLD));

  world->player = create_player();
  warp_sprite(world->player->character->sprite, ROWS - 3, COLS / 2);

  for (i = 0; i < MAX_ROOMS; i++) {
    world->rooms[i] = NULL;
  }

  world->num_rooms = 0;
  world->room_idx = 0;

  return world;
}




void destroy_world(WORLD *world)
{
  if (world == NULL) {
    return;
  }

  destroy_player(world->player);
  
  clear_rooms(world);

  free(world);
}




void add_room(WORLD *world, ROOM *room)
{
  if (world == NULL || room == NULL) {
    return;
  }
  
  world->rooms[world->num_rooms] = room;
  world->num_rooms++;
}




void clear_rooms(WORLD *world)
{
  int i;
  
  if (world == NULL) {
    return;
  }
  
  for (i = 0; i < MAX_ROOMS; i++) {
    destroy_room(world->rooms[i]);
  }
}




void update_world(WORLD *world)
{
  update_player(world->player, world);
  update_room(world->rooms[world->room_idx]);
}




void paint_world(WORLD *world, BITMAP *canvas)
{
  paint_room(world->rooms[world->room_idx], canvas);
  paint_sprite(world->player->character->sprite, canvas);
}
