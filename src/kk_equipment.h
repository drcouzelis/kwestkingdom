#ifndef KK_EQUIPMENT_H
#define KK_EQUIPMENT_H


#include "kk_utilities.h"


typedef struct EQUIPMENT EQUIPMENT;
struct SPRITE;


struct EQUIPMENT
{
  struct SPRITE *sprite;
  FLAG equipped;
  
  /**
   * The amount of damage this equipment blocks.
   */
  int guards;
  
  /**
   * The amount of damage this equipment attacks.
   */
  int attacks;
};


EQUIPMENT *create_equipment(struct SPRITE *sprite, int guards, int attacks);
EQUIPMENT *destroy_equipment(EQUIPMENT *equip);


#endif
