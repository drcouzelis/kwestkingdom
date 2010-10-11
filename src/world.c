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

  world->type = STORY_WORLD;
  
  world->player = create_player();
  warp_sprite(world->player->character->sprite, ROWS - 3, COLS / 2);

  for (i = 0; i < MAX_ROOMS; i++) {
    world->rooms[i] = NULL;
  }

  world->num_rooms = 0;
  world->room_idx = 0;
  
  world->room_num = 0;

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
  
  /**
   * If using door
   *   Draw current room to canvas
   *   If next room doesn't exist
   *     Create a new set of cached rooms (amount is num_cached_rooms)
   *     When adding a room, check max_cached_rooms and delete as needed
   *     For every door-reference to the deleted room, mark the door as a wall
   *   Move to the next room
   */
}




void paint_world(WORLD *world, BITMAP *canvas)
{
  paint_room(world->rooms[world->room_idx], canvas);
  paint_sprite(world->player->character->sprite, canvas);
}
