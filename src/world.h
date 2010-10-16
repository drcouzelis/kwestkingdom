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
  
  /**
   * The room number that is currently occupied.
   * This may be greater than the number of rooms that
   * are currently in the world.
   */
  /*int room_num;*/
  
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
  FLAG (*is_game_won)(WORLD *world);
};


WORLD *create_world();
void destroy_world(WORLD *world);

void add_room(WORLD *world, struct ROOM *room);
void clear_rooms(WORLD *world);
struct ROOM *current_room(WORLD *world);
int find_highest_room_number(WORLD *world);

void update_world(WORLD *world);
void paint_world(WORLD *world, BITMAP *canvas);


#endif
