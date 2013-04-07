#ifndef HEART_HEADER
#define HEART_HEADER


#include "Item.h"


class Heart : public Item {

protected:

  ANIM heart_anim;

public:

  Heart();
  void collectedBy(Character *character);
};


#endif
