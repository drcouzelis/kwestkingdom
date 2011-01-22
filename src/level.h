#ifndef LEVEL_HEADER
#define LEVEL_HEADER


#define ROOMS_PER_LEVEL 10


typedef struct LEVEL LEVEL;
struct ROOM;


struct LEVEL
{
  struct ROOM *rooms[ROOMS_PER_LEVEL];
  int room_idx;
  
  int num;
};


/**
 * The level number will determine
 * what the level looks like.
 */
LEVEL *create_level(int num, int entr_row, int entr_col);
void destroy_level(LEVEL *level);


#endif
