#ifndef KK_DIRECTION_H
#define KK_DIRECTION_H


enum
{
  NORTH = 0,
  SOUTH,
  EAST,
  WEST
};


enum
{
  UP = 0,
  DOWN,
  RIGHT,
  LEFT
};


typedef struct DIRECTION DIRECTION;


struct DIRECTION
{
  int type;
  
  int h_offset;
  int v_offset;
  
  int x_offset;
  int y_offset;
};


extern const DIRECTION north;
extern const DIRECTION south;
extern const DIRECTION east;
extern const DIRECTION west;

extern const DIRECTION up;
extern const DIRECTION down;
extern const DIRECTION right;
extern const DIRECTION left;


#endif
