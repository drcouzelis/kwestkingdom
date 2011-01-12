#ifndef WORLD_HEADER
#define WORLD_HEADER


#include <allegro.h>

#define MAX_ROOMS 40


struct PLAYER;
struct ROOM;


void init_world();
void stop_world();

/**
 * The player.
 */
struct PLAYER *grab_hot_player();

/**
 * Add a room to the world.
 * Rooms will always be in order based on their number.
 * It will be added to the end of the list of rooms.
 * If there are too many cached rooms, delete some of the old ones.
 */
void add_room(struct ROOM *room);

/**
 * The room that the player is currently in.
 */
struct ROOM *grab_hot_room();


/**
 * Create a new set of cached rooms.
 * If the number of rooms in the world exceeds the
 * max number of cached rooms, then some rooms will
 * be removed.
 */
void cache_rooms();

void update_world();
void paint_world(BITMAP *canvas);


#endif
