#ifndef KK_DOOR_H
#define KK_DOOR_H


typedef struct DOOR DOOR;


struct DOOR
{
  int new_room_num;
  int new_row;
  int new_col;
};


DOOR *create_door(int new_room_num, int new_row, int new_col);
DOOR *destroy_door(DOOR *door);


#endif
