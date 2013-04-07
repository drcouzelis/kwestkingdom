#ifndef ITEM_HEADER
#define ITEM_HEADER


#include "Sprite.h"

class Character;
 

class Item : public Sprite {
public:
  virtual void collectedBy(Character *character)=0;
};

  
#endif
