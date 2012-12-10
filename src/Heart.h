#ifndef HEART_HEADER
#define HEART_HEADER


#include "Item.h"


class Heart : public Item {
public:
  Heart();

  void collectedBy(Character *character);
};


#endif
