#ifndef KK_TILE_H
#define KK_TILE_H


typedef struct TILE TILE;
struct ANIM;


typedef enum
{
  EMPTY = 0,
  SWIMMABLE,
  WALKABLE,
  FLYABLE,
  SOARABLE
} TILE_TYPE;


struct TILE
{
  struct ANIM *anim;
  
  /**
   * Helps determine how a character can interact
   * with this tile.
   */
  TILE_TYPE type;
};


TILE *create_tile(struct ANIM *anim, TILE_TYPE type);
TILE *destroy_tile(TILE *tile);


#endif
