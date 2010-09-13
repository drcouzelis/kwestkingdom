#ifndef WORLD_HEADER
#define WORLD_HEADER


#include <allegro.h>


#define MAX_ROOMS 40


typedef struct WORLD WORLD;
struct PLAYER;
struct ROOM;


struct WORLD
{
  /**
   * Represents the player, aka the hero!
   */
  struct PLAYER *player;
  
  /**
   * A list of the rooms in this world.
   */
  struct ROOM *rooms[MAX_ROOMS];
  int num_rooms;
  int room_idx;
};


WORLD *create_world();
void destroy_world(WORLD *world);

void add_room(WORLD *world, struct ROOM *room);
void clear_rooms(WORLD *world);

void update_world(WORLD *world);
void paint_world(WORLD *world, BITMAP *canvas);


#endif
