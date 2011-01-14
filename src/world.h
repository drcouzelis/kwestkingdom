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
   * A list of rooms in this world.
   * Rooms will always be in order based on their number.
   */
  struct ROOM *rooms[MAX_ROOMS];
  int room_idx;
  
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
  
  /**
   * This function is used to create new rooms.
   * Different types of rooms need to be made for
   * different types of world.
   */
  ROOM *(*create_room)(WORLD *world, int num);
  
  /**
   * This function is used to see if the game
   * has been won.
   * Different types of worlds have different
   * win conditions.
   */
  FLAG (*is_end_of_world)(WORLD *world);
};


WORLD *create_world();
void destroy_world(WORLD *world);

/**
 * Add a room to the world.
 * Rooms will always be in order based on their number.
 * It will be added to the end of the list of rooms.
 * If there are too many cached rooms, delete some of the old ones.
 */
void add_room(WORLD *world, struct ROOM *room);

/**
 * The room that the player is currently in.
 */
struct ROOM *grab_room(WORLD *world);


/**
 * Create a new set of cached rooms.
 * If the number of rooms in the world exceeds the
 * max number of cached rooms, then some rooms will
 * be removed.
 */
void cache_rooms(WORLD *world);

void update_world(WORLD *world);
void paint_world(WORLD *world, BITMAP *canvas);


#endif
