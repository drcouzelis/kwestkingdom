#ifndef INVENTORY_HEADER
#define INVENTORY_HEADER


#include <allegro.h>


typedef struct INVENTORY INVENTORY;
struct EQUIPMENT;


enum
{
  SWORD = 0,
  SHIELD,
  BOW,
  ARROW,
  HAMMER,
  
  NUM_EQUIPMENT
};


struct INVENTORY
{
  struct EQUIPMENT *equipment[NUM_EQUIPMENT];
};


INVENTORY *create_inventory();
INVENTORY *destroy_inventory(INVENTORY *invent);

void update_inventory(INVENTORY *invent);
void paind_inventory(INVENTORY *invent);

void move_inventory(INVENTORY *invent, int x, int y);
void warp_inventory(INVENTORY *invent, int x, int y);


#endif
