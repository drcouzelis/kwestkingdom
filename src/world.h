#ifndef WORLD_HEADER
#define WORLD_HEADER


#include <allegro.h>


#define MAX_ROOMS 40


typedef struct WORLD WORLD;
struct PLAYER;
struct ROOM;


typedef enum
{
  STORY_WORLD = 0,
  ENDLESS_WORLD
} WORLD_TYPE;


struct WORLD
{
  /**
   * What type of world this is.
   */
  WORLD_TYPE type;
  
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
  
  /**
   * The room number that is currently occupied.
   * This may be greater than the number of rooms that
   * are currently in the world.
   */
  int room_num;
  
  /**
   * When it comes times to create a new set of rooms,
   * this many rooms will be created at a time.
   */
  int num_cached_rooms; /* Try 10 */
  
  /**
   * When the max number of cached rooms is met,
   * one room will be deleted for every new cached
   * room that is created.
   * The max number of cached rooms must be equal
   * to or greater than the number of cached rooms.
   * (It doesn't make sense otherwise)
   */
  int max_cached_rooms; /* Try 10 */
};


WORLD *create_world();
void destroy_world(WORLD *world);

void add_room(WORLD *world, struct ROOM *room);
void clear_rooms(WORLD *world);
struct ROOM *current_room(WORLD *world);

void update_world(WORLD *world);
void paint_world(WORLD *world, BITMAP *canvas);


#endif
