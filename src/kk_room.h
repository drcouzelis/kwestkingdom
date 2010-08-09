#ifndef KK_ROOM_H
#define KK_ROOM_H


#include <allegro.h>


#define MAX_ENEMIES 100


typedef struct ROOM ROOM;
struct DOOR;
struct ENEMY;
struct HELP;
struct TILE;


struct ROOM
{
  /**
   * A list of the enemies currently in the room.
   */
  struct ENEMY *enemies[MAX_ENEMIES];
  int num_enemies;
  
  /**
   * A map of the tiles in the room.
   */
  struct TILE **tiles;

  /**
   * A map of the help tiles in the room.
   */
  struct HELP **help;
  
  /**
   * A map of the doors in the room.
   */
  struct DOOR **doors;
  
  /**
   * The number of tiles in the room.
   */
  int rows;
  int cols;
};


ROOM *create_room(int rows, int cols);
ROOM *destroy_room(ROOM *room);

void update_room(ROOM *room);
void paint_room(ROOM *room, BITMAP *canvas);


#endif
