#ifndef WORLD_HEADER
#define WORLD_HEADER


#include <allegro.h>


#define MAX_ROOMS 40


enum
{
  WORLD_NORMAL_STATE = 0,
  WORLD_SCROLLING_STATE,
  WORLD_SHAKING_STATE
};


typedef struct SNAPSHOT SNAPSHOT;
typedef struct WORLD WORLD;
struct PLAYER;
struct ROOM;
struct SPRITE;


struct SNAPSHOT
{
  BITMAP *film;
  struct SPRITE *sprite;
};


struct WORLD
{
  int state;
  
  /**
   * Represents the player, aka the hero!
   */
  struct PLAYER *player;
  
  /**
   * A level is a collection of rooms.
   * The world only has the current level.
   * Old levels are deleted,
   * and new levels are created when needed.
   */
  struct LEVEL *level;
  
  /**
   * This is used to see if the game
   * has been won.
   * Either set it to the number of the
   * final level, or to -1 for no end.
   */
  int final_level;
  
  /**
   * These are used to scroll between rooms.
   */
  SNAPSHOT *prev_snapshot;
  SNAPSHOT *next_snapshot;
};


WORLD *create_world();
void destroy_world(WORLD *world);

void update_world(WORLD *world);
void paint_world(WORLD *world, BITMAP *canvas);

struct ROOM *grab_room(WORLD *world);


#endif
