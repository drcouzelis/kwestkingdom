#ifndef COLLECTABLE_HEADER
#define COLLECTABLE_HEADER


#include "Character.h"


class Collectable {
  virtual void collectedBy(Character *character)=0;
};



#endif
